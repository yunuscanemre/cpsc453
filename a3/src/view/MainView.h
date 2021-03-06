#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <QObject>
#include <ui_MainWindow.h>
#include <QImage>
#include <glm/glm.hpp>

class GlWidget;
class QMainWindow;
class RgbImage;

class MainView : public QObject
{
   Q_OBJECT

public:
   MainView();
   virtual ~MainView();
   
   void show();
   void setImage(QImage image);

   glm::vec3 getCamera();

signals:
   void saveImageSelected(bool checked);
   void exitSelected(bool checked);
   void updateCamera();

private:
   void setupUi();

private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* glwidget_;
};

#endif
