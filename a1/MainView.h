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
   void setOrigImage(RgbImage* image);
   void setModifiedImage(RgbImage* image);
   void enableDissolve();
   
signals:
   void quantizationChanged(int level);
   void brightnessChanged(double scale);
   void saturationChanged(double scale);
   void scaleChanged(int scale);
   void contrastChanged(double scale);
   void dissolveChanged(double distance);

   void openImageSelected(bool checked);
   void saveImageSelected(bool checked);
   void dissolveSelected(bool checked);

private:
   void setupUi();

private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* original_;
   GlWidget* modified_;



};

#endif
