#ifndef _FRAGLIGHT_H
#define _FRAGLIGHT_H

#include "effectinterface.h"
#include "glwidget.h"
#include <QGLShader>
#include <QGLShaderProgram>

 class FragLight : public QObject, public EffectInterface
 {
     Q_OBJECT
     Q_INTERFACES(EffectInterface)

 private:
     QGLShaderProgram ShaderProgram;

 public:
     void onPluginLoad();
     void preFrame();
     void postFrame();
 };
 
 #endif
 
 
