#include "TrackellaNtupler/TrackellaNtupler/interface/TrackTree.hh"

void TrackTree::Init()
{
   ev_ntrk.clear();
   
   trk_pt.clear();
   
   hit_detId.clear();
   hit_localPos_x.clear();
   hit_localPos_y.clear();
   hit_localPosErr_xx.clear();
   hit_localPosErr_yy.clear();
   hit_globalPos_x.clear();
   hit_globalPos_y.clear();
   hit_globalPos_z.clear();
   hit_globalPosErr_cxx.clear();
   hit_globalPosErr_cyy.clear();
   hit_globalPosErr_czz.clear();
}

void TrackTree::CreateBranches(int buffersize = 32000)
{
   tree->Branch("ev_ntrk", "std::vector<int>", &ev_ntrk, buffersize);
   
   tree->Branch("trk_pt", "std::vector<float>", &trk_pt, buffersize);
   
   tree->Branch("hit_detId", "std::vector<int>", &hit_detId, buffersize);
   tree->Branch("hit_localPos_x", "std::vector<float>", &hit_localPos_x, buffersize);
   tree->Branch("hit_localPos_y", "std::vector<float>", &hit_localPos_y, buffersize);
   tree->Branch("hit_localPosErr_xx", "std::vector<float>", &hit_localPosErr_xx, buffersize);
   tree->Branch("hit_localPosErr_yy", "std::vector<float>", &hit_localPosErr_yy, buffersize);
   tree->Branch("hit_globalPos_x", "std::vector<float>", &hit_globalPos_x, buffersize);
   tree->Branch("hit_globalPos_y", "std::vector<float>", &hit_globalPos_y, buffersize);
   tree->Branch("hit_globalPos_z", "std::vector<float>", &hit_globalPos_z, buffersize);
   tree->Branch("hit_globalPosErr_cxx", "std::vector<float>", &hit_globalPosErr_cxx, buffersize);
   tree->Branch("hit_globalPosErr_cyy", "std::vector<float>", &hit_globalPosErr_cyy, buffersize);
   tree->Branch("hit_globalPosErr_czz", "std::vector<float>", &hit_globalPosErr_czz, buffersize);
}
