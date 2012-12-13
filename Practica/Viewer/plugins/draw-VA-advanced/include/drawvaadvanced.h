#ifndef _DRAWVAADVANCED_H
#define _DRAWVAADVANCED_H

#include "drawinterface.h"
#include "vertex.h"
#include <vector>
using namespace std;

 class DrawVAAdvanced : public QObject, public DrawInterface
 {
     Q_OBJECT
     Q_INTERFACES(DrawInterface)

 private:
     vector<vector<Vertex> > vertices;
     vector<vector<Vertex> > normals;
     vector<vector<int> > indices;
     vector<int> cont;

 public:
     void drawScene();
     void onPluginLoad();
     void onObjectAdd();
 };
 
 #endif
 
 
