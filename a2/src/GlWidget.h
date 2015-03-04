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
   GlWidget(QWidget *parent,
            QVector<GLfloat>* vertices,
            QVector<GLshort>* indices,
            QVector<GLfloat>* normals);
   ~GlWidget();

   void setCamera(double x, double y, double z);
   void setTranslation(double x, double y, double z);
   void setRotation(int x, int y, int z);
   void setFOV(double fov);
   void setScale(double scale);
   void setSpecularPower(double power);
   void setAlbedo(double x, double y, double z);
   void setAmbient(double x, double y, double z);
   void setDiffuse(double x, double y, double z);

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
   float cameraX_;
   float cameraY_;
   float cameraZ_;
   float transX_;
   float transY_;
   float transZ_;
   float rotateX_;
   float rotateY_;
   float rotateZ_;
   float fov_;
   float scale_;
   float power_;
   float albedoX_;
   float albedoY_;
   float albedoZ_;
   float ambientX_;
   float ambientY_;
   float ambientZ_;
   float diffuseX_;
   float diffuseY_;
   float diffuseZ_;
   QVector<GLfloat>* vertices_;
   QVector<GLshort>* indices_;
   QVector<GLfloat>* normals_;
};

#endif /* GLWIDGET_H_ */
