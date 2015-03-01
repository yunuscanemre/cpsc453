#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>

#include <Helpers.h>

MainView::MainView() 
{
   setupUi();

   qtConnect(mainUi_->cameraX, SIGNAL(valueChanged(int)),
             this, SLOT(changeCamera()));
   qtConnect(mainUi_->cameraY, SIGNAL(valueChanged(int)),
             this, SLOT(changeCamera()));
   qtConnect(mainUi_->cameraZ, SIGNAL(valueChanged(int)),
             this, SLOT(changeCamera()));

   qtConnect(mainUi_->translateX, SIGNAL(valueChanged(int)),
             this, SLOT(changeTranslation()));
   qtConnect(mainUi_->translateY, SIGNAL(valueChanged(int)),
             this, SLOT(changeTranslation()));
   qtConnect(mainUi_->translateZ, SIGNAL(valueChanged(int)),
             this, SLOT(changeTranslation()));

   qtConnect(mainUi_->rotateX, SIGNAL(valueChanged(int)),
             this, SLOT(changeRotation()));
   qtConnect(mainUi_->rotateY, SIGNAL(valueChanged(int)),
             this, SLOT(changeRotation()));
   qtConnect(mainUi_->rotateZ, SIGNAL(valueChanged(int)),
             this, SLOT(changeRotation()));

   qtConnect(mainUi_->fovEntry, SIGNAL(valueChanged(double)),
             this, SLOT(changeFOV(double)));

   qtConnect(mainUi_->actionExit, SIGNAL(triggered(bool)),
             this, SIGNAL(exitSelected(bool)));

}

MainView::~MainView() 
{
}

void MainView::changeCamera()
{
   scene_->setCamera(mainUi_->cameraX->value(),
                     mainUi_->cameraY->value(),
                     mainUi_->cameraZ->value());
}

void MainView::changeTranslation()
{
   scene_->setTranslation(mainUi_->translateX->value(),
                          mainUi_->translateY->value(),
                          mainUi_->translateZ->value());
}

void MainView::changeRotation()
{
   scene_->setRotation(mainUi_->rotateX->value(),
                       mainUi_->rotateY->value(),
                       mainUi_->rotateZ->value());
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



