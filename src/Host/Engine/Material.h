#pragma once

#include "Object.h"

namespace RenderingDemo
{
	class Material : public Object
	{
	public:
		Material();
		virtual ~Material();

	private:
		Material(Material const &other) = delete;
		void operator=(Material const &other) = delete;
	};
}
