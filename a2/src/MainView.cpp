#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>

#include <Helpers.h>

MainView::MainView()
{
   setupUi();

   // Camera
   qtConnect(mainUi_->cameraX, SIGNAL(valueChanged(int)),
             this, SLOT(changeCamera()));
   qtConnect(mainUi_->cameraY, SIGNAL(valueChanged(int)),
             this, SLOT(changeCamera()));
   qtConnect(mainUi_->cameraZ, SIGNAL(valueChanged(int)),
             this, SLOT(changeCamera()));
   qtConnect(mainUi_->fovEntry, SIGNAL(valueChanged(double)),
             this, SLOT(changeFOV(double)));

   // Model
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

   qtConnect(mainUi_->scaleEntry, SIGNAL(valueChanged(double)),
             this, SLOT(changeScale(double)));

   // Lighting/Material
   qtConnect(mainUi_->powerEntry, SIGNAL(valueChanged(double)),
             this, SLOT(changeSpecularPower(double)));

   qtConnect(mainUi_->albedoX, SIGNAL(valueChanged(double)),
             this, SLOT(changeAlbedo()));
   qtConnect(mainUi_->albedoY, SIGNAL(valueChanged(double)),
             this, SLOT(changeAlbedo()));
   qtConnect(mainUi_->albedoZ, SIGNAL(valueChanged(double)),
             this, SLOT(changeAlbedo()));

   qtConnect(mainUi_->ambientX, SIGNAL(valueChanged(double)),
             this, SLOT(changeAmbient()));
   qtConnect(mainUi_->ambientY, SIGNAL(valueChanged(double)),
             this, SLOT(changeAmbient()));
   qtConnect(mainUi_->ambientZ, SIGNAL(valueChanged(double)),
             this, SLOT(changeAmbient()));

   qtConnect(mainUi_->diffuseX, SIGNAL(valueChanged(double)),
             this, SLOT(changeDiffuse()));
   qtConnect(mainUi_->diffuseY, SIGNAL(valueChanged(double)),
             this, SLOT(changeDiffuse()));
   qtConnect(mainUi_->diffuseZ, SIGNAL(valueChanged(double)),
             this, SLOT(changeDiffuse()));

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

void MainView::changeScale(double scale)
{
   scene_->setScale(scale);
}

void MainView::changeSpecularPower(double power)
{
   scene_->setSpecularPower(power);
}

void MainView::changeAlbedo()
{
   scene_->setAlbedo(mainUi_->albedoX->value(),
                     mainUi_->albedoY->value(),
                     mainUi_->albedoZ->value());
}

void MainView::changeAmbient()
{
   scene_->setAmbient(mainUi_->ambientX->value(),
                      mainUi_->ambientY->value(),
                      mainUi_->ambientZ->value());
}

void MainView::changeDiffuse()
{
   scene_->setDiffuse(mainUi_->diffuseX->value(),
                      mainUi_->diffuseY->value(),
                      mainUi_->diffuseZ->value());
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



