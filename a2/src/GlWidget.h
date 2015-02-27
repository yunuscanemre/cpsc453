#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>

class QOpenGLVertexArrayObject;

class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
   Q_OBJECT

public:
   GlWidget(QWidget *parent, QVector<GLfloat>* vertices);
   ~GlWidget();

   void setCameraX(int x);
   void setCameraY(int y);
   void setCameraZ(int z);

protected:
   virtual void paintGL();
   virtual void resizeGL(int w, int h);
   virtual void initializeGL();

private:
   void setupRenderingContext();
   bool loadShaderFile(const char *filename, GLuint shader);
   void loadAllShaders();

private:
   QOpenGLVertexArrayObject* qVAO_;
   int cameraX_;
   int cameraY_;
   int cameraZ_;
   QVector<GLfloat>* vertices_;
};

#endif /* GLWIDGET_H_ */
