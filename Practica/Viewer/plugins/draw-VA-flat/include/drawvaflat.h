#ifndef _DRAWVAFLAT_H
#define _DRAWVAFLAT_H

#include "drawinterface.h"
#include <vector>
using namespace std;

 class DrawVAFlat : public QObject, public DrawInterface
 {
     Q_OBJECT
     Q_INTERFACES(DrawInterface)

 private:
     vector< vector<float[3]> > va;
     unsigned int numVA = 0; 

 public:
     void drawScene();
     void onPluginLoad();
     void onObjectAdd();
 };
 
 #endif
 
 
