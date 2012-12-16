#ifndef _OBJSEL_H
#define _OBJSEL_H

#include "actioninterface.h"

class ObjSel : public QObject, public ActionInterface
 {
     Q_OBJECT
     Q_INTERFACES(ActionInterface)

 public:
    void mouseReleaseEvent ( QMouseEvent * event );
 
 private:
    void pintaEscenaConColores();
    int   pxClick, pyClick;
 };
 
 #endif
 
 
