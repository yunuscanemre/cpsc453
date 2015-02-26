#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
   Q_OBJECT

public:
   GlWidget(QWidget *parent);

protected:
   virtual void paintGL();
   virtual void resizeGL(int w, int h);
   virtual void initializeGL();

private:
   void setupRenderingContext();
   bool loadShaderFile(const char *filename, GLuint shader);

};

#endif /* GLWIDGET_H_ */
