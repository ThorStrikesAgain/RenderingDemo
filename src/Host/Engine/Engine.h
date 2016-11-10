#pragma once

#include <qopenglfunctions_4_3_core.h>

namespace RenderingDemo
{
	extern QOpenGLFunctions_4_3_Core * gGL;

	class Engine
	{
	public:
		static Engine* GetInstance()
		{
			static Engine* engine = nullptr;
			if (engine == nullptr)
			{
				engine = new Engine{};
			}
			return engine;
		}

	private:
		Engine();
		
		Engine(Engine const *other) = delete;
		void operator =(Engine const * other) = delete;
	};
}
