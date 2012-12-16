#include "drawvboflat.h"
#include "glwidget.h"

void DrawVBOFlat::drawScene()
{
    int j = 0;
    for(int i = 0; i<ids.size(); ++i) {
        if(i%4==0) {    //v
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, ids[i]);
            glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)0);
        } else if(i%4==1) { //n
            glBindBuffer(GL_ARRAY_BUFFER, ids[i]);
            glNormalPointer(GL_FLOAT, 0, (GLvoid*)0);
            //glEnableClientState(GL_NORMAL_ARRAY);
        } else if(i%4==2) { //c
            glBindBuffer(GL_ARRAY_BUFFER, ids[i]);
            glColorPointer(4, GL_FLOAT, 0, (GLvoid*)0);
            //glEnableClientState(GL_COLOR_ARRAY);
        } else if(i%4==3) { //i
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ids[i]);
            glDrawElements(GL_TRIANGLES, tamI[j++], GL_UNSIGNED_INT, (GLvoid*)0);

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}

void DrawVBOFlat::onPluginLoad() {
    Scene* scene = pglwidget->scene();
    MaterialLib* matlib = MaterialLib::instance();
    //Per cada objecte de l'escena
    for(int i = 0; i<scene->objects().size(); ++i) {
        Object obj = scene->objects()[i];
        vector<Vertex> v = obj.vertices();
        vector<Vertex> n = v;
        vector<Color> c; c.resize(v.size());
        for(int j = 0; j<obj.faces().size(); ++j) {
            Face face = obj.faces()[j];
            Material m = matlib->material(face.materialIndex());
            for(int l = 0; l<face.numVertices(); ++l) {
                n[face.vertexIndex(l)] = face.normal();
                c[face.vertexIndex(l)] = m.ambient();
            }
        }
        /* v = array de vertices
         * n = array de normales de cada vertice
         * c = array de colores de cada vertice
         */
        GLuint auxID[3];
        glGenBuffers(3, auxID);
        ids.push_back(auxID[0]);
        ids.push_back(auxID[1]);
        ids.push_back(auxID[2]);

        glBindBuffer(GL_ARRAY_BUFFER, auxID[0]);
        glBufferData(GL_ARRAY_BUFFER, v.size()*sizeof(Vertex), (void*)&v[0],GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, auxID[1]);
        glBufferData(GL_ARRAY_BUFFER, n.size()*sizeof(Vertex), (void*)&n[0],GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, auxID[2]);
        glBufferData(GL_ARRAY_BUFFER, c.size()*sizeof(Color), (void*)&c[0],GL_STATIC_DRAW);

        //Ahora falta calcular el vector de Indices
        vector<int> ind;
        for(int j = 0; j<obj.faces().size(); ++j) {
            int first, last, next;
            Face face = obj.faces()[j];
            first = face.vertexIndex(0);
            last = face.vertexIndex(1);
            next = face.vertexIndex(2);
            ind.push_back(first); ind.push_back(last); ind.push_back(next);
            for(int l = 3; l<face.numVertices(); ++l) {
                last = next;
                next = face.vertexIndex(l);
                ind.push_back(first); ind.push_back(last); ind.push_back(next);
            }
        }
        /* ind = array de indices */
        GLuint auxID2[1];
        glGenBuffers(1, auxID2);
        ids.push_back(auxID2[0]);
        tamI.push_back(ind.size());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, auxID2[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size()*sizeof(int), (void*)&ind[0], GL_STATIC_DRAW);
    }
}

void DrawVBOFlat::onObjectAdd() {
    Scene* scene = pglwidget->scene();
    MaterialLib* matlib = MaterialLib::instance();
    Object obj = scene->objects()[scene->objects().size()-1];
    vector<Vertex> v = obj.vertices();
    vector<Vertex> n = v;
    vector<Color> c; c.resize(v.size());
    for(int j = 0; j<obj.faces().size(); ++j) {
        Face face = obj.faces()[j];
        Material m = matlib->material(face.materialIndex());
        for(int l = 0; l<face.numVertices(); ++l) {
            n[face.vertexIndex(l)] = face.normal();
            c[face.vertexIndex(l)] = m.ambient();
        }
    }
    /* v = array de vertices
     * n = array de normales de cada vertice
     * c = array de colores de cada vertice
     */
    GLuint auxID[3];
    glGenBuffers(3, auxID);
    ids.push_back(auxID[0]);
    ids.push_back(auxID[1]);
    ids.push_back(auxID[2]);

    glBindBuffer(GL_ARRAY_BUFFER, auxID[0]);
    glBufferData(GL_ARRAY_BUFFER, v.size()*sizeof(Vertex), (void*)&v[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, auxID[1]);
    glBufferData(GL_ARRAY_BUFFER, n.size()*sizeof(Vertex), (void*)&n[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, auxID[2]);
    glBufferData(GL_ARRAY_BUFFER, c.size()*sizeof(Color), (void*)&c[0],GL_STATIC_DRAW);

    //Ahora falta calcular el vector de Indices
    vector<int> ind;
    for(int j = 0; j<obj.faces().size(); ++j) {
        int first, last, next;
        Face face = obj.faces()[j];
        first = face.vertexIndex(0);
        last = face.vertexIndex(1);
        next = face.vertexIndex(2);
        ind.push_back(first); ind.push_back(last); ind.push_back(next);
        for(int l = 3; l<face.numVertices(); ++l) {
            last = next;
            next = face.vertexIndex(l);
            ind.push_back(first); ind.push_back(last); ind.push_back(next);
        }
    }
    /* ind = array de indices */
    GLuint auxID2[1];
    glGenBuffers(1, auxID2);
    ids.push_back(auxID2[0]);
    tamI.push_back(ind.size());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, auxID2[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size()*sizeof(int), (void*)&ind[0], GL_STATIC_DRAW);
}

Q_EXPORT_PLUGIN2(drawvboflat, DrawVBOFlat)   // plugin name, plugin class
