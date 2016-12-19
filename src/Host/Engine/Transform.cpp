#include "Transform.h"

#include <algorithm>

namespace RenderingDemo
{
	Transform::Transform() :
		localPosition_{ 0, 0, 0 },
		localRotation_{ 1, 0, 0, 0 },
		localScale_{ 1, 1, 1 },
		parent_{ nullptr }
	{
	}

	Transform::~Transform()
	{
		SetParent(nullptr);
		for (auto child : children_)
		{
			// If the user wants a more fancy behaviour (ex: set their parent to mine), he can implement it before
			// destroying the objects. But by default, we don't want to alter the parent. There could be side
			// effects unknown at this level, and we don't want to force the user to undo what we did.
			//
			// Don't call SetParent(nullptr) on the child from here, because it will attempt to modify children_
			// while we are
			// iterating over it.
			child->parent_ = nullptr;
		}
		children_.clear();
	}

	glm::vec3 const & Transform::GetLocalPosition() const
	{
		return localPosition_;
	}

	void Transform::SetLocalPosition(const glm::vec3& localPosition)
	{
		localPosition_ = localPosition;
	}

	glm::quat const & Transform::GetLocalRotation() const
	{
		return localRotation_;
	}

	void Transform::SetLocalRotation(const glm::quat& localRotation)
	{
		localRotation_ = localRotation;
	}

	glm::vec3 const & Transform::GetLocalScale() const
	{
		return localScale_;
	}

	void Transform::SetLocalScale(const glm::vec3& localScale)
	{
		localScale_ = localScale;
	}

	Transform* Transform::GetParent() const
	{
		return parent_;
	}

	///
	/// The parent doesn't take ownership of this transform.
	///
	void Transform::SetParent(Transform* newParent)
	{
		if (newParent == parent_)
		{
			return;
		}

		if (newParent != nullptr)
		{
			// Prevent loops.
			if (newParent == this || newParent->IsDescendantOf(*this))
			{
				Q_ASSERT(false); // TODO: Log an error instead of asserting.
				return;
			}

			// Add this to the children of the new parent.
			newParent->children_.push_back(this);
		}

		// Remove this from the children of the old parent.
		if (parent_ != nullptr)
		{
			std::vector<Transform*> & childrenOfOldParent = parent_->children_;
			auto iter = std::find(childrenOfOldParent.begin(), childrenOfOldParent.end(), this);
			Q_ASSERT(iter != childrenOfOldParent.end()); // We should be in the list of children of our parent.
			childrenOfOldParent.erase(iter);
		}

		// Set the new parent.
		parent_ = newParent;
	}

	std::vector<Transform*> const & Transform::GetChildren() const
	{
		return children_;
	}

	bool Transform::IsDescendantOf(Transform const & some) const
	{
		Transform const * toTest = parent_;
		while (toTest != nullptr)
		{
			if (toTest == &some)
			{
				return true;
			}
			toTest = toTest->parent_;
		} 

		return false;
	}
}
