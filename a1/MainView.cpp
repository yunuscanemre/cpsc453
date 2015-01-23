#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <RgbImage.h>

MainView::MainView() 
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
   modified_->makeCurrent();
   modified_->loadImage(image);
}

