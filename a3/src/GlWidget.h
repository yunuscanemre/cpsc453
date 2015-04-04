#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QObject>
#include <QtOpenGL/qgl.h>
#include <QLabel>
#include <QPixmap>

class QResizeEvent;

class GlWidget : public QLabel
{
   Q_OBJECT

public:
   GlWidget(QWidget *parent);

//   void setImage(QPixmap image);
//   void rotateImage(int degrees);

protected:
//   virtual void paintGL();
   virtual void resizeEvent(QResizeEvent* event);

private:
//   QLabel l;
//   QPixmap p;
//   bool img;
};

#endif /* GLWIDGET_H_ */
