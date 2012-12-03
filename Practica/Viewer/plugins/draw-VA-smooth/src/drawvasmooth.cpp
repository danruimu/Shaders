#include "drawvasmooth.h"
#include "glwidget.h"

void DrawVASmooth::drawScene()
{
    Scene *scene = pglwidget->scene();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for(unsigned int i = 0; i<scene->objects().size(); ++i) {
        glVertexPointer(3, GL_FLOAT, 0, (void *) &vertices[i][0]);
        glNormalPointer(GL_FLOAT, 0, (void *) &normals[i][0]);

        glDrawArrays(GL_TRIANGLES, 0, vertices[i].size());

    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawVASmooth::onPluginLoad() {
    Scene* scene = pglwidget->scene();
    for(unsigned int i = 0; i<scene->objects().size(); ++i) {
        Object o = scene->objects()[i];
        vector<float> verticesAux;
        vector<float> normalsAux;
        for(unsigned int j = 0; j<o.faces().size(); ++j) {
            Face f = o.faces()[j];
            Vertex n = f.normal();
            for(unsigned int l = 0; l<f.numVertices(); ++l) {
                Vertex v = o.vertices()[f.vertexIndex(l)];
                verticesAux.push_back(v.coord().x());
                verticesAux.push_back(v.coord().y());
                verticesAux.push_back(v.coord().z());
                normalsAux.push_back(n.coord().x());
                normalsAux.push_back(n.coord().y());
                normalsAux.push_back(n.coord().z());
            }
        }
        vertices.push_back(verticesAux);
        normals.push_back(normalsAux);
    }
}

void DrawVASmooth::onObjectAdd() {
    Scene* scene = pglwidget->scene();
    Object o = scene->objects()[scene->objects().size()-1];
    vector<float> verticesAux;
    vector<float> normalsAux;
    for(unsigned int j = 0; j<o.faces().size(); ++j) {
        Face f = o.faces()[j];
        Vertex n = f.normal();
        for(unsigned int l = 0; l<f.numVertices(); ++l) {
            Vertex v = o.vertices()[f.vertexIndex(l)];
            verticesAux.push_back(v.coord().x());
            verticesAux.push_back(v.coord().y());
            verticesAux.push_back(v.coord().z());
            normalsAux.push_back(n.coord().x());
            normalsAux.push_back(n.coord().y());
            normalsAux.push_back(n.coord().z());
        }
    }
    vertices.push_back(verticesAux);
    normals.push_back(normalsAux);
}

Q_EXPORT_PLUGIN2(drawvasmooth, DrawVASmooth)   // plugin name, plugin class
