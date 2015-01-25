#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <RgbImage.h>

#include <Helpers.h>

MainView::MainView() 
{
   setupUi();

   qtConnect(mainUi_->quantizationEntry, SIGNAL(valueChanged(int)),
             this, SIGNAL(quantizationChanged(int)));

   qtConnect(mainUi_->actionOpenImage, SIGNAL(triggered(bool)),
             this, SIGNAL(openImageSelected(bool)));

   qtConnect(mainUi_->actionSaveImage, SIGNAL(triggered(bool)),
             this, SIGNAL(saveImageSelected(bool)));
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
   original_->loadImage(image);
   modified_->updateGL();
}

void MainView::setModifiedImage(RgbImage* image)
{
   modified_->makeCurrent();
   modified_->loadImage(image);
   modified_->updateGL();
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
   mainUi_->quantizationEntry->
      setStatusTip("Sets quantization level. Hit enter for changes to take effect.");
}



