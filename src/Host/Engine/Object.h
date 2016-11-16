#pragma once

#include "Engine.h"

namespace RenderingDemo
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		std::string const & GetName() const;
		void SetName(std::string const &name);

	private:
		Object(Object const &other) = delete;
		void operator=(Object const &other) = delete;

		std::string name_;
	};
}
