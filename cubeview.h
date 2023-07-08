#ifndef CUBEVIEW_H
#define CUBEVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class CubeView : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT

public:
    explicit CubeView(QWidget *parent = nullptr);
    ~CubeView();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *e) override;

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;

    QMatrix4x4 projection;

    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
};

#endif // CUBEVIEW_H
