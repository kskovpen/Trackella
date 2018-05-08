#include <memory>
#include <iostream>
#include <sstream>

#include "TRegexp.h"
#include "TString.h"
#include "Compression.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "CLHEP/Units/GlobalSystemOfUnits.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"

#include "TrackellaNtupler/TrackellaNtupler/interface/TrackTree.hh"

class TrackAnalysis : public edm::EDAnalyzer
{
 public:

   explicit TrackAnalysis(const edm::ParameterSet&);
   ~TrackAnalysis();

   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

 private:

   virtual void analyze(const edm::Event&, const edm::EventSetup&) override;

   virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
   virtual void endRun(const edm::Run&, const edm::EventSetup&) override;
   
   edm::EDGetTokenT<std::vector<reco::Track> > generalTracksToken_;
   edm::EDGetTokenT<std::vector<reco::Vertex> > offlinePrimaryVerticesToken_;
   
   edm::Handle<std::vector<reco::Track> > generalTracksHandle;
   edm::Handle<std::vector<reco::Vertex> > offlinePrimaryVerticesHandle;
   
   TrackTree *ftree;
   
   const edm::Service<TFileService> fs;
};

TrackAnalysis::TrackAnalysis(const edm::ParameterSet& iConfig)
{
   generalTracksToken_    = consumes<std::vector<reco::Track> >(iConfig.getParameter<edm::InputTag>("generalTracksInput"));
   offlinePrimaryVerticesToken_    = consumes<std::vector<reco::Vertex> >(iConfig.getParameter<edm::InputTag>("offlinePrimaryVerticesInput"));
   
   TFile& f = fs->file();   
   f.SetCompressionAlgorithm(ROOT::kZLIB);
   f.SetCompressionLevel(9);
   ftree = new TrackTree(fs->make<TTree>("tree","tree"));
   ftree->CreateBranches(32000);
}

TrackAnalysis::~TrackAnalysis()
{
}

void TrackAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{ 
   using namespace edm;
   
   ftree->Init();

   iEvent.getByToken(generalTracksToken_,generalTracksHandle);
   iEvent.getByToken(offlinePrimaryVerticesToken_,offlinePrimaryVerticesHandle);
   
   const std::vector<reco::Track> &gt = *generalTracksHandle.product();
   const std::vector<reco::Vertex> &pv = *offlinePrimaryVerticesHandle.product();

   ftree->trk_n.push_back(gt.size());
   ftree->vtx_n.push_back(pv.size());

   for( unsigned int it=0;it<gt.size();it++ )
     {
	reco::Track trk = gt.at(it);
	
	reco::TrackBase::ParameterVector par = trk.parameters();
	reco::TrackBase::CovarianceMatrix cov = trk.covariance();
			
	ftree->trk_pt.push_back(trk.pt());
	ftree->trk_eta.push_back(trk.eta());
	ftree->trk_phi.push_back(trk.phi());

	for(int ip=0;ip<5;ip++) ftree->trk_par.push_back(par(ip));
	for(int ip=0;ip<5;ip++)
	  for(int ipp=0;ipp<5;ipp++)
	    ftree->trk_cov.push_back(cov(ip,ipp));
	
	ftree->trk_vx.push_back(trk.vx());
	ftree->trk_vy.push_back(trk.vy());
	ftree->trk_vz.push_back(trk.vz());
	
	edm::RefToBase<TrajectorySeed> seedRef = trk.seedRef();
	unsigned int nSeed = seedRef->nHits();
	
	ftree->trk_seed_n.push_back(nSeed);
	
	for(unsigned int is=0;is<nSeed;is++)
	  {
	     const TrackingRecHit &shit = *(seedRef->recHits().first+is);

	     ftree->trk_seed_detId.push_back(shit.geographicalId().rawId());
	     ftree->trk_seed_localPos_x.push_back(shit.localPosition().x());
	     ftree->trk_seed_localPos_y.push_back(shit.localPosition().y());
	     ftree->trk_seed_localPosErr_xx.push_back(shit.localPositionError().xx());
	     ftree->trk_seed_localPosErr_yy.push_back(shit.localPositionError().yy());
	     ftree->trk_seed_globalPos_x.push_back(shit.globalPosition().x());
	     ftree->trk_seed_globalPos_y.push_back(shit.globalPosition().y());
	     ftree->trk_seed_globalPos_z.push_back(shit.globalPosition().z());
	     ftree->trk_seed_globalPosErr_cxx.push_back(shit.globalPositionError().cxx());
	     ftree->trk_seed_globalPosErr_cyy.push_back(shit.globalPositionError().cyy());
	     ftree->trk_seed_globalPosErr_czz.push_back(shit.globalPositionError().czz());
	  }	
	
	int nHits = 0;
	for( trackingRecHit_iterator ih=trk.recHitsBegin();ih!=trk.recHitsEnd();++ih )
	  {
	     if( ! (*ih)->isValid() ) continue;
	     
//	     if ( (*ih)->geographicalId().det() != DetId::Tracker ) continue;

	     const TrackingRecHit &thit = **ih;
//	     const SiPixelRecHit* rmh = dynamic_cast<const SiPixelRecHit*>(&thit);
	     
//	     if( rmh )
//	       {	
		  ftree->trk_hit_detId.push_back(thit.geographicalId().rawId());
		  ftree->trk_hit_localPos_x.push_back(thit.localPosition().x());
		  ftree->trk_hit_localPos_y.push_back(thit.localPosition().y());
		  ftree->trk_hit_localPosErr_xx.push_back(thit.localPositionError().xx());
		  ftree->trk_hit_localPosErr_yy.push_back(thit.localPositionError().yy());
		  ftree->trk_hit_globalPos_x.push_back(thit.globalPosition().x());
		  ftree->trk_hit_globalPos_y.push_back(thit.globalPosition().y());
		  ftree->trk_hit_globalPos_z.push_back(thit.globalPosition().z());
		  ftree->trk_hit_globalPosErr_cxx.push_back(thit.globalPositionError().cxx());
		  ftree->trk_hit_globalPosErr_cyy.push_back(thit.globalPositionError().cyy());
		  ftree->trk_hit_globalPosErr_czz.push_back(thit.globalPositionError().czz());
//	       }
	       nHits++;
	  }
	ftree->trk_hit_n.push_back(nHits);
     }

   for( unsigned int iv=0;iv<pv.size();iv++ )
     {
	reco::Vertex vtx = pv.at(iv);
			
	ftree->vtx_x.push_back(vtx.x());
	ftree->vtx_y.push_back(vtx.y());
	ftree->vtx_z.push_back(vtx.z());
	ftree->vtx_xError.push_back(vtx.xError());
	ftree->vtx_yError.push_back(vtx.yError());
	ftree->vtx_zError.push_back(vtx.zError());

	for(int ip=0;ip<3;ip++)
	  for(int ipp=0;ipp<3;ipp++)
	    ftree->vtx_cov.push_back(vtx.covariance(ip,ipp));
	
//	for( trackRef_iterator it=vtx.tracks_begin();it!=vtx.tracks_end();++it )
//	  {
//	     
//	  }
     }
   
   ftree->tree->Fill();
}

void TrackAnalysis::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
}

void TrackAnalysis::endRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
}

void TrackAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackAnalysis);

