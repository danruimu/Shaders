#ifndef _FRAGLIGHT_H
#define _FRAGLIGHT_H

#include "effectinterface.h"

 class FragLight : public QObject, public EffectInterface
 {
     Q_OBJECT
     Q_INTERFACES(EffectInterface)

 public:
     void drawScene();
 };
 
 #endif
 
 
