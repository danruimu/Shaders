#ifndef _DRAWVAFLAT_H
#define _DRAWVAFLAT_H

#include "drawinterface.h"
#include "vertex.h"
#include <vector>
using namespace std;

 class DrawVAFlat : public QObject, public DrawInterface
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
 
 
