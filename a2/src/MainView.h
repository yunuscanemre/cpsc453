#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <QObject>
#include <ui_MainWindow.h>
#include <QVector>
#include <GL/gl.h>
#include <glm/glm.hpp>

class GlWidget;
class QMainWindow;
class RgbImage;
class QVBoxLayout;

class MainView : public QObject
{
   Q_OBJECT

public:
   MainView();
   virtual ~MainView();

   void createGlWidget(QVector<GLfloat>* vertices, QVector<GLshort>* indices, QVector<GLfloat>* normals);
   void show();

   void setCameraPosition(glm::vec3 position);
   void setTranslation(glm::vec3 translation);

signals:
   void exitSelected(bool);

private slots:
   void updateCamera();

   void updateTranslation();
   void updateRotation();
   void updateFov(double fov);
   void updateScale(double scale);
   void updateSpecularPower(double power);
   void updateAlbedo();
   void updateAmbient();
   void updateDiffuse();

private:
   void setupUi();

private:
   QMainWindow* mainWindow_;
   Ui::MainWindow* mainUi_;
   GlWidget* scene_;
   QVBoxLayout* layout_;
};

#endif
