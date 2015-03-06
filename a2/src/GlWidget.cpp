#include <GlWidget.h>
#include <QWidget>
#include <stdlib.h>
#include <iostream>
#include <Helpers.h>
#include <QOpenGLVertexArrayObject>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
// VAO and VBO to handle vertex state and data
GLuint vertexVbo;
GLuint normalVbo;
GLuint indiceVbo;

// shader program to use
GLuint myShaderProgram;

// Constants to help with location bindings
#define VERTEX_DATA 0
#define VERTEX_COLOUR 2
#define VERTEX_NORMAL 1
#define PI 3.14159265
//#define VERTEX_INDICES 3

GlWidget::GlWidget(QWidget *parent,
                   QVector<GLfloat>* vertices,
                   QVector<GLshort>* indices,
                   QVector<GLfloat>* normals) :
      QOpenGLWidget(parent),
      qVAO_(NULL),
      vertices_(vertices),
      indices_(indices),
      normals_(normals),
      cameraPosition_(0.0, 0.0, 2.613),
      translation_(0.0, 0.0, 0.0),
      rotation_(0.0, 0.0, 0.0),
      fov_(45),
      scale_(1),
      power_(1),
      albedo_(0.7, 0.7, 0.7),
      ambient_(0.1, 0.1, 0.1),
      diffuse_(0.5, 0.2, 0.7)
{
}

GlWidget::~GlWidget()
{
   qVAO_->destroy();
   deletePointer(qVAO_);
}

void GlWidget::paintGL()
{
   GLint modelViewMatrixID = glGetUniformLocation(myShaderProgram, "mv_matrix");
   GLint projMatrixID = glGetUniformLocation(myShaderProgram, "proj_matrix");
   GLint specularPowerID = glGetUniformLocation(myShaderProgram, "specular_power");
   GLint specularAlbedoID = glGetUniformLocation(myShaderProgram, "specular_albedo");
   GLint ambientID = glGetUniformLocation(myShaderProgram, "ambient");
   GLint diffuseAlbedoID = glGetUniformLocation(myShaderProgram, "diffuse_albedo");

   // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   glm::mat4 projMatrix = glm::perspective(fov_, 4.0f / 3.0f, 0.1f, 100.0f);

   // Camera matrix
   glm::mat4 viewMatrix = glm::lookAt(cameraPosition_, // Camera is at (X,Y,Z), in World Space
                                      glm::vec3(0, 0, 0), // and looks at the origin
                                      glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
                                     );

   // Model matrix : an identity matrix (model will be at the origin)
   glm::mat4 Model = glm::mat4(1.0f);

   // Scale Model
   Model = glm::scale(Model, glm::vec3(scale_));

   glm::mat4 xRotationMatrix = glm::rotate(Model, rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
   glm::mat4 yRotationMatrix = glm::rotate(Model, rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
   glm::mat4 zRotationMatrix = glm::rotate(Model, rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));

   // Rotate View
   Model = Model*xRotationMatrix;
   Model = Model*yRotationMatrix;
   Model = Model*zRotationMatrix;

   // Translate View
   glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation_);
   viewMatrix = viewMatrix*translationMatrix;

   glm::mat4 modelViewMatrix = viewMatrix * Model;

   // Clear the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(myShaderProgram);

   // Send our transformation to the currently bound shader,
   glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, &modelViewMatrix[0][0]);
   glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, &projMatrix[0][0]);

   glUniform1f(specularPowerID, power_);
   glUniform3fv(specularAlbedoID, 1, &albedo_[0]);
   glUniform3fv(ambientID, 1, &ambient_[0]);
   glUniform3fv(diffuseAlbedoID, 1, &diffuse_[0]);

   glDrawElements( GL_TRIANGLES, indices_->size(), GL_UNSIGNED_SHORT, 0);
}

void GlWidget::resizeGL(int w, int h)
{
   // Set Viewport to window dimensions
   glViewport(0, 0, w, h);
}

