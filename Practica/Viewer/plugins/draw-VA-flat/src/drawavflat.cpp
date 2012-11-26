#include "drawvaflat.h"
#include "glwidget.h"

void DrawVAFlat::drawScene()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	for(int i = 0; i<numVA; ++i) {
		glDrawArrays(GL_TRIANGLES, 0, va[numVa]);
	}
}

void DrawVAFlat::onPluginLoad() {
	Scene* scene = pglwidget->scene();
	for(unsigned int i=0; i<scene->objects().size(); ++i) {
		glVertexPointer(3, GL_FLOAT, 0, va[i]);
		numVA = i;
	}
}

void DrawVAFlat::onObjectAdd() {
	Scene* scene = pglwidget->scene();
	for(unsigned int i=0; i<scene->objects().size(); ++i) {
		glVertexPointer(3, GL_FLOAT, 0, va[i]);
		numVA = i;
	}
}

Q_EXPORT_PLUGIN2(drawvaflat, DrawVAFlat)   // plugin name, plugin class
