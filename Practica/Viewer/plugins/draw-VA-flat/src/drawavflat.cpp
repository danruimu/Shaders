#include "drawvaflat.h"
#include "glwidget.h"

void DrawVAFlat::drawScene()
{
    float vert[vertices.size()];
    float norm[normals.size()];

    for(unsigned int i=0; i<vertices.size(); ++i) vert[i] = vertices[i];
    for(unsigned int i=0; i<normals.size(); ++i) norm[i] = normals[i];

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for(unsigned int i = 0; i<vertices.size(); ++i) {
        glVertexPointer(3, GL_FLOAT, 0, (void*) vert);
	}
    for(unsigned int i = 0; i<normals.size(); ++i) {
        glNormalPointer(GL_FLOAT, 0, (void*) norm);
    }
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawVAFlat::onPluginLoad() {
	Scene* scene = pglwidget->scene();
    for(unsigned int i=0; i<scene->objects().size(); ++i) {
        Object obj = scene->objects()[i];
        for(unsigned int j=0; j<obj.vertices().size(); ++j) {
            Vertex v = obj.vertices()[j];
            vertices.push_back(v.coord().x());
            vertices.push_back(v.coord().y());
            vertices.push_back(v.coord().z());
        }
        for(unsigned int j=0; j<obj.faces().size(); ++j) {
            Face f = obj.faces()[j];
            Vertex n = f.normal();
            normals.push_back(n.coord().x());
            normals.push_back(n.coord().y());
            normals.push_back(n.coord().z());
        }
    }
}

void DrawVAFlat::onObjectAdd() {
	Scene* scene = pglwidget->scene();
    Object obj = scene->objects()[scene->objects().size()-1];
    for(unsigned int i=0; i<obj.vertices().size(); ++i) {
        Vertex v = obj.vertices()[i];
        vertices.push_back(v.coord().x());
        vertices.push_back(v.coord().y());
        vertices.push_back(v.coord().z());
	}
    for(unsigned int j=0; j<obj.faces().size(); ++j) {
        Face f = obj.faces()[j];
        Vertex n = f.normal();
        normals.push_back(n.coord().x());
        normals.push_back(n.coord().y());
        normals.push_back(n.coord().z());
    }
}

Q_EXPORT_PLUGIN2(drawvaflat, DrawVAFlat)   // plugin name, plugin class
