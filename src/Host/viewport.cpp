#include "viewport.h"

#include <fstream>
#include <sstream>
#include <string>

#include "Engine/Engine.h"
#include "Engine/Shader.h"

using namespace RenderingDemo;

Viewport::Viewport(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format = this->format();
	format.setVersion(4, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	setFormat(format);
}

Viewport::~Viewport()
{
}

// TODO: Move this to a utilities file.
static std::string ReadAllText(char const *path)
{
	auto fs = std::ifstream{ path, std::ios_base::in };
	auto ss = std::ostringstream{};
	ss << fs.rdbuf();
	return ss.str();
}

void Viewport::initializeGL()
{
	QOpenGLWidget::initializeGL();
	
	// Initialize the engine.
	Engine::GetInstance();
}

void Viewport::paintGL()
{
	//QOpenGLWidget::paintGL();
	gGL->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gGL->glClear(GL_COLOR_BUFFER_BIT);

	// Test
	std::string vertCode = ReadAllText("E:/Alexandre/Projets/RenderingDemo/src/Host/Shaders/Basic.vert");
	std::string fragCode = ReadAllText("E:/Alexandre/Projets/RenderingDemo/src/Host/Shaders/Basic.frag");
	Shader test{ vertCode, fragCode };
	test.Use();

	// Vertex Array
	GLuint vertexArray;
	gGL->glGenVertexArrays(1, &vertexArray);
	gGL->glBindVertexArray(vertexArray);

	// Vertex Buffer
	GLuint vertexBuffer;
	gGL->glGenBuffers(1, &vertexBuffer);
	gGL->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	GLfloat vertexBufferData[] = 
	{
		-1.0f, -1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f,
		 0.0f,  1.0f, 0.0f, 1.0f,
	};
	gGL->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	// Vertex Attributes
	gGL->glVertexAttribPointer(
		0,        // Attribute index
		4,        // Components per vertex
		GL_FLOAT, // Component type
		GL_FALSE, // Must be normalized?
		0,        // Stride (tightly packed)
		NULL);    // No offset from the start of the buffer

	// Draw.
	gGL->glEnableVertexAttribArray(0);
	gGL->glDrawArrays(GL_TRIANGLES, 0, 3);
	gGL->glDisableVertexAttribArray(0);

	gGL->glDeleteBuffers(1, &vertexBuffer);
	gGL->glDeleteVertexArrays(1, &vertexArray);
}

void Viewport::resizeGL(int w, int h)
{
	QOpenGLWidget::resizeGL(w, h);
}
