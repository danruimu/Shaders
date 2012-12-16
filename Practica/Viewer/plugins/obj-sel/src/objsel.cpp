#include "objsel.h"
#include "glwidget.h"

void ObjSel::pintaEscenaConColores() {
    float r,g,b;
    r = g = b = 0.0f;
    Scene* scene = pglwidget->scene();

    // per cada objecte
    for (unsigned int i=1; i<scene->objects().size(); ++i)
    {
        const Object& obj = scene->objects()[i];
        // per cada cara
        for(unsigned int c=0; c<obj.faces().size(); c++)
        {
            const Face& face = obj.faces()[c];
            glColor3f(r,g,b);
            glBegin (GL_POLYGON);
            glNormal3f(face.normal().x(), face.normal().y(), face.normal().z());
            // per cada vertex
            for(int v=0; v<face.numVertices(); v++)
            {
                const Point& p = obj.vertices()[face.vertexIndex(v)].coord();
                glVertex3f(p.x(), p.y(), p.z());
            }
            glEnd();
        }

        if(r<1.0f) {
            r += 0.01f;
        } else if(g<1.0f) {
            g += 0.01f;
        } else if(b<1.0f) {
            b += 0.01f;
        } else {
            std::cout<<"No se pueden manejar mas objetos al mismo tiempo"<<std::endl;
        }
        if(r==0.8f && g==0.8f && b==0.8f) b +=0.01f;
    }
    pglwidget->updateGL();
}

void ObjSel::mouseReleaseEvent( QMouseEvent *event)
{
    Scene *scene = pglwidget->scene();

    pintaEscenaConColores();

    pxClick = event->x();
    pyClick = event->y();

    if(event->button() & Qt::LeftButton && event->modifiers() & Qt::ControlModifier) {
        Color color;
        glReadBuffer(GL_FRONT);
        glReadPixels(pxClick, pyClick, 1, 1, GL_RGBA, GL_FLOAT, (void*)&color);

        if(color.red()==0.8f && color.green()==0.8f && color.blue()==0.8f && color.alpha()==0.0f) {
            std::cout<<"Estoy en el fondo"<<std::endl;
            scene->setSelectedObject(-1);
        } else {
            std::cout<<"Estoy en un objeto"<<std::endl;
            std::cout<<color.red()<<","<<color.green()<<","<<color.blue()<<std::endl;
        }
    }

    pglwidget->updateGL();
}

Q_EXPORT_PLUGIN2(objsel, ObjSel)   // plugin name, plugin class
