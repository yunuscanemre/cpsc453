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

   void createGlWidget(QVector<GLfloat>* vertices, QVector<GLfloat>* normals);
   void show();

signals:
   void exitSelected(bool);

private slots:
   void changeCamera();
   void changeTranslation();
   void changeRotation();
   void changeFOV(double fov);
   void changeScale(double scale);

private:
   void setupUi();

private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* scene_;
   QVBoxLayout* layout_;
};

#endif
