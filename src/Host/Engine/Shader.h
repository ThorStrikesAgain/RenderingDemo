#pragma once

#include "Engine.h"

namespace RenderingDemo
{
	class Shader
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
