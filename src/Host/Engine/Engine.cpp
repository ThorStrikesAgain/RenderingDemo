#include "Engine.h"

namespace RenderingDemo
{
	QOpenGLFunctions_4_3_Core * gGL;

	Engine::Engine()
	{
		QOpenGLContext *c = QOpenGLContext::currentContext();
		gGL = c->versionFunctions<QOpenGLFunctions_4_3_Core>();
	}
}
