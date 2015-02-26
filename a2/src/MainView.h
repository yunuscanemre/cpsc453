#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <QObject>
#include <ui_MainWindow.h>

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

signals:


private:
   void setupUi();

private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* scene_;
};

#endif
