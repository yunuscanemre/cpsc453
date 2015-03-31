#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <RgbImage.h>

#include <Helpers.h>

MainView::MainView() 
{
   setupUi();

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

void MainView::setImage(RgbImage* image)
{
   glwidget_->makeCurrent();
   glwidget_->drawRgbImage(image);
   glwidget_->updateGL();
}


void MainView::setupUi()
{
   mainWindow_ = new QMainWindow();
   mainUi_ = new Ui::MainWindow();
   mainUi_->setupUi(mainWindow_);
   glwidget_ = new GlWidget(mainWindow_);
   QVBoxLayout* imgLayout = new QVBoxLayout(mainUi_->imgContainerWidget);
   imgLayout->addWidget(glwidget_);
   mainUi_->imgContainerWidget->setLayout(imgLayout);

}



