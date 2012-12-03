#include "drawvaflat.h"
#include "glwidget.h"

void DrawVAFlat::drawScene()
{
    Scene *scene = pglwidget->scene();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for(unsigned int i = 0; i<vertices.size(); ++i) {
        glVertexPointer(3, GL_FLOAT, 0, (void *) &vertices[i][0]);
        glNormalPointer(GL_FLOAT, 0, (void *) &normals[i][0]);

        glDrawArrays(GL_TRIANGLES, 0, vertices[i].size());

    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawVAFlat::onPluginLoad() {
    Scene* scene = pglwidget->scene();
    for(unsigned int i = 0; i<scene->objects().size(); ++i) {
        Object o = scene->objects()[i];
        vector<float> verticesAux;
        vector<float> normalsAux;
        for(unsigned int j = 0; j<o.vertices().size(); ++j) {
            Vertex vert = o.vertices()[j];
            verticesAux.push_back(vert.coord().x());
            verticesAux.push_back(vert.coord().y());
            verticesAux.push_back(vert.coord().z());
        }
        normalsAux = vector<float> (verticesAux.size());
        for(unsigned int j = 0; j<o.faces().size(); ++j) {
            Face f = o.faces()[j];
            Vertex normal = f.normal();
            for(unsigned int l = 0; l<f.numVertices(); ++l) {
                normalsAux[f.vertexIndex(l)*3] = normal.coord().x();
                normalsAux[f.vertexIndex(l)*3+1] = normal.coord().y();
                normalsAux[f.vertexIndex(l)*3+2] = normal.coord().z();
            }
        }
        vertices.push_back(verticesAux);
        normals.push_back(normalsAux);

        vector<int> indicesAux(o.faces().size()*3);
    }
}

void DrawVAFlat::onObjectAdd() {
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

Q_EXPORT_PLUGIN2(drawvaflat, DrawVAFlat)   // plugin name, plugin class
