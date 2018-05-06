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
   
   std::vector<int> ev_ntrk;
   
   std::vector<float> trk_pt;
   
   std::vector<int> hit_detId;
   std::vector<float> hit_localPos_x;
   std::vector<float> hit_localPos_y;
   std::vector<float> hit_localPosErr_xx;
   std::vector<float> hit_localPosErr_yy;
   std::vector<float> hit_globalPos_x;
   std::vector<float> hit_globalPos_y;
   std::vector<float> hit_globalPos_z;
   std::vector<float> hit_globalPosErr_cxx;
   std::vector<float> hit_globalPosErr_cyy;
   std::vector<float> hit_globalPosErr_czz;
};

#endif
