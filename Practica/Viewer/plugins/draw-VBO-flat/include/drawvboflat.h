#ifndef _DRAWVBOFLAT_H
#define _DRAWVBOFLAT_H

#include "drawinterface.h"
#include "vertex.h"
#include "color.h"
#include "materiallib.h"
#include "glwidget.h"
#include <vector>
using namespace std;

 class DrawVBOFlat : public QObject, public DrawInterface
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
 
