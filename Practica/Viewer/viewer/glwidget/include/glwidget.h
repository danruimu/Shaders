#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "GL/glew.h"
#include "scene.h"
#include "camera.h"
#include "drawinterface.h"
#include "renderinterface.h"
#include "effectinterface.h"
#include "actioninterface.h"
#include <QPluginLoader>
#include <QtOpenGL/qgl.h>
#include <QKeyEvent>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include <iostream>
#include <vector>


// see Qt docs, "Creating shared libraries"
#ifdef PLUGINGLWIDGET_LIBRARY
#define PLUGINGLWIDGET_EXPORT Q_DECL_EXPORT
#else
#define PLUGINGLWIDGET_EXPORT Q_DECL_IMPORT
#endif

class  GLWidget : public QGLWidget  
{
    Q_OBJECT

public:
    PLUGINGLWIDGET_EXPORT GLWidget(QWidget * parent);
    PLUGINGLWIDGET_EXPORT Scene* scene();
    PLUGINGLWIDGET_EXPORT Camera* camera();

public slots:
    PLUGINGLWIDGET_EXPORT void help(void);
    PLUGINGLWIDGET_EXPORT void addObject();
    PLUGINGLWIDGET_EXPORT void addObjectFromFile(const QString& filename);
    PLUGINGLWIDGET_EXPORT void resetCamera();
    PLUGINGLWIDGET_EXPORT void drawAxes() const;
    PLUGINGLWIDGET_EXPORT Box boundingBoxIncludingAxes() const;
    PLUGINGLWIDGET_EXPORT void loadPlugin(); 

protected:
    virtual void initializeGL();
    virtual void paintGL( void );
    virtual void resizeGL (int width, int height);

    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent( QMouseEvent *e);
    virtual void mouseReleaseEvent( QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyReleaseEvent ( QKeyEvent *e);
    virtual void wheelEvent ( QWheelEvent *e);
    
private:
    Scene pscene;  
    Camera pcamera;
    
    RenderInterface* renderPlugin;
    DrawInterface* drawPlugin;
    vector<EffectInterface*> effectPlugins;
    vector<ActionInterface*> actionPlugins;
};

#endif
