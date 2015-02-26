//#include <GL/glew.h>
#include <GlWidget.h>
#include <QWidget>
#include <stdlib.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
//#include <GL/gl_mangle.h>
#include <iostream>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>
using namespace std;
// VAO and VBO to handle vertex state and data
GLuint myVAO[1];
GLuint myVBO;
GLuint myIndexBuffer;

// shader program to use
GLuint myShaderProgram;

// Geometry for the simple scene - a tetrahedron with some vertex
// attributes and a list of faces specifying connectivity
static const GLfloat tetVertices[] = {
  0.0f, 0.0f, -0.75f, 1.0f,
  0.0f, 0.75f, 0.0f, 1.0f,
  -0.75f, -0.75f, 0.0f, 1.0f,
  0.75f, -0.75f, 0.0f, 1.0f,
};
static const GLushort tetFaceIndices[] = {
  0,1,2,
  0,1,3,
  1,2,3,
  0,2,3
};
static const GLfloat tetColours[] = {
  1.0f,1.0f,1.0f,1.0f,
  1.0f,0.0f,0.0f,1.0f,
  0.0f,1.0f,0.0f,1.0f,
  0.0f,0.0f,1.0f,1.0f
};
static const GLfloat tetNormals[] = {
  0.0f,0.0f,-1.0f,
  0.0f,1.0f,0.0f,
  -0.707107f, -0.707107f,0.0f,
  0.707107f, -0.707107f,0.0f
};

////////////////////////////////////////////////////////////////
// Load the shader from the specified file. Returns false if the
// shader could not be loaded
static GLubyte shaderText[8192];
bool GlWidget::loadShaderFile(const char *filename, GLuint shader) {
  GLint shaderLength = 0;
  FILE *fp;

  // Open the shader file
  fp = fopen(filename, "r");
  if(fp != NULL) {
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
  else {
    return false;
  }

  // Load the string into the shader object
  GLchar* fsStringPtr[1];
  fsStringPtr[0] = (GLchar *)((const char*)shaderText);
  glShaderSource(shader, 1, (const GLchar **)fsStringPtr, NULL );

  return true;
}

// Constants to help with location bindings
#define VERTEX_DATA 0
#define VERTEX_COLOUR 1
#define VERTEX_NORMAL 2
#define VERTEX_INDICES 3

// Called to draw scene
void GlWidget::renderScene() {
  // Clear the window and the depth buffer
   fprintf(stderr, "render \n");
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram( myShaderProgram );
   fprintf(stderr, "use prog \n");

   // Note that this version of the draw command uses the
   // bound index buffer to get the vertex coordinates.
//   glDrawElements( GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);
   fprintf(stderr, "render end\n");
}

void GlWidget::ChangeSize(int w, int h) {
   // Set Viewport to window dimensions
   fprintf(stderr, "resize\n");
   glViewport(0, 0, w, h);
}

// This function does any needed initialization on the rendering
// context.
void GlWidget::setupRenderingContext() {

  // Background
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
  glEnable(GL_DEPTH_TEST);

  // First setup the shaders
  //Now, let's setup the shaders
  GLuint hVertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  myShaderProgram = (GLuint)NULL;
  GLint testVal;

  if( !loadShaderFile("interpColour.vs", hVertexShader) ) {
    glDeleteShader( hVertexShader );
    glDeleteShader( hFragmentShader );
    cout << "The shader " << "interpColour.vs" << " could not be found." << endl;
  }
  std::cout << "Here" << endl;
  if( !loadShaderFile("interpColour.fs", hFragmentShader) ) {
    glDeleteShader( hVertexShader );
    glDeleteShader( hFragmentShader );
    cout << "The shader " << "interpColour.fs" << " could not be found." << endl;
  }

  glCompileShader(hVertexShader);
  glCompileShader(hFragmentShader);


  // Check for any error generated during shader compilation
  glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &testVal);
  if( testVal == GL_FALSE ) {
    char source[8192];
    char infoLog[8192];
    glGetShaderSource( hVertexShader, 8192, NULL, source );
    glGetShaderInfoLog( hVertexShader, 8192, NULL, infoLog);
    cout << "The shader: " << endl << (const char*)source << endl << " failed to compile:" << endl;
    fprintf( stderr, "%s\n", infoLog);
    glDeleteShader(hVertexShader);
    glDeleteShader(hFragmentShader);
  }
  glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &testVal);
  if( testVal == GL_FALSE ) {
    char source[8192];
    char infoLog[8192];
    glGetShaderSource( hFragmentShader, 8192, NULL, source);
    glGetShaderInfoLog( hFragmentShader, 8192, NULL, infoLog);
    cout << "The shader: " << endl << (const char*)source << endl << " failed to compile:" << endl;
    fprintf( stderr, "%s\n", infoLog);
    glDeleteShader(hVertexShader);
    glDeleteShader(hFragmentShader);
  }

  // Create the shader program and bind locations for the vertex
  // attributes before linking. The linking process can also generate errors

  myShaderProgram = glCreateProgram();
  glAttachShader(myShaderProgram, hVertexShader);
  glAttachShader(myShaderProgram, hFragmentShader);

  glBindAttribLocation( myShaderProgram, VERTEX_DATA, "vVertex" );
  glBindAttribLocation( myShaderProgram, VERTEX_COLOUR, "vColor" );

  glLinkProgram( myShaderProgram );
  glDeleteShader( hVertexShader );
  glDeleteShader( hFragmentShader );
  glGetProgramiv( myShaderProgram, GL_LINK_STATUS, &testVal );
  if( testVal == GL_FALSE ) {
    char infoLog[1024];
    glGetProgramInfoLog( myShaderProgram, 1024, NULL, infoLog);
    cout << "The shader program" << "(interpColour.vs + interpColour.fs) failed to link:" << endl << (const char*)infoLog << endl;
    glDeleteProgram(myShaderProgram);
    myShaderProgram = (GLuint)NULL;
  }

  // Now setup the geometry in a vertex buffer object

  // setup the vertex state array object. All subsequent buffers will
  // be bound to it.
  QOpenGLVertexArrayObject qVAO;
  bool good = qVAO.create();
  good ? cout<<"VOA created\n" : cout<<"VOA error\n";
