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
   
   std::vector<int> trk_n;   
   std::vector<float> trk_pt;
   std::vector<float> trk_eta;
   std::vector<float> trk_phi;
   std::vector<float> trk_par;
   std::vector<float> trk_cov;
   std::vector<float> trk_vx;
   std::vector<float> trk_vy;
   std::vector<float> trk_vz;
   
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
