#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <glm/glm.hpp>

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

   void setCamera(glm::vec3);
   void setTranslation(glm::vec3);
   void setRotation(glm::vec3);
   void setFOV(double fov);
   void setScale(double scale);
   void setSpecularPower(double power);
   void setAlbedo(glm::vec3);
   void setAmbient(glm::vec3);
   void setDiffuse(glm::vec3);

protected:
   virtual void paintGL();
   virtual void resizeGL(int w, int h);
   virtual void initializeGL();

private:
   void setupRenderingContext();
   bool loadShaderFile(const char *filename, GLuint shader);
   void loadAllShaders();

// Public for convinience of not writing getters. MUST set with setter cause it calls update
private:
   QOpenGLVertexArrayObject* qVAO_;
   QVector<GLfloat>* vertices_;
   QVector<GLshort>* indices_;
   QVector<GLfloat>* normals_;

public:
   glm::vec3 cameraPosition_;
   glm::vec3 translation_;
   glm::vec3 rotation_;
   float fov_;
   float scale_;
   float power_;
   glm::vec3 albedo_;
   glm::vec3 ambient_;
   glm::vec3 diffuse_;
};

#endif /* GLWIDGET_H_ */
