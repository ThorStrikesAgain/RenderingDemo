#include "Component.h"
#include "GameObject.h"

namespace RenderingDemo
{
	Component::Component() :
		gameObject_{ nullptr }
	{
	}

	Component::~Component()
	{
		if (gameObject_ != nullptr)
		{
			gameObject_->RemoveComponent(*this);
		}
	}

	GameObject* Component::GetGameObject() const
	{
		return gameObject_;
	}
}
