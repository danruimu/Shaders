#ifndef _OBJSEL_H
#define _OBJSEL_H

#include "actioninterface.h"

class ObjSel : public QObject, public ActionInterface
 {
     Q_OBJECT
     Q_INTERFACES(ActionInterface)

 public:
    ObjSel();
 
    void	keyPressEvent ( QKeyEvent *  ) {};
    void	keyReleaseEvent ( QKeyEvent *  ) {};
    
    void	mouseMoveEvent ( QMouseEvent * event );
    void	mousePressEvent ( QMouseEvent * event );
    void	mouseReleaseEvent ( QMouseEvent * event );
    void	wheelEvent ( QWheelEvent *  ) {};
 
 private:
    typedef  enum {NONE, ROTATE, ZOOM, PAN} MouseAction;
    MouseAction pmouseAction;
    int   pxClick, pyClick;
 };
 
 #endif
 
 
