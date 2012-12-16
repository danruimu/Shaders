#include "fraglight.h"

void FragLight::onPluginLoad() {
    QGLShader vs(QGLShader::Vertex);
    QGLShader fs(QGLShader::Fragment);

    QString vsFile = QFileDialog::getOpenFileName(NULL, "Select the vertex shader", "/home/dani/uni/G/Shaders/Practica/Viewer/plugins/frag-light/src/", "Vertex Shaders (*.vert)");
    QString fsFile = QFileDialog::getOpenFileName(NULL, "Select the fragment shader", "/home/dani/uni/G/Shaders/Practica/Viewer/plugins/frag-light/src/", "Fragment Shaders (*.frag)");

    vs.compileSourceFile(vsFile);
    fs.compileSourceFile(fsFile);

    ShaderProgram.addShader(&vs);
    ShaderProgram.addShader(&fs);

    ShaderProgram.link();
}

void FragLight::preFrame() {
    ShaderProgram.bind();
}

void FragLight::postFrame() {
    ShaderProgram.release();
}

Q_EXPORT_PLUGIN2(fraglight, FragLight)   // plugin name, plugin class