void GlWidget::setCamera(glm::vec3 position)
{
   cameraPosition_ = position;
   update();
}

void GlWidget::setTranslation(glm::vec3 translation)
{
   translation_ = translation;
   update();
}

void GlWidget::setRotation(glm::vec3 rotationsInDegrees)
{
   rotation_.x = PI*(float)rotationsInDegrees.x/180.0;
   rotation_.y = PI*(float)rotationsInDegrees.y/180.0;
   rotation_.z = PI*(float)rotationsInDegrees.z/180.0;
   update();
}

void GlWidget::setFOV(double fov)
{
   fov_ = fov;
   update();
}

void GlWidget::setScale(double scale)
{
   scale_ = scale;
   update();
}

void GlWidget::setSpecularPower(double power)
{
   power_ = (float) power;
   update();
}

void GlWidget::setAlbedo(glm::vec3 albedo)
{
   albedo_ = albedo;
   update();
}

void GlWidget::setAmbient(glm::vec3 ambient)
{
   ambient_ = ambient;
   update();
}

void GlWidget::setDiffuse(glm::vec3 diffuse)
{
   diffuse_ = diffuse;
   update();
}

void GlWidget::initializeGL()
{
   // These two lines will print out the version of OpenGL and GLSL
   // that are being used so that problems due to version differences
   // can easily be identified.
   initializeOpenGLFunctions();
   printf("OpenGL version: %s\n", (const char*) glGetString(GL_VERSION));
   printf("GLSL version: %s\n",
         (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION));
   // Do any necessary initializations (enabling buffers, setting up
   // shaders, geometry etc., before entering the main loop.)
   // This is done by calling the function setupRenderingContext().
   setupRenderingContext();
}

// This function does any needed initialization on the rendering context.
void GlWidget::setupRenderingContext()
{

   // Background
   glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
   glEnable(GL_DEPTH_TEST);

   loadAllShaders();

   // Now setup the geometry in a vertex buffer object
   // setup the vertex state array object. All subsequent buffers will
   // be bound to it.
   qVAO_ = new QOpenGLVertexArrayObject();
   bool good = qVAO_->create();
   good ? cout << "VOA created\n" : cout << "VOA error\n";
   qVAO_->bind();

   glGenBuffers(1, &vertexVbo);
   glBindBuffer( GL_ARRAY_BUFFER, vertexVbo);
   int verticesByteSize = vertices_->size()*sizeof(GLfloat);
   glBufferData(GL_ARRAY_BUFFER, verticesByteSize, vertices_->data(), GL_STATIC_DRAW);
   glEnableVertexAttribArray(VERTEX_DATA);
   glVertexAttribPointer(VERTEX_DATA, // attribute. No particular reason for 0, but must match the layout in the shader.
                         4,                  // size
                         GL_FLOAT,           // type
                         GL_FALSE,           // normalized?
                         0,                  // stride
                         (void*) 0            // array buffer offset
                        );
   glEnableVertexAttribArray(VERTEX_NORMAL);

   glGenBuffers(1, &normalVbo);
   glBindBuffer( GL_ARRAY_BUFFER, normalVbo);
   int normalsByteSize = normals_->size()*sizeof(GLfloat);
   glBufferData(GL_ARRAY_BUFFER, normalsByteSize, normals_->data(), GL_STATIC_DRAW);
   glVertexAttribPointer(VERTEX_NORMAL,
                         3,
                         GL_FLOAT,
                         GL_FALSE,
                         0,
                         (void*) 0
                        );

   glGenBuffers(1, &indiceVbo );
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indiceVbo );
   int indicesByteSize = sizeof(GLshort)*indices_->size();
   glBufferData( GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices_->data(), GL_STATIC_DRAW );
}

