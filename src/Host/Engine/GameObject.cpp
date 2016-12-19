#include "GameObject.h"

namespace RenderingDemo
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
		for (auto component : components_)
		{
			component->gameObject_ = nullptr;
			delete component;
		}
		components_.clear();
	}

	///
	/// The GameObject takes ownership of the component.
	///
	void GameObject::AddComponent(Component& component)
	{
		components_.push_back(&component);
		Q_ASSERT(component.gameObject_ == nullptr);
		component.gameObject_ = this;
	}

	///
	/// The GameObject denies ownership of the component.
	///
	void GameObject::RemoveComponent(const Component& component)
	{
		auto iter = std::find(components_.begin(), components_.end(), &component);
		if (iter != components_.end())
		{
			Q_ASSERT((*iter)->gameObject_ == this);
			(*iter)->gameObject_ = nullptr;
			components_.erase(iter);
		}
	}

	std::vector<Component*> const & GameObject::GetComponents() const
	{
		return components_;
	}
}
