#include "Object.h"

#include <sstream>

namespace RenderingDemo
{
	Object::Object()
	{
		static int sInstanceCounter = 0;
		std::ostringstream oss;
		oss << "Object" << sInstanceCounter++;
		name_ = oss.str();
	}

	Object::~Object()
	{
	}

	std::string const & Object::GetName() const
	{
		return name_;
	}

	void Object::SetName(std::string const &name)
	{
		name_ = name;
	}
}