void GlWidget::loadAllShaders()
{
   // First setup the shaders
   //Now, let's setup the shaders
   GLuint hVertexShader = glCreateShader(GL_VERTEX_SHADER);
   GLuint hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   myShaderProgram = (GLuint) NULL;
   GLint testVal;

   if(!loadShaderFile("src/per-fragment-phong.vs.glsl", hVertexShader))
   {
      glDeleteShader(hVertexShader);
      glDeleteShader(hFragmentShader);
      cout << "The shader could not be found." << endl;
   }
   std::cout << "Here" << endl;
   if(!loadShaderFile("src/per-fragment-phong.fs.glsl", hFragmentShader))
   {
      glDeleteShader(hVertexShader);
      glDeleteShader(hFragmentShader);
      cout << "The shader could not be found." << endl;
   }

   glCompileShader(hVertexShader);
   glCompileShader(hFragmentShader);

   // Check for any error generated during shader compilation
   glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &testVal);
   if(testVal == GL_FALSE)
   {
      char source[8192];
      char infoLog[8192];
      glGetShaderSource(hVertexShader, 8192, NULL, source);
      glGetShaderInfoLog(hVertexShader, 8192, NULL, infoLog);
      cout << "The shader: " << endl << (const char*) source << endl
            << " failed to compile:" << endl;
      fprintf(stderr, "%s\n", infoLog);
      glDeleteShader(hVertexShader);
      glDeleteShader(hFragmentShader);
   }
   glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &testVal);
   if(testVal == GL_FALSE)
   {
      char source[8192];
      char infoLog[8192];
      glGetShaderSource(hFragmentShader, 8192, NULL, source);
      glGetShaderInfoLog(hFragmentShader, 8192, NULL, infoLog);
      cout << "The shader: " << endl << (const char*) source << endl
            << " failed to compile:" << endl;
      fprintf(stderr, "%s\n", infoLog);
      glDeleteShader(hVertexShader);
      glDeleteShader(hFragmentShader);
   }

   // Create the shader program and bind locations for the vertex
   // attributes before linking. The linking process can also generate errors

   myShaderProgram = glCreateProgram();
   glAttachShader(myShaderProgram, hVertexShader);
   glAttachShader(myShaderProgram, hFragmentShader);

   glBindAttribLocation(myShaderProgram, VERTEX_DATA, "position");
   glBindAttribLocation(myShaderProgram, VERTEX_NORMAL, "normal");
   glBindAttribLocation(myShaderProgram, VERTEX_COLOUR, "color");

   glLinkProgram(myShaderProgram);
   glDeleteShader(hVertexShader);
   glDeleteShader(hFragmentShader);
   glGetProgramiv(myShaderProgram, GL_LINK_STATUS, &testVal);
   if(testVal == GL_FALSE)
   {
      char infoLog[1024];
      glGetProgramInfoLog(myShaderProgram, 1024, NULL, infoLog);
      cout << "The shader program" << " failed to link:" << endl
            << (const char*) infoLog << endl;
      glDeleteProgram(myShaderProgram);
      myShaderProgram = (GLuint) NULL;
   }

}

// Load the shader from the specified file. Returns false if the shader could not be loaded
static GLubyte shaderText[8192];
bool GlWidget::loadShaderFile(const char *filename, GLuint shader)
{
   GLint shaderLength = 0;
   FILE *fp;

   // Open the shader file
   fp = fopen(filename, "r");
   if(fp != NULL)
   {
      // See how long the file is
      while (fgetc(fp) != EOF)
         shaderLength++;

      // Go back to beginning of file
      rewind(fp);

      // Read the whole file in
      fread(shaderText, 1, shaderLength, fp);

      // Make sure it is null terminated and close the file
      shaderText[shaderLength] = '\0';
      fclose(fp);
   }
   else
   {
      return false;
   }

   // Load the string into the shader object
   GLchar* fsStringPtr[1];
   fsStringPtr[0] = (GLchar *) ((const char*) shaderText);
   glShaderSource(shader, 1, (const GLchar **) fsStringPtr, NULL);

   return true;
}
