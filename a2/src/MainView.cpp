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

   qtConnect(mainUi_->translateX, SIGNAL(valueChanged(int)),
             this, SLOT(translateX(int)));
   qtConnect(mainUi_->translateY, SIGNAL(valueChanged(int)),
             this, SLOT(translateY(int)));
   qtConnect(mainUi_->translateZ, SIGNAL(valueChanged(int)),
             this, SLOT(translateZ(int)));

   qtConnect(mainUi_->rotateX, SIGNAL(valueChanged(int)),
             this, SLOT(rotateX(int)));
   qtConnect(mainUi_->rotateY, SIGNAL(valueChanged(int)),
             this, SLOT(rotateY(int)));
   qtConnect(mainUi_->rotateZ, SIGNAL(valueChanged(int)),
             this, SLOT(rotateZ(int)));

   qtConnect(mainUi_->fovEntry, SIGNAL(valueChanged(double)),
             this, SLOT(changeFOV(double)));

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

void MainView::translateX(int x)
{
   scene_->setTranslateX(x);
}

void MainView::translateY(int y)
{
   scene_->setTranslateY(y);
}

void MainView::translateZ(int z)
{
   scene_->setTranslateZ(z);
}

void MainView::rotateX(int x)
{
   scene_->setRotateX(x);
}

void MainView::rotateY(int y)
{
   scene_->setRotateY(y);
}

void MainView::rotateZ(int z)
{
   scene_->setRotateZ(z);
}

void MainView::changeFOV(double fov)
{
   scene_->setFOV(fov);
}



void MainView::createGlWidget(QVector<GLfloat>* vertices, QVector<GLfloat>* normals)
{
   scene_ = new GlWidget(mainWindow_, vertices, normals);
   layout_->addWidget(scene_);
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


   layout_ = new QVBoxLayout(mainUi_->containerWidget);
   mainUi_->containerWidget->setLayout(layout_);
}



