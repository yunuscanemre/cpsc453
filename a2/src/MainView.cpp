#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <glm/glm.hpp>

#include <Helpers.h>

MainView::MainView()
{
   scene_ = NULL;
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

   qtConnect(mainUi_->gold, SIGNAL(clicked()),
             this, SLOT(makeGold()));

   qtConnect(mainUi_->chrome, SIGNAL(clicked()),
             this, SLOT(makeChrome()));

   qtConnect(mainUi_->copper, SIGNAL(clicked()),
             this, SLOT(makeCopper()));

   qtConnect(mainUi_->plastic, SIGNAL(clicked()),
             this, SLOT(makePlastic()));

   qtConnect(mainUi_->drawFloor, SIGNAL(stateChanged(int)),
             this, SLOT(drawFloor(int)));

   qtConnect(mainUi_->actionExit, SIGNAL(triggered(bool)),
             this, SIGNAL(exitSelected(bool)));
   qtConnect(mainUi_->actionNewModel, SIGNAL(triggered(bool)),
             this, SIGNAL(loadNewModel(bool)));

}

MainView::~MainView()
{
}

void MainView::drawFloor(int shouldDraw)
{
   scene_->drawFloor((bool) shouldDraw);
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

void MainView::makeGold()
{
   scene_->setAmbient(glm::vec3(0.24725, 0.1995, 0.0745));
   scene_->setDiffuse(glm::vec3(0.75164, 0.60648, 0.22648));
   scene_->setAlbedo(glm::vec3(0.628281, 0.555802, 0.366065));
   scene_->setSpecularPower(51.2);
   syncEntriesToCurrentValues();
}

void MainView::makeChrome()
{
   scene_->setAmbient(glm::vec3(0.254));
   scene_->setDiffuse(glm::vec3(0.44));
   scene_->setAlbedo(glm::vec3(0.7745974));
   scene_->setSpecularPower(76.8);
   syncEntriesToCurrentValues();
}

void MainView::makeCopper()
{
   scene_->setAmbient(glm::vec3(0.19125, 0.0735, 0.0225));
   scene_->setDiffuse(glm::vec3(0.7038, 0.27048, 0.0828));
   scene_->setAlbedo(glm::vec3(0.256777, 0.137622, 0.086014));
   scene_->setSpecularPower(12.8);
   syncEntriesToCurrentValues();
}

void MainView::makePlastic()
{
   scene_->setAmbient(glm::vec3(0.0));
   scene_->setDiffuse(glm::vec3(0.01));
   scene_->setAlbedo(glm::vec3(0.5));
   scene_->setSpecularPower(32);
   syncEntriesToCurrentValues();
}

void MainView::syncEntriesToCurrentValues()
{
   mainUi_->cameraX->blockSignals(true);
   mainUi_->cameraX->setValue(scene_->cameraPosition_.x);
   mainUi_->cameraX->blockSignals(false);
   mainUi_->cameraY->blockSignals(true);
   mainUi_->cameraY->setValue(scene_->cameraPosition_.y);
   mainUi_->cameraY->blockSignals(false);
   mainUi_->cameraZ->blockSignals(true);
   mainUi_->cameraZ->setValue(scene_->cameraPosition_.z);
   mainUi_->cameraZ->blockSignals(false);
   mainUi_->translateX->blockSignals(true);
   mainUi_->translateX->setValue(scene_->translation_.x);
   mainUi_->translateX->blockSignals(false);
   mainUi_->translateY->blockSignals(true);
   mainUi_->translateY->setValue(scene_->translation_.y);
   mainUi_->translateY->blockSignals(false);
   mainUi_->translateZ->blockSignals(true);
   mainUi_->translateZ->setValue(scene_->translation_.z);
   mainUi_->translateZ->blockSignals(false);
   mainUi_->rotateX->blockSignals(true);
   mainUi_->rotateX->setValue(scene_->rotation_.x);
   mainUi_->rotateX->blockSignals(false);
   mainUi_->rotateY->blockSignals(true);
   mainUi_->rotateY->setValue(scene_->rotation_.y);
   mainUi_->rotateY->blockSignals(false);
   mainUi_->rotateZ->blockSignals(true);
   mainUi_->rotateZ->setValue(scene_->rotation_.z);
   mainUi_->rotateZ->blockSignals(false);
   mainUi_->ambientX->blockSignals(true);
   mainUi_->ambientX->setValue(scene_->ambient_.x);
   mainUi_->ambientX->blockSignals(false);
   mainUi_->ambientY->blockSignals(true);
   mainUi_->ambientY->setValue(scene_->ambient_.y);
   mainUi_->ambientY->blockSignals(false);
   mainUi_->ambientZ->blockSignals(true);
   mainUi_->ambientZ->setValue(scene_->ambient_.z);
   mainUi_->ambientZ->blockSignals(false);
   mainUi_->albedoX->blockSignals(true);
   mainUi_->albedoX->setValue(scene_->albedo_.x);
   mainUi_->albedoX->blockSignals(false);
   mainUi_->albedoY->blockSignals(true);
   mainUi_->albedoY->setValue(scene_->albedo_.y);
   mainUi_->albedoY->blockSignals(false);
   mainUi_->albedoZ->blockSignals(true);
   mainUi_->albedoZ->setValue(scene_->albedo_.z);
   mainUi_->albedoZ->blockSignals(false);
   mainUi_->diffuseX->blockSignals(true);
   mainUi_->diffuseX->setValue(scene_->diffuse_.x);
   mainUi_->diffuseX->blockSignals(false);
   mainUi_->diffuseY->blockSignals(true);
   mainUi_->diffuseY->setValue(scene_->diffuse_.y);
   mainUi_->diffuseY->blockSignals(false);
   mainUi_->diffuseZ->blockSignals(true);
   mainUi_->diffuseZ->setValue(scene_->diffuse_.z);
   mainUi_->diffuseZ->blockSignals(false);
   mainUi_->fovEntry->blockSignals(true);
   mainUi_->fovEntry->setValue(scene_->fov_);
   mainUi_->fovEntry->blockSignals(false);
   mainUi_->scaleEntry->blockSignals(true);
   mainUi_->scaleEntry->setValue(scene_->scale_);
   mainUi_->scaleEntry->blockSignals(false);
   mainUi_->powerEntry->blockSignals(true);
   mainUi_->powerEntry->setValue(scene_->power_);
   mainUi_->powerEntry->blockSignals(false);
}

void MainView::createGlWidget(QVector<GLfloat>* vertices, QVector<GLshort>* indices, QVector<GLfloat>* normals)
{
   if(scene_ != NULL)
   {
      deletePointer(scene_);
      layout_->removeWidget(scene_);
   }
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



