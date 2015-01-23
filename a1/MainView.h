#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <ui_MainWindow.h>

class GlWidget;
class QMainWindow;
class RgbImage;

class MainView
{
public:
   MainView();
   virtual ~MainView();
   
   virtual void show();
   virtual void setOrigImage(RgbImage* image);
   
private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* original_;
   GlWidget* modified_;

};

#endif
