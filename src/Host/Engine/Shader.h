#pragma once

#include "Object.h"

namespace RenderingDemo
{
	class Shader : public Object
	{
	public:
		/// @param[in]  vertCode Vertex shader code.
		/// @param[out] fragCode Fragment shader code.
		Shader(std::string const & vertCode, std::string const & fragCode);
		~Shader();

		void Use() const;

	private:
		Shader(Shader const &other) = delete;
		void operator=(Shader const &other) = delete;

		GLuint vert_;
		GLuint frag_;

		GLuint program_;
	};
}
