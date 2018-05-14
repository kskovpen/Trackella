#ifndef TRACKTREE_H
#define TRACKTREE_H

#include <TTree.h>
#include <TLorentzVector.h>
#include <string>
#include <iostream>
#include <vector>

#include <boost/any.hpp>
using boost::any_cast;
typedef std::map<std::string, std::map<std::string, boost::any> >  t_map;

#define DEFVAL -666

class TrackTree
{
 public:

   TrackTree(TTree* _tree) {tree = _tree;};
   TTree* tree;

   void Init();
   void CreateBranches(int buffersize);

   int ev_run;
   int ev_id;
   int ev_lb;
   
   float bs_x0;
   float bs_y0;
   float bs_z0;
   float bs_sigmaZ;
   float bs_dxdz;
   float bs_dydz;
   float bs_BeamWidthX;
   float bs_BeamWidthY;
   float bs_x0Error;
   float bs_y0Error;
   float bs_z0Error;
   float bs_sigmaZ0Error;
   float bs_dxdzError;
   float bs_dydzError;
   float bs_BeamWidthXError;
   float bs_BeamWidthYError;
   
   std::vector<int> trk_n;   
   std::vector<float> trk_pt;
   std::vector<float> trk_eta;
   std::vector<float> trk_phi;
   std::vector<float> trk_par;
   std::vector<float> trk_cov;
   std::vector<float> trk_vx;
   std::vector<float> trk_vy;
   std::vector<float> trk_vz;

   std::vector<float> trk_chi2;
   std::vector<float> trk_ndof;
   std::vector<float> trk_dxy;
   std::vector<float> trk_dxyError;
   std::vector<float> trk_dz;
   std::vector<float> trk_dzError;
   std::vector<float> trk_dxy_bs;
   std::vector<float> trk_dz_bs;
   
   std::vector<int> trk_hit_n;
   std::vector<int> trk_hit_detId;
   std::vector<float> trk_hit_localPos_x;
   std::vector<float> trk_hit_localPos_y;
   std::vector<float> trk_hit_localPosErr_xx;
   std::vector<float> trk_hit_localPosErr_yy;
   std::vector<float> trk_hit_globalPos_x;
   std::vector<float> trk_hit_globalPos_y;
   std::vector<float> trk_hit_globalPos_z;
   std::vector<float> trk_hit_globalPosErr_cxx;
   std::vector<float> trk_hit_globalPosErr_cyy;
   std::vector<float> trk_hit_globalPosErr_czz;

   std::vector<int> trk_seed_n;
   std::vector<int> trk_seed_detId;
   std::vector<float> trk_seed_localPos_x;
   std::vector<float> trk_seed_localPos_y;
   std::vector<float> trk_seed_localPosErr_xx;
   std::vector<float> trk_seed_localPosErr_yy;
   std::vector<float> trk_seed_globalPos_x;
   std::vector<float> trk_seed_globalPos_y;
   std::vector<float> trk_seed_globalPos_z;
   std::vector<float> trk_seed_globalPosErr_cxx;
   std::vector<float> trk_seed_globalPosErr_cyy;
   std::vector<float> trk_seed_globalPosErr_czz;

   std::vector<int> vtx_n;
   std::vector<float> vtx_x;
   std::vector<float> vtx_y;
   std::vector<float> vtx_z;
   std::vector<float> vtx_xError;
   std::vector<float> vtx_yError;
   std::vector<float> vtx_zError;
   std::vector<float> vtx_cov;
};

#endif