//  glGenVertexArrays(1, myVAO);
  qVAO.bind();
//  glBindVertexArray(myVAO[0]);

  glGenBuffers(1, &myVBO);
  glBindBuffer( GL_ARRAY_BUFFER, myVBO );
  fprintf(stderr, "bind vbo \n");
  // Allocate space and load vertex data into the buffer.
  // We are using one VBO for all the data. For this demo, we won't be
  // making use of the normals but the code below shown how we might
  // store them in the VBO.
  glBufferData(GL_ARRAY_BUFFER, sizeof(tetVertices) +
   sizeof(tetColours) + sizeof(tetNormals), NULL,
   GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tetVertices),
    tetVertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(tetVertices),
    sizeof(tetColours), tetColours);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(tetVertices) +
    sizeof(tetColours), sizeof(tetNormals),
    tetNormals);
  fprintf(stderr, "sub data\n");
  // Load face indices into the index buffer
  glGenBuffers(1, &myIndexBuffer );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, myIndexBuffer );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(tetFaceIndices), tetFaceIndices, GL_STATIC_DRAW );
  fprintf(stderr, "GL_ELEMENT_ARRAY_BUFFER\n");
  // Now we'll use the attribute locations to map our vertex data (in
  // the VBO) to the shader
  glEnableVertexAttribArray( VERTEX_DATA );
  glVertexAttribPointer( VERTEX_DATA, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) 0 );
  glEnableVertexAttribArray( VERTEX_COLOUR );
  glVertexAttribPointer( VERTEX_COLOUR, 4, GL_FLOAT, GL_FALSE, 0,
   (const GLvoid*)(sizeof(tetVertices)));
  fprintf(stderr, "glVertexAttribPointer\n");
}

GlWidget::GlWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void GlWidget::paintGL()
{
   renderScene();
}

void GlWidget::resizeGL(int w, int h)
{
   ChangeSize(w, h);
}

void GlWidget::initializeGL()
{
   fprintf(stderr, "here \n");
//   QOpenGLContext* m_context = new QOpenGLContext();
//   QSurfaceFormat* a = new QSurfaceFormat();
//   a->setRenderableType(QSurfaceFormat::OpenGL);
//   m_context->setFormat(*a);
//   m_context->create();
//   initializeOpenGLFunctions();

//   QSurfaceFormat format;
//       format.setDepthBufferSize( 24 );
//       format.setMajorVersion( 4 );
//       format.setMinorVersion( 3 );
//       format.setSamples( 4 );
//       format.setProfile( QSurfaceFormat::CoreProfile );
//       setFormat( format );
//       create();
//
//       // Create an OpenGL context
//       QOpenGLContext* m_context = new QOpenGLContext;
//       m_context->setFormat( format );
//       m_context->create();
//
//       // Make the context current on this window
////       m_context->makeCurrent( this );
//       makeCurrent();
//
//       // Obtain a functions object and resolve all entry points
//       // m_funcs is declared as: QOpenGLFunctions_4_3_Core* m_funcs
//       QOpenGLFunctions_3_3_Core* m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_3_Core>();
//       if ( !m_funcs ) {
//           fprintf(stderr, "error \n");
//       }
//       m_funcs->initializeOpenGLFunctions();


//   glewExperimental = GL_TRUE;
//   GLenum err = glewInit();


   // These two lines will print out the version of OpenGL and GLSL
   // that are being used so that problems due to version differences
   // can easily be identified.
   initializeOpenGLFunctions();
   printf( "OpenGL version: %s\n", (const char*)glGetString(GL_VERSION) );
   printf( "GLSL version: %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
   fprintf(stderr, "here 2 \n");
   // Do any necessary initializations (enabling buffers, setting up
   // shaders, geometry etc., before entering the main loop.)
   // This is done by calling the function setupRenderingContext().
   setupRenderingContext();

}



