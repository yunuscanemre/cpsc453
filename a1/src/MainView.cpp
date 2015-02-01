#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <RgbImage.h>

#include <Helpers.h>

const QString TIP =
      "Hit enter for changes to take effect. You can scroll through values.";

MainView::MainView() 
{
   setupUi();

   qtConnect(mainUi_->quantizationEntry, SIGNAL(valueChanged(int)),
             this, SIGNAL(quantizationChanged(int)));

   qtConnect(mainUi_->brightnessEntry, SIGNAL(valueChanged(double)),
             this, SIGNAL(brightnessChanged(double)));

   qtConnect(mainUi_->saturationEntry, SIGNAL(valueChanged(double)),
             this, SIGNAL(saturationChanged(double)));

   qtConnect(mainUi_->scaleEntry, SIGNAL(valueChanged(int)),
             this, SIGNAL(scaleChanged(int)));

   qtConnect(mainUi_->rotationEntry, SIGNAL(valueChanged(int)),
             this, SIGNAL(rotationChanged(int)));

   qtConnect(mainUi_->contrastEntry, SIGNAL(valueChanged(double)),
             this, SIGNAL(contrastChanged(double)));

   qtConnect(mainUi_->dissolveEntry, SIGNAL(valueChanged(double)),
             this, SIGNAL(dissolveChanged(double)));

   qtConnect(mainUi_->dissolveSelect, SIGNAL(clicked(bool)),
                this, SIGNAL(dissolveSelected(bool)));

   qtConnect(mainUi_->actionOpenImage, SIGNAL(triggered(bool)),
             this, SIGNAL(openImageSelected(bool)));

   qtConnect(mainUi_->actionSaveImage, SIGNAL(triggered(bool)),
             this, SIGNAL(saveImageSelected(bool)));

   qtConnect(mainUi_->actionExit, SIGNAL(triggered(bool)),
             this, SIGNAL(exitSelected(bool)));
}

MainView::~MainView() 
{
}

void MainView::show()
{
   mainWindow_->show();
}

void MainView::setOrigImage(RgbImage* image)
{
   // opengl calls affect this widget
   original_->makeCurrent();
   original_->drawRgbImage(image);
   original_->updateGL();
}

void MainView::setModifiedImage(RgbImage* image)
{
   modified_->makeCurrent();
   modified_->drawRgbImage(image);
   modified_->updateGL();
}

void MainView::enableDissolve()
{
   mainUi_->dissolveEntry->setEnabled(true);
   mainUi_->dissolveEntry->setStatusTip(TIP);
}


void MainView::setupUi()
{
   mainWindow_ = new QMainWindow();
   mainUi_ = new Ui::MainWindow();
   mainUi_->setupUi(mainWindow_);
   modified_ = new GlWidget(mainWindow_);
   original_ = new GlWidget(mainWindow_);
   QVBoxLayout* origImgLayout = new QVBoxLayout(mainUi_->origImgContainerWidget);
   origImgLayout->addWidget(original_);
   mainUi_->origImgContainerWidget->setLayout(origImgLayout);

   QVBoxLayout* modImgLayout = new QVBoxLayout(mainUi_->modImgContainerWidget);
   modImgLayout->addWidget(modified_);
   mainUi_->modImgContainerWidget->setLayout(modImgLayout);

   mainUi_->quantizationEntry->setStatusTip(TIP);
   mainUi_->brightnessEntry->setStatusTip(TIP);
   mainUi_->saturationEntry->setStatusTip(TIP);
   mainUi_->scaleEntry->setStatusTip(TIP);
   mainUi_->rotationEntry->setStatusTip(TIP);
   mainUi_->contrastEntry->setStatusTip(TIP);
   mainUi_->dissolveSelect->setStatusTip(QString("Select image to dissolve to"));
   mainUi_->dissolveEntry->setStatusTip(QString("First select an image to dissolve to"));
}



