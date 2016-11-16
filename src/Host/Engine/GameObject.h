#pragma once

#include <vector>

#include "Object.h"

class Component;

namespace RenderingDemo
{
	class GameObject : public Object
	{
	public:
		GameObject();
		virtual ~GameObject();

	private:
		GameObject(GameObject const &other) = delete;
		void operator=(GameObject const &other) = delete;
		
		std::vector<Component*> components_;
	};
}
