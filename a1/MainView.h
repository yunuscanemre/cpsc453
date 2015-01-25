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
   
   virtual void show();
   virtual void setOrigImage(RgbImage* image);
   void setModifiedImage(RgbImage* image);
   
signals:
   void quantizationChanged(int level);
   void openImageSelected(bool checked);
   void saveImageSelected(bool checked);

private:
   void setupUi();

private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* original_;
   GlWidget* modified_;



};

#endif
