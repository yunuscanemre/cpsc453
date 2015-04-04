#include <GlWidget.h>
#include <QImage>
#include <QWidget>
#include <stdlib.h>
#include <QResizeEvent>

GlWidget::GlWidget(QWidget *parent) : QLabel(parent)
{
//   img = false;
}

//void GlWidget::setImage(QPixmap image)
//{
//   p = image;
//   l.setPixmap(p);
//   img = true;
//}

//void GlWidget::paintGL()
//{
//
//}

void GlWidget::resizeEvent(QResizeEvent* event)
{
//   const QPixmap* p = pixmap();
//   if(p != NULL)
//   {
//      int w = this->width();
//      int h = this->height();
//      setPixmap(p->scaled(w, h, Qt::KeepAspectRatioByExpanding));
//   }
//   fprintf(stderr, "here %d, %d\n", event->size().width(), event->size().height());
//   QLabel::resizeEvent(event);
}




