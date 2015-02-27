#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>

#include <Helpers.h>

MainView::MainView() 
{
   setupUi();

   qtConnect(mainUi_->cameraX, SIGNAL(valueChanged(int)),
             this, SLOT(changeCameraX(int)));
   qtConnect(mainUi_->cameraY, SIGNAL(valueChanged(int)),
             this, SLOT(changeCameraY(int)));
   qtConnect(mainUi_->cameraZ, SIGNAL(valueChanged(int)),
             this, SLOT(changeCameraZ(int)));
   qtConnect(mainUi_->actionExit, SIGNAL(triggered(bool)),
             this, SIGNAL(exitSelected(bool)));

}

MainView::~MainView() 
{
}

void MainView::changeCameraX(int x)
{
   scene_->setCameraX(x);
}

void MainView::changeCameraY(int y)
{
   scene_->setCameraY(y);
}

void MainView::changeCameraZ(int z)
{
   scene_->setCameraZ(z);
}

void MainView::show()
{
   mainWindow_->show();
}

void MainView::setupUi()
{
   mainWindow_ = new QMainWindow();
   mainUi_ = new Ui::MainWindow();
   mainUi_->setupUi(mainWindow_);

   scene_ = new GlWidget(mainWindow_);
   QVBoxLayout* layout = new QVBoxLayout(mainUi_->containerWidget);
   layout->addWidget(scene_);
   mainUi_->containerWidget->setLayout(layout);
}



