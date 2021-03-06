#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QObject>
#include <QtOpenGL/qgl.h>

class RgbImage;

class GlWidget : public QGLWidget
{
   Q_OBJECT

public:
   GlWidget(QWidget *parent);

   void drawRgbImage(RgbImage* image);
//   void rotateImage(int degrees);

protected:
   virtual void paintGL();
   virtual void resizeGL(int w, int h);
   virtual void initializeGL();
};

#endif /* GLWIDGET_H_ */
