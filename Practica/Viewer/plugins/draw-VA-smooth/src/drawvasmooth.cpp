#include "drawvasmooth.h"
#include "glwidget.h"

void DrawVASmooth::drawScene()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    //Per cada vertex array que tinguem guardat
    for(int i = 0; i<vertices.size(); ++i) {
        //Creem el vertex array real
        glVertexPointer(3, GL_FLOAT, 0, (void *) &vertices[i][0]);
        glNormalPointer(GL_FLOAT, 0, (void *) &normals[i][0]);

        glDrawElements(GL_TRIANGLES, indices[i].size(), GL_UNSIGNED_INT, (void *) &indices[i][0]);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawVASmooth::onPluginLoad() {
    Scene* scene = pglwidget->scene();
    //Per cada objecte de l'escena
    for(int i = 0; i<scene->objects().size(); ++i) {
        Object obj = scene->objects()[i];
        //Guardem els vertexs de l'objecte a l'ultima posicio de "vertices"
        vertices.push_back(obj.vertices());
        //Redimensionem normals, que tindra la mateixa mida que vertices i posem tot a zero
        normals.push_back(obj.vertices());
        cont = vector<int>(normals[i].size(), 0);
        Point p; p.setX(0); p.setY(0); p.setZ(0);
        for(int j=0; j<normals[i].size(); ++j) normals[i][j].setCoord(p);
        //Per cada cara mirem a quins vertexs pertany la normal
        for(int j = 0; j<obj.faces().size(); ++j) {
            Face face = obj.faces()[j];
            //Per cada vertex de la cara mirem a quina posicio correspont de "vertices" i sumem la normal e incrementem
            //el vector de contadors
            for(int l = 0; l<face.numVertices(); ++l) {
                Point q;
                q.setX(normals[i][face.vertexIndex(l)].coord().x()+face.normal().x());
                q.setX(normals[i][face.vertexIndex(l)].coord().y()+face.normal().y());
                q.setX(normals[i][face.vertexIndex(l)].coord().z()+face.normal().z());
                normals[i][face.vertexIndex(l)] = q;
                cont[face.vertexIndex(l)]++;
            }
        }
        vector<int> ind;
        //Per cada cara s'ha de mirar de calcular tots els indexos possibles que tindrem
        for(int j = 0; j<obj.faces().size(); ++j) {
            int first, last, next;
            Face face = obj.faces()[j];
            first = face.vertexIndex(0);
            last = face.vertexIndex(1);
            next = face.vertexIndex(2);
            //Creem tots el triangles possibles de una cara
            ind.push_back(first); ind.push_back(last); ind.push_back(next);
            for(int l = 3; l<face.numVertices(); ++l) {
                last = next;
                next = face.vertexIndex(l);
                ind.push_back(first); ind.push_back(last); ind.push_back(next);
            }
        }
        indices.push_back(ind);
        //Calculem les noves normals
        for(int j = 0; j<normals[i].size(); ++j) {
            Point q;
            q.setX(normals[i][j].coord().x()/cont[j]);
            q.setY(normals[i][j].coord().y()/cont[j]);
            q.setZ(normals[i][j].coord().z()/cont[j]);
            normals[i][j] = q;
        }
    }
}

void DrawVASmooth::onObjectAdd() {
    Scene* scene = pglwidget->scene();

    Object obj = scene->objects()[scene->objects().size()-1];
    //Guardem els vertexs de l'objecte a l'ultima posicio de "vertices"
    vertices.push_back(obj.vertices());
    //Redimensionem normals, que tindra la mateixa mida que vertices i posem tot a zero
    normals.push_back(obj.vertices());
    cont = vector<int>(normals[scene->objects().size()-1].size(), 0);
    Point p; p.setX(0); p.setY(0); p.setZ(0);
    for(int j=0; j<normals[scene->objects().size()-1].size(); ++j) normals[scene->objects().size()-1][j].setCoord(p);
    //Per cada cara mirem a quins vertexs pertany la normal
    for(int j = 0; j<obj.faces().size(); ++j) {
        Face face = obj.faces()[j];
        //Per cada vertex de la cara mirem a quina posicio correspont de "vertices" i sumem la normal e incrementem
        //el vector de contadors
        for(int l = 0; l<face.numVertices(); ++l) {
            Point q;
            q.setX(normals[scene->objects().size()-1][face.vertexIndex(l)].coord().x()+face.normal().x());
            q.setX(normals[scene->objects().size()-1][face.vertexIndex(l)].coord().y()+face.normal().y());
            q.setX(normals[scene->objects().size()-1][face.vertexIndex(l)].coord().z()+face.normal().z());
            normals[scene->objects().size()-1][face.vertexIndex(l)] = q;
            cont[face.vertexIndex(l)]++;
        }
    }
    vector<int> ind;
    //Per cada cara s'ha de mirar de calcular tots els indexos possibles que tindrem
    for(int j = 0; j<obj.faces().size(); ++j) {
        int first, last, next;
        Face face = obj.faces()[j];
        first = face.vertexIndex(0);
        last = face.vertexIndex(1);
        next = face.vertexIndex(2);
        //Creem tots el triangles possibles de una cara
        ind.push_back(first); ind.push_back(last); ind.push_back(next);
        for(int l = 3; l<face.numVertices(); ++l) {
            last = next;
            next = face.vertexIndex(l);
            ind.push_back(first); ind.push_back(last); ind.push_back(next);
        }
    }
    indices.push_back(ind);
    //Calculem les noves normals
    for(int j = 0; j<normals[scene->objects().size()-1].size(); ++j) {
        Point q;
        q.setX(normals[scene->objects().size()-1][j].coord().x()/cont[j]);
        q.setY(normals[scene->objects().size()-1][j].coord().y()/cont[j]);
        q.setZ(normals[scene->objects().size()-1][j].coord().z()/cont[j]);
        normals[scene->objects().size()-1][j] = q;
    }
}

Q_EXPORT_PLUGIN2(drawvasmooth, DrawVASmooth)   // plugin name, plugin class
