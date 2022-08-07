#include "./ShaderBase.h"

namespace OpenGLBase {
	const GLchar* ShaderBase::ReadShaderFile(const char* path)
	{
		GLchar* source;
		FILE* file = fopen(path, "rb");//r or rb?. See this website https://stackoverflow.com/questions/2174889/whats-the-differences-between-r-and-rb-in-fopen

		if (!file)
		{
			std::cout << "Unable to open file '" << path << "'" << std::endl;
			return NULL;
		}
		fseek(file, 0, SEEK_END); //to get the file len
		int len = ftell(file);
		fseek(file, 0, SEEK_SET); //set the pointer back to start
		source = new GLchar[len + 1];//set the end with 0
		fread(source, 1, len, file);//seems like remove first and end copy from another file
		source[len] = 0;
		fclose(file);
		return const_cast<const GLchar*>(source);
	}
	void ShaderBase::SetInt(std::string name, GLuint index)
	{
		GLuint loc = glGetUniformLocation(*this->id, "name");
		if (!loc) {
			std::cout << "Error get location integer\n";
			return;
		}
		glUniform1i(loc, index);
	}
	GLuint ShaderBase::LoadShader(ShaderInfo* infos)
	{
		if (infos == nullptr)
			return -1;

		GLuint program = glCreateProgram();
		GLuint createShaderTemp;
		while (infos->type != GL_NONE) {

			createShaderTemp = glCreateShader(infos->type);

			const GLchar* shaderSource = ShaderBase::ReadShaderFile(infos->path);
			if (!shaderSource) {
				std::cout << "Your path is " << infos->path << std::endl;
				std::cout << "Error path plz rewrite the path again" << std::endl;
				return -1;
			}

			glShaderSource(createShaderTemp, 1, &shaderSource, NULL);
			glCompileShader(createShaderTemp);

			GLint success;
			glGetShaderiv(createShaderTemp, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLchar InfoLog[1024];
				glGetShaderInfoLog(createShaderTemp, 1024, NULL, InfoLog);
				std::cout << "Error compiling shader type " << infos->type << ": " << InfoLog;
			}
			glAttachShader(program, createShaderTemp);

			glDeleteShader(createShaderTemp);//Not sure it's ok or no
			++infos;
		}
		glLinkProgram(program);

		return program;
	}
}