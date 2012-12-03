#include "drawvaflat.h"
#include "glwidget.h"

void DrawVAFlat::drawScene()
{
    glVertexPointer(3, GL_FLOAT, 0, (void *) &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, (void *) &normals[0]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawVAFlat::onPluginLoad() {
    Scene* scene = pglwidget->scene();
    for(unsigned int i = 0; i<scene->objects().size(); ++i) {
        Object o = scene->objects()[i];
        for(unsigned int j = 0; j<o.faces().size(); ++j) {
            Face f = o.faces()[j];
            Vertex n = f.normal();
            for(unsigned int l = 0; l<f.numVertices(); ++l) {
                Vertex v = o.vertices()[f.vertexIndex(l)];
                vertices.push_back(v.coord().x());
                vertices.push_back(v.coord().y());
                vertices.push_back(v.coord().z());
                normals.push_back(n.coord().x());
                normals.push_back(n.coord().y());
                normals.push_back(n.coord().z());
            }
        }
    }
}

void DrawVAFlat::onObjectAdd() {
    Scene* scene = pglwidget->scene();
    Object o = scene->objects()[scene->objects().size()-1];
    for(unsigned int j = 0; j<o.faces().size(); ++j) {
        Face f = o.faces()[j];
        Vertex n = f.normal();
        for(unsigned int l = 0; l<f.numVertices(); ++l) {
            Vertex v = o.vertices()[f.vertexIndex(l)];
            vertices.push_back(v.coord().x());
            vertices.push_back(v.coord().y());
            vertices.push_back(v.coord().z());
            normals.push_back(n.coord().x());
            normals.push_back(n.coord().y());
            normals.push_back(n.coord().z());
        }
    }
}

Q_EXPORT_PLUGIN2(drawvaflat, DrawVAFlat)   // plugin name, plugin class
