#pragma once

#include "Object.h"

namespace RenderingDemo
{
	class GameObject;

	class Component : public Object
	{
		friend GameObject;

	public:
		Component();
		virtual ~Component();

		GameObject* GetGameObject() const;

	private:
		Component(Component const &other) = delete;
		void operator=(Component const &other) = delete;

		GameObject* gameObject_;
	};
}
