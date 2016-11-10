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

	std::string vertCode = ReadAllText("E:/Alexandre/Projets/RenderingDemo/src/Host/Shaders/Basic.vert");
	std::string fragCode = ReadAllText("E:/Alexandre/Projets/RenderingDemo/src/Host/Shaders/Basic.frag");
	Shader test{ vertCode, fragCode };
}

void Viewport::paintGL()
{
	QOpenGLWidget::paintGL();
	gGL->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	gGL->glClear(GL_COLOR_BUFFER_BIT);
}

void Viewport::resizeGL(int w, int h)
{
	QOpenGLWidget::resizeGL(w, h);
}
