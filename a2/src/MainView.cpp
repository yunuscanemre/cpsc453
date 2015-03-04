#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <glm/glm.hpp>

#include <Helpers.h>

MainView::MainView()
{
   setupUi();

   // Camera
   qtConnect(mainUi_->cameraX, SIGNAL(valueChanged(double)),
             this, SLOT(updateCamera()));
   qtConnect(mainUi_->cameraY, SIGNAL(valueChanged(double)),
             this, SLOT(updateCamera()));
   qtConnect(mainUi_->cameraZ, SIGNAL(valueChanged(double)),
             this, SLOT(updateCamera()));
   qtConnect(mainUi_->fovEntry, SIGNAL(valueChanged(double)),
             this, SLOT(updateFov(double)));

   // Model
   qtConnect(mainUi_->translateX, SIGNAL(valueChanged(double)),
             this, SLOT(updateTranslation()));
   qtConnect(mainUi_->translateY, SIGNAL(valueChanged(double)),
             this, SLOT(updateTranslation()));
   qtConnect(mainUi_->translateZ, SIGNAL(valueChanged(double)),
             this, SLOT(updateTranslation()));

   qtConnect(mainUi_->rotateX, SIGNAL(valueChanged(int)),
             this, SLOT(updateRotation()));
   qtConnect(mainUi_->rotateY, SIGNAL(valueChanged(int)),
             this, SLOT(updateRotation()));
   qtConnect(mainUi_->rotateZ, SIGNAL(valueChanged(int)),
             this, SLOT(updateRotation()));

   qtConnect(mainUi_->scaleEntry, SIGNAL(valueChanged(double)),
             this, SLOT(updateScale(double)));

   // Lighting/Material
   qtConnect(mainUi_->powerEntry, SIGNAL(valueChanged(double)),
             this, SLOT(updateSpecularPower(double)));

   qtConnect(mainUi_->albedoX, SIGNAL(valueChanged(double)),
             this, SLOT(updateAlbedo()));
   qtConnect(mainUi_->albedoY, SIGNAL(valueChanged(double)),
             this, SLOT(updateAlbedo()));
   qtConnect(mainUi_->albedoZ, SIGNAL(valueChanged(double)),
             this, SLOT(updateAlbedo()));

   qtConnect(mainUi_->ambientX, SIGNAL(valueChanged(double)),
             this, SLOT(updateAmbient()));
   qtConnect(mainUi_->ambientY, SIGNAL(valueChanged(double)),
             this, SLOT(updateAmbient()));
   qtConnect(mainUi_->ambientZ, SIGNAL(valueChanged(double)),
             this, SLOT(updateAmbient()));

   qtConnect(mainUi_->diffuseX, SIGNAL(valueChanged(double)),
             this, SLOT(updateDiffuse()));
   qtConnect(mainUi_->diffuseY, SIGNAL(valueChanged(double)),
             this, SLOT(updateDiffuse()));
   qtConnect(mainUi_->diffuseZ, SIGNAL(valueChanged(double)),
             this, SLOT(updateDiffuse()));

   qtConnect(mainUi_->actionExit, SIGNAL(triggered(bool)),
             this, SIGNAL(exitSelected(bool)));

}

MainView::~MainView()
{
}

void MainView::updateCamera()
{
   scene_->setCamera(glm::vec3(mainUi_->cameraX->value(),
                               mainUi_->cameraY->value(),
                               mainUi_->cameraZ->value()));
}

void MainView::setCameraPosition(glm::vec3 position)
{
   scene_->setCamera(position);
}

void MainView::updateTranslation()
{
   scene_->setTranslation(glm::vec3(mainUi_->translateX->value(),
                                    mainUi_->translateY->value(),
                                    mainUi_->translateZ->value()));
}

void MainView::setTranslation(glm::vec3 translation)
{
   scene_->setTranslation(translation);
}

void MainView::updateRotation()
{
   scene_->setRotation(glm::vec3(mainUi_->rotateX->value(),
                                 mainUi_->rotateY->value(),
                                 mainUi_->rotateZ->value()));
}

void MainView::updateFov(double fov)
{
   scene_->setFOV(fov);
}

void MainView::updateScale(double scale)
{
   scene_->setScale(scale);
}

void MainView::updateSpecularPower(double power)
{
   scene_->setSpecularPower(power);
}

void MainView::updateAlbedo()
{
   scene_->setAlbedo(glm::vec3(mainUi_->albedoX->value(),
                               mainUi_->albedoY->value(),
                               mainUi_->albedoZ->value()));
}

void MainView::updateAmbient()
{
   scene_->setAmbient(glm::vec3(mainUi_->ambientX->value(),
                                mainUi_->ambientY->value(),
                                mainUi_->ambientZ->value()));
}

void MainView::updateDiffuse()
{
   scene_->setDiffuse(glm::vec3(mainUi_->diffuseX->value(),
                                mainUi_->diffuseY->value(),
                                mainUi_->diffuseZ->value()));
}

void MainView::createGlWidget(QVector<GLfloat>* vertices, QVector<GLshort>* indices, QVector<GLfloat>* normals)
{
   scene_ = new GlWidget(mainWindow_, vertices, indices, normals);
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



