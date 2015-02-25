#include <GlWidget.h>
#include <QWidget>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

GlWidget::GlWidget(QWidget *parent) : QGLWidget(parent)
{
}

void GlWidget::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glBegin(GL_QUADS);

   glTexCoord2f(0.0, 0.0);
   glVertex3f(-1.0, -1.0, 0.0);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(-1.0, 1.0, 0.0);

   glTexCoord2f(1.0, 1.0);
   glVertex3f(1.0, 1.0, 0.0);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(1.0, -1.0, 0.0);

   glEnd();

   glFlush();
   glDisable(GL_TEXTURE_2D);
}

void GlWidget::resizeGL(int w, int h)
{
   float viewWidth = 1.1;
   float viewHeight = 1.1;
   glViewport(0, 0, w, h);
   h = (h==0) ? 1 : h;
   w = (w==0) ? 1 : w;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if ( h < w ) {
       viewWidth *= (float)w/(float)h;
   }
   else {
       viewHeight *= (float)h/(float)w;
   }
   glOrtho( -viewWidth, viewWidth, -viewHeight, viewHeight, -1.0, 1.0 );

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void GlWidget::initializeGL()
{
}



