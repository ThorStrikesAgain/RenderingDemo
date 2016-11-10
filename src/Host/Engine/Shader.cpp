#include "Shader.h"

#include <QtGlobal>

#include "Engine.h"

namespace RenderingDemo
{
	Shader::Shader(std::string const &vertCode, std::string const &fragCode)
	{
		GLint result;

		vert_ = gGL->glCreateShader(GL_VERTEX_SHADER);
		Q_ASSERT(vert_ != 0);
		char const *vertCodeChars = vertCode.c_str();
		gGL->glShaderSource(vert_, 1, &vertCodeChars, NULL);
		gGL->glCompileShader(vert_);
		gGL->glGetShaderiv(vert_, GL_COMPILE_STATUS, &result);
		Q_ASSERT(result == GL_TRUE);
		
		frag_ = gGL->glCreateShader(GL_FRAGMENT_SHADER);
		Q_ASSERT(frag_ != 0);
		char const *fragCodeChars = fragCode.c_str();
		gGL->glShaderSource(frag_, 1, &fragCodeChars, NULL);
		gGL->glCompileShader(frag_);
		gGL->glGetShaderiv(frag_, GL_COMPILE_STATUS, &result);
		Q_ASSERT(result == GL_TRUE);

	}

	Shader::~Shader()
	{
		Q_ASSERT(vert_ != 0);
		Q_ASSERT(frag_ != 0);

		gGL->glDeleteShader(vert_);
		vert_ = 0;

		gGL->glDeleteShader(frag_);
		frag_ = 0;
	}
}
