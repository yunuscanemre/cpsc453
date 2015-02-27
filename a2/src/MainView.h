#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <QObject>
#include <ui_MainWindow.h>
#include <QVector>
#include <GL/gl.h>

class GlWidget;
class QMainWindow;
class RgbImage;
class QVBoxLayout;

class MainView : public QObject
{
   Q_OBJECT

public:
   MainView();
   virtual ~MainView();

   void createGlWidget(QVector<GLfloat>* vertices);
   void show();

signals:
   void exitSelected(bool);

private slots:
void changeCameraX(int);
void changeCameraY(int);
void changeCameraZ(int);

void translateX(int);
void translateY(int);
void translateZ(int);

void rotateX(int);
void rotateY(int);
void rotateZ(int);

private:
   void setupUi();

private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* scene_;
   QVBoxLayout* layout_;
};

#endif
