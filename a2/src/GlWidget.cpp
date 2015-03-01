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
GLuint myVBO;
GLuint myIndexBuffer;

// shader program to use
GLuint myShaderProgram;

// Geometry for the simple scene - a tetrahedron with some vertex
// attributes and a list of faces specifying connectivity
static const GLfloat tetVertices[] = {
      -1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
       -1.0f, 2.0f, 0.0f,
       1.0f, 2.0f, 0.0f,
       0.0f, 1.0f, 0.0f,

};
//static const GLushort tetFaceIndices[] = {
// 0, 1, 2
//};
//static const GLfloat tetColours[] = {
//
//};

//static const GLfloat tetNormals[] = {
//  0.0f,0.0f,-1.0f,
//  0.0f,1.0f,0.0f,
//  -0.707107f, -0.707107f,0.0f,
//  0.707107f, -0.707107f,0.0f
//};

// Constants to help with location bindings
#define VERTEX_DATA 0
#define VERTEX_COLOUR 2
#define VERTEX_NORMAL 1
//#define VERTEX_INDICES 3

GlWidget::GlWidget(QWidget *parent, QVector<GLfloat>* vertices, QVector<GLfloat>* normals) :
      QOpenGLWidget(parent),
      qVAO_(NULL),
      cameraX_(0),
      cameraY_(0),
      cameraZ_(8),
      transX_(0),
      transY_(0),
      transZ_(0),
      rotateX_(0.0),
      rotateY_(0.0),
      rotateZ_(0.0),
      fov_(45),
      vertices_(vertices),
      normals_(normals)
{

}

GlWidget::~GlWidget()
{
   qVAO_->destroy();
   deletePointer(qVAO_);
}

void GlWidget::paintGL()
{
   GLuint modelViewMatrixID = glGetUniformLocation(myShaderProgram, "mv_matrix");
   GLuint projMatrixID = glGetUniformLocation(myShaderProgram, "proj_matrix");

   // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   glm::mat4 projMatrix = glm::perspective(fov_, 4.0f / 3.0f, 0.1f, 100.0f);

   // Camera matrix
   glm::mat4 viewMatrix = glm::lookAt(glm::vec3(cameraX_, cameraY_, cameraZ_), // Camera is at (4,3,3), in World Space
   glm::vec3(0, 0, 0), // and looks at the origin
   glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
         );

   // Model matrix : an identity matrix (model will be at the origin)
   glm::mat4 Model = glm::mat4(1.0f);

   glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transX_, transY_, transZ_));

   // Translate View
   viewMatrix = viewMatrix*translationMatrix;

   glm::mat4 xRotationMatrix = glm::rotate(viewMatrix, rotateX_, glm::vec3(1.0f, 0.0f, 0.0f));
   glm::mat4 yRotationMatrix = glm::rotate(viewMatrix, rotateY_, glm::vec3(0.0f, 1.0f, 0.0f));
   glm::mat4 zRotationMatrix = glm::rotate(viewMatrix, rotateZ_, glm::vec3(0.0f, 0.0f, 1.0f));

   // Rotate View
   viewMatrix = viewMatrix*xRotationMatrix;
   viewMatrix = viewMatrix*yRotationMatrix;
   viewMatrix = viewMatrix*zRotationMatrix;

   glm::mat4 modelViewMatrix = viewMatrix * Model;

   // Clear the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(myShaderProgram);

   // Send our transformation to the currently bound shader,
   glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, &modelViewMatrix[0][0]);
   glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, &projMatrix[0][0]);

   glEnableVertexAttribArray(VERTEX_DATA);
   glVertexAttribPointer(0, // attribute. No particular reason for 0, but must match the layout in the shader.
         3,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void*) 0            // array buffer offset
         );
   // Note that this version of the draw command uses the
   // bound index buffer to get the vertex coordinates.
//   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
   glDrawArrays(GL_TRIANGLES, 0, vertices_->size());
}

void GlWidget::resizeGL(int w, int h)
{
   // Set Viewport to window dimensions
   glViewport(0, 0, w, h);
}

void GlWidget::setCamera(int x, int y, int z)
{
   cameraX_ = x;
   cameraY_ = y;
   cameraZ_ = z;
   update();
}

void GlWidget::setTranslation(int x, int y, int z)
{
   transX_ = x;
   transY_ = y;
   transZ_ = z;
   update();
}
void GlWidget::setRotation(int x, int y, int z)
{
   float xRad = M_PI*(float)x/180.0;
   float yRad = M_PI*(float)y/180.0;
   float zRad = M_PI*(float)z/180.0;
   rotateX_ = xRad;
   rotateY_ = yRad;
   rotateZ_ = zRad;
   update();
}

void GlWidget::setFOV(double fov)
{
   fov_ = fov;
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

   glGenBuffers(1, &myVBO);
   glBindBuffer( GL_ARRAY_BUFFER, myVBO);

   // Allocate space and load vertex data into the buffer.
   int verticesByteSize = vertices_->size()*sizeof(GLfloat);
   int normalsByteSize = 0;//normals_->size()*sizeof(GLfloat);
   int totalByteSize = verticesByteSize + normalsByteSize;
   glBufferData(GL_ARRAY_BUFFER, totalByteSize, NULL, GL_STATIC_DRAW);

   glBufferSubData(GL_ARRAY_BUFFER, 0, verticesByteSize, vertices_->data());
//   glBufferSubData(GL_ARRAY_BUFFER, verticesByteSize, verticesByteSize, normals_->data());
//   glBufferSubData(GL_ARRAY_BUFFER, sizeof(tetVertices), sizeof(tetColours),
//         tetColours);
//   glBufferSubData(GL_ARRAY_BUFFER, sizeof(tetVertices) + sizeof(tetColours),
//         sizeof(tetNormals), tetNormals);

   // Load face indices into the index buffer
//   glGenBuffers(1, &myIndexBuffer);
//   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, myIndexBuffer);
//   glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(tetFaceIndices),
//         tetFaceIndices, GL_STATIC_DRAW);

   // Now we'll use the attribute locations to map our vertex data (in
   // the VBO) to the shader
//   glEnableVertexAttribArray( VERTEX_DATA);
//   glVertexAttribPointer( VERTEX_DATA, 3, GL_FLOAT, GL_FALSE, 0,
//         (const GLvoid*) 0);
//   glEnableVertexAttribArray( VERTEX_COLOUR);
//   glVertexAttribPointer( VERTEX_COLOUR, 4, GL_FLOAT, GL_FALSE, 0,
//         (const GLvoid*) vertices_->size());
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

////////////////////////////////////////////////////////////////
// Load the shader from the specified file. Returns false if the
// shader could not be loaded
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
