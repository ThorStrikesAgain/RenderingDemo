#include "viewport.h"

#include <Windows.h>
#include <gl/GL.h>
#include <Wingdi.h>

#include <qopenglcontext.h>
#include <qopenglfunctions_4_3_core.h>

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

void Viewport::initializeGL()
{
	QOpenGLWidget::initializeGL();
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Viewport::paintGL()
{
	QOpenGLWidget::paintGL();
	QOpenGLContext *c = QOpenGLContext::currentContext();
	QSurfaceFormat format = c->format();
	int major = format.majorVersion();
	int minor = format.minorVersion();

	QOpenGLFunctions_4_3_Core *f = c->versionFunctions<QOpenGLFunctions_4_3_Core>();
	f->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	f->glClear(GL_COLOR_BUFFER_BIT);
}

void Viewport::resizeGL(int w, int h)
{
	QOpenGLWidget::resizeGL(w, h);
}
