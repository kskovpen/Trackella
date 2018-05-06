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
   
   edm::Handle<std::vector<reco::Track> > generalTracksHandle;
   
   TrackTree *ftree;
   
   const edm::Service<TFileService> fs;
};

TrackAnalysis::TrackAnalysis(const edm::ParameterSet& iConfig)
{
   generalTracksToken_    = consumes<std::vector<reco::Track> >(iConfig.getParameter<edm::InputTag>("generalTracksInput"));
   
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
   
   const std::vector<reco::Track> &gt = *generalTracksHandle.product();

   ftree->ev_ntrk.push_back(gt.size());

   for( unsigned int it=0;it<gt.size();it++ )
     {
	reco::Track trk = gt.at(it);
			
	ftree->trk_pt.push_back(trk.pt());

	edm::RefToBase<TrajectorySeed> seedRef = trk.seedRef();
	
	for( trackingRecHit_iterator ih=trk.recHitsBegin();ih!=trk.recHitsEnd();++ih )
	  {
	     if( ! (*ih)->isValid() ) continue;
	     
	     if ( (*ih)->geographicalId().det() != DetId::Tracker ) continue;

	     const TrackingRecHit &thit = **ih;
	     const SiPixelRecHit* rmh = dynamic_cast<const SiPixelRecHit*>(&thit);
	     
	     if( rmh )
	       {	
		  ftree->hit_detId.push_back(rmh->geographicalId().rawId());
		  ftree->hit_localPos_x.push_back(rmh->localPosition().x());
		  ftree->hit_localPos_y.push_back(rmh->localPosition().y());
		  ftree->hit_localPosErr_xx.push_back(rmh->localPositionError().xx());
		  ftree->hit_localPosErr_yy.push_back(rmh->localPositionError().yy());
		  ftree->hit_globalPos_x.push_back(rmh->globalPosition().x());
		  ftree->hit_globalPos_y.push_back(rmh->globalPosition().y());
		  ftree->hit_globalPos_z.push_back(rmh->globalPosition().z());
		  ftree->hit_globalPosErr_cxx.push_back(rmh->globalPositionError().cxx());
		  ftree->hit_globalPosErr_cyy.push_back(rmh->globalPositionError().cyy());
		  ftree->hit_globalPosErr_czz.push_back(rmh->globalPositionError().czz());
	       }
	  }
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

