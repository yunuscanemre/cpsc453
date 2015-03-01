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
   GlWidget(QWidget *parent, QVector<GLfloat>* vertices, QVector<GLfloat>* normals);
   ~GlWidget();

   void setCameraX(int x);
   void setCameraY(int y);
   void setCameraZ(int z);

   void setTranslateX(int x);
   void setTranslateY(int y);
   void setTranslateZ(int z);

   void setRotateX(int x);
   void setRotateY(int y);
   void setRotateZ(int z);

   void setFOV(double fov);

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
   int transX_;
   int transY_;
   int transZ_;
   float rotateX_;
   float rotateY_;
   float rotateZ_;
   float fov_;
   QVector<GLfloat>* vertices_;
   QVector<GLfloat>* normals_;
};

#endif /* GLWIDGET_H_ */
