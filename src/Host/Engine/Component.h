#pragma once

#include "Object.h"

namespace RenderingDemo
{
	class Component : public Object
	{
	public:
		Component();
		virtual ~Component();

	private:
		Component(Component const &other) = delete;
		void operator=(Component const &other) = delete;
	};
}
