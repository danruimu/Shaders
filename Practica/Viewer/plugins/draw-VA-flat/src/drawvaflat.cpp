#include "drawvaflat.h"
#include "glwidget.h"

void DrawVAFlat::drawScene()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    //Per cada vertex array que tinguem guardat
    for(int i = 0; i<vertices.size(); ++i) {
        //Creem el vertex array real
        glVertexPointer(3, GL_FLOAT, 0, (void *) &vertices[i][0]);
        glNormalPointer(GL_FLOAT, 0, (void *) &normals[i][0]);
        glColorPointer(4, GL_FLOAT, 0, (void *) &colors[i][0]);

        glDrawElements(GL_TRIANGLES, indices[i].size(), GL_UNSIGNED_INT, (void *) &indices[i][0]);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void DrawVAFlat::onPluginLoad() {
    Scene* scene = pglwidget->scene();
    MaterialLib* matlib = MaterialLib::instance();
    //Per cada objecte de l'escena
    for(int i = 0; i<scene->objects().size(); ++i) {
        Object obj = scene->objects()[i];
        //Guardem els vertexs de l'objecte a l'ultima posicio de "vertices"
        vertices.push_back(obj.vertices());
        //Redimensionem normals, que tindra la mateixa mida que vertices
        normals.push_back(obj.vertices());
        vector<Color> aux(normals[i].size());
        colors.push_back(aux);
        //Per cada cara mirem a quins vertexs pertany la normal i el color de la cara
        for(int j = 0; j<obj.faces().size(); ++j) {
            Face face = obj.faces()[j];
            Material m = matlib->material(face.materialIndex());
            //Per cada vertex de la cara mirem a quina posicio correspont de "vertices"
            for(int l = 0; l<face.numVertices(); ++l) {
                normals[i][face.vertexIndex(l)] = face.normal();
                colors[i][face.vertexIndex(l)] = m.ambient();
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
    }
}

void DrawVAFlat::onObjectAdd() {
    Scene* scene = pglwidget->scene();
    MaterialLib* matlib = MaterialLib::instance();
    Object obj = scene->objects()[scene->objects().size()-1];
    //Guardem els vertexs de l'objecte a l'ultima posicio de "vertices"
    vertices.push_back(obj.vertices());
    //Redimensionem normals, que tindra la mateixa mida que vertices
    normals.push_back(obj.vertices());
    vector<Color> aux(normals[scene->objects().size()-1].size());
    colors.push_back(aux);
    //Per cada cara mirem a quins vertexs pertany la normal
    for(int j = 0; j<obj.faces().size(); ++j) {
        Face face = obj.faces()[j];
        Material m = matlib->material(face.materialIndex());
        //Per cada vertex de la cara mirem a quina posicio correspont de "vertices"
        for(int l = 0; l<face.numVertices(); ++l) {
            normals[scene->objects().size()-1][face.vertexIndex(l)] = face.normal();
            colors[scene->objects().size()-1][face.vertexIndex(l)] = m.ambient();
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
}

Q_EXPORT_PLUGIN2(drawvaflat, DrawVAFlat)   // plugin name, plugin class
