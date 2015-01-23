#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <ui_MainWindow.h>
#include <QtGui/qmainwindow.h>

class MainView
{
public:
   MainView();
   virtual ~MainView();
   
   virtual void show();
   
private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;

};

#endif
