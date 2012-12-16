#include "drawvbosmooth.h"
#include "glwidget.h"

void DrawVBOSmooth::drawScene()
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

void DrawVBOSmooth::onPluginLoad() {
    Scene* scene = pglwidget->scene();
    MaterialLib* matlib = MaterialLib::instance();
    //Per cada objecte de l'escena
    for(int i = 0; i<scene->objects().size(); ++i) {
        Object obj = scene->objects()[i];
        vector<Vertex> v = obj.vertices();
        vector<Vertex> n = v;
        Point q; q.setX(0); q.setY(0); q.setZ(0);
        for(int a = 0; a<n.size(); ++a) {
            n[a].setCoord(q);
        }
        vector<int> cont(n.size(),0);
        vector<Color> c; c.resize(v.size());
        for(int j = 0; j<obj.faces().size(); ++j) {
            Face face = obj.faces()[j];
            Material m = matlib->material(face.materialIndex());
            for(int l = 0; l<face.numVertices(); ++l) {
                q.setX(n[face.vertexIndex(l)].coord().x()+face.normal().x());
                q.setY(n[face.vertexIndex(l)].coord().y()+face.normal().y());
                q.setZ(n[face.vertexIndex(l)].coord().z()+face.normal().z());
                n[face.vertexIndex(l)].setCoord(q);
                ++cont[face.vertexIndex(l)];

                c[face.vertexIndex(l)] = m.ambient();
            }
        }
        for(int j = 0; j<n.size(); ++j) {
            q.setX(n[j].coord().x()/cont[j]);
            q.setY(n[j].coord().y()/cont[j]);
            q.setZ(n[j].coord().z()/cont[j]);
            n[j].setCoord(q);
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

void DrawVBOSmooth::onObjectAdd() {
    Scene* scene = pglwidget->scene();
    MaterialLib* matlib = MaterialLib::instance();
    Object obj = scene->objects()[scene->objects().size()-1];
    vector<Vertex> v = obj.vertices();
    vector<Vertex> n = v;
    Point q; q.setX(0); q.setY(0); q.setZ(0);
    for(int a = 0; a<n.size(); ++a) {
        n[a].setCoord(q);
    }
    vector<int> cont(n.size(),0);
    vector<Color> c; c.resize(v.size());
    for(int j = 0; j<obj.faces().size(); ++j) {
        Face face = obj.faces()[j];
        Material m = matlib->material(face.materialIndex());
        for(int l = 0; l<face.numVertices(); ++l) {
            q.setX(n[face.vertexIndex(l)].coord().x()+face.normal().x());
            q.setY(n[face.vertexIndex(l)].coord().y()+face.normal().y());
            q.setZ(n[face.vertexIndex(l)].coord().z()+face.normal().z());
            n[face.vertexIndex(l)].setCoord(q);
            ++cont[face.vertexIndex(l)];

            c[face.vertexIndex(l)] = m.ambient();
        }
    }
    for(int j = 0; j<n.size(); ++j) {
        q.setX(n[j].coord().x()/cont[j]);
        q.setY(n[j].coord().y()/cont[j]);
        q.setZ(n[j].coord().z()/cont[j]);
        n[j].setCoord(q);
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

Q_EXPORT_PLUGIN2(drawvbosmooth, DrawVBOSmooth)   // plugin name, plugin class
