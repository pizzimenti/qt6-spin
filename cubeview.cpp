#include "cubeview.h"
#include <QTimerEvent>

CubeView::CubeView(QWidget *parent) :
    QOpenGLWidget(parent),
    vbo(QOpenGLBuffer::VertexBuffer),
    rotationAxis(0.0, 1.0, 0.0),
    angularSpeed(360.0f / 7000.0f) { // One full rotation in 7 seconds
}

CubeView::~CubeView() {
    makeCurrent();
    vbo.destroy();
    doneCurrent();
}

void CubeView::initializeGL() {
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode

    // Clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    // Shader setup
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    program.link();
    program.bind();

    // Cube setup
    GLfloat vertices[] = {
        // Front face
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,

        // Back face
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,

        // Top face
        -1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0,  1.0,
         1.0,  1.0, -1.0,

        // Bottom face
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0, -1.0,  1.0,
        -1.0, -1.0,  1.0,

        // Right face
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0,  1.0,  1.0,
         1.0, -1.0,  1.0,

        // Left face
        -1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
        -1.0, -1.0,  1.0,
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, 24 * sizeof(GLfloat));

    // Timer setup
    startTimer(20);
}

void CubeView::resizeGL(int w, int h) {
    projection.setToIdentity();
    projection.perspective(60.0f, w / float(h), 0.1f, 100.0f);
}

void CubeView::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup the camera matrix
    QMatrix4x4 cameraMatrix;
    cameraMatrix.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

    program.bind();
    program.setUniformValue("projMatrix", projection);
    QMatrix4x4 rotationMatrix4x4;
    rotationMatrix4x4.rotate(rotation);
    program.setUniformValue("mvMatrix", cameraMatrix * rotationMatrix4x4);

    program.setUniformValue("normalMatrix", cameraMatrix.normalMatrix());

    // Draw cube
    glEnableVertexAttribArray(0);
    vbo.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(0);
}

void CubeView::timerEvent(QTimerEvent *) {
    // Update rotation
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

    // Update widget
    update();
}
