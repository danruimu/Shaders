#ifndef _DRAWVBOFLAT_H
#define _DRAWVBOFLAT_H

#include "drawinterface.h"
#include "vertex.h"
#include <vector>
using namespace std;

 class DrawVBOFlat : public QObject, public DrawInterface
 {
     Q_OBJECT
     Q_INTERFACES(DrawInterface)

 private:
     vector<vector<Vertex> > vertices;
     vector<vector<Vertex> > normals;
     vector<vector<int> > indices;

 public:
     void drawScene();
     void onPluginLoad();
     void onObjectAdd();
 };
 
 #endif
 
 
