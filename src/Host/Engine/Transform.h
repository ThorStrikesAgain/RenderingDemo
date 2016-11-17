#pragma once

#include "Component.h"

namespace RenderingDemo
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

	private:
		Transform(Transform const &other) = delete;
		void operator=(Transform const &other) = delete;
	};
}
