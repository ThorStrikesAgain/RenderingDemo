#pragma once

#include "Component.h"

#include <glm/gtc/quaternion.hpp>
#include <vector>

namespace RenderingDemo
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		glm::vec3 const & GetLocalPosition() const;
		void SetLocalPosition(glm::vec3 const & localPosition);

		glm::quat const & GetLocalRotation() const;
		void SetLocalRotation(glm::quat const & localRotation);

		glm::vec3 const & GetLocalScale() const;
		void SetLocalScale(glm::vec3 const & localScale);

		Transform* GetParent() const;
		void SetParent(Transform* parent);

		std::vector<Transform*> const & GetChildren() const;

		///
		/// Indicates whether the provided transform is strictly a descendant of this object. If the provided object is
		/// a descendant, the object on which this method is called shall be in its hierarchy of parents.
		///
		bool IsDescendantOf(Transform const & some) const;

	private:
		Transform(Transform const & other) = delete;
		void operator=(Transform const & other) = delete;

		glm::vec3 localPosition_;
		glm::quat localRotation_;
		glm::vec3 localScale_;

		Transform* parent_;
		std::vector<Transform*> children_;
	};
}
