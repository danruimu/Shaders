#ifndef _DRAWVBOSMOOTH_H
#define _DRAWVBOSMOOTH_H

#include "drawinterface.h"
#include "vertex.h"
#include <vector>
using namespace std;

 class DrawVBOSmooth : public QObject, public DrawInterface
 {
     Q_OBJECT
     Q_INTERFACES(DrawInterface)

 private:
     vector<GLuint> ids;    //vector de identificadors de VBO, on es guardaen cuartets VNCI de cada objecte
     vector<int> tamI;

 public:
     void drawScene();
     void onPluginLoad();
     void onObjectAdd();
 };
 
 #endif
 
 
