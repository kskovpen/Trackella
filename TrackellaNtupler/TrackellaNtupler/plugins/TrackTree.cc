#include "TrackellaNtupler/TrackellaNtupler/interface/TrackTree.hh"

void TrackTree::Init()
{
   trk_n.clear();   
   trk_pt.clear();
   trk_eta.clear();
   trk_phi.clear();
   trk_par.clear();
   trk_cov.clear();
   trk_vx.clear();
   trk_vy.clear();
   trk_vz.clear();
   
   trk_hit_n.clear();
   trk_hit_detId.clear();
   trk_hit_localPos_x.clear();
   trk_hit_localPos_y.clear();
   trk_hit_localPosErr_xx.clear();
   trk_hit_localPosErr_yy.clear();
   trk_hit_globalPos_x.clear();
   trk_hit_globalPos_y.clear();
   trk_hit_globalPos_z.clear();
   trk_hit_globalPosErr_cxx.clear();
   trk_hit_globalPosErr_cyy.clear();
   trk_hit_globalPosErr_czz.clear();

   trk_seed_n.clear();
   trk_seed_detId.clear();
   trk_seed_localPos_x.clear();
   trk_seed_localPos_y.clear();
   trk_seed_localPosErr_xx.clear();
   trk_seed_localPosErr_yy.clear();
   trk_seed_globalPos_x.clear();
   trk_seed_globalPos_y.clear();
   trk_seed_globalPos_z.clear();
   trk_seed_globalPosErr_cxx.clear();
   trk_seed_globalPosErr_cyy.clear();
   trk_seed_globalPosErr_czz.clear();

   vtx_n.clear();
   vtx_x.clear();
   vtx_y.clear();
   vtx_z.clear();
   vtx_xError.clear();
   vtx_yError.clear();
   vtx_zError.clear();
   vtx_cov.clear();
}

void TrackTree::CreateBranches(int buffersize = 32000)
{
   tree->Branch("trk_n", "std::vector<int>", &trk_n, buffersize);
   tree->Branch("trk_pt", "std::vector<float>", &trk_pt, buffersize);
   tree->Branch("trk_eta", "std::vector<float>", &trk_eta, buffersize);
   tree->Branch("trk_phi", "std::vector<float>", &trk_phi, buffersize);
   tree->Branch("trk_par", "std::vector<float>", &trk_par, buffersize);
   tree->Branch("trk_cov", "std::vector<float>", &trk_cov, buffersize);
   tree->Branch("trk_vx", "std::vector<float>", &trk_vx, buffersize);
   tree->Branch("trk_vy", "std::vector<float>", &trk_vy, buffersize);
   tree->Branch("trk_vz", "std::vector<float>", &trk_vz, buffersize);
   
   tree->Branch("trk_hit_n", "std::vector<int>", &trk_hit_n, buffersize);
   tree->Branch("trk_hit_detId", "std::vector<int>", &trk_hit_detId, buffersize);
   tree->Branch("trk_hit_localPos_x", "std::vector<float>", &trk_hit_localPos_x, buffersize);
   tree->Branch("trk_hit_localPos_y", "std::vector<float>", &trk_hit_localPos_y, buffersize);
   tree->Branch("trk_hit_localPosErr_xx", "std::vector<float>", &trk_hit_localPosErr_xx, buffersize);
   tree->Branch("trk_hit_localPosErr_yy", "std::vector<float>", &trk_hit_localPosErr_yy, buffersize);
   tree->Branch("trk_hit_globalPos_x", "std::vector<float>", &trk_hit_globalPos_x, buffersize);
   tree->Branch("trk_hit_globalPos_y", "std::vector<float>", &trk_hit_globalPos_y, buffersize);
   tree->Branch("trk_hit_globalPos_z", "std::vector<float>", &trk_hit_globalPos_z, buffersize);
   tree->Branch("trk_hit_globalPosErr_cxx", "std::vector<float>", &trk_hit_globalPosErr_cxx, buffersize);
   tree->Branch("trk_hit_globalPosErr_cyy", "std::vector<float>", &trk_hit_globalPosErr_cyy, buffersize);
   tree->Branch("trk_hit_globalPosErr_czz", "std::vector<float>", &trk_hit_globalPosErr_czz, buffersize);

   tree->Branch("trk_seed_n", "std::vector<int>", &trk_seed_n, buffersize);
   tree->Branch("trk_seed_detId", "std::vector<int>", &trk_seed_detId, buffersize);
   tree->Branch("trk_seed_localPos_x", "std::vector<float>", &trk_seed_localPos_x, buffersize);
   tree->Branch("trk_seed_localPos_y", "std::vector<float>", &trk_seed_localPos_y, buffersize);
   tree->Branch("trk_seed_localPosErr_xx", "std::vector<float>", &trk_seed_localPosErr_xx, buffersize);
   tree->Branch("trk_seed_localPosErr_yy", "std::vector<float>", &trk_seed_localPosErr_yy, buffersize);
   tree->Branch("trk_seed_globalPos_x", "std::vector<float>", &trk_seed_globalPos_x, buffersize);
   tree->Branch("trk_seed_globalPos_y", "std::vector<float>", &trk_seed_globalPos_y, buffersize);
   tree->Branch("trk_seed_globalPos_z", "std::vector<float>", &trk_seed_globalPos_z, buffersize);
   tree->Branch("trk_seed_globalPosErr_cxx", "std::vector<float>", &trk_seed_globalPosErr_cxx, buffersize);
   tree->Branch("trk_seed_globalPosErr_cyy", "std::vector<float>", &trk_seed_globalPosErr_cyy, buffersize);
   tree->Branch("trk_seed_globalPosErr_czz", "std::vector<float>", &trk_seed_globalPosErr_czz, buffersize);
   
   tree->Branch("vtx_n", "std::vector<int>", &vtx_n, buffersize);
   tree->Branch("vtx_x", "std::vector<float>", &vtx_x, buffersize);
   tree->Branch("vtx_y", "std::vector<float>", &vtx_y, buffersize);
   tree->Branch("vtx_z", "std::vector<float>", &vtx_z, buffersize);
   tree->Branch("vtx_xError", "std::vector<float>", &vtx_xError, buffersize);
   tree->Branch("vtx_yError", "std::vector<float>", &vtx_yError, buffersize);
   tree->Branch("vtx_zError", "std::vector<float>", &vtx_zError, buffersize);
   tree->Branch("vtx_cov", "std::vector<float>", &vtx_cov, buffersize);
}
