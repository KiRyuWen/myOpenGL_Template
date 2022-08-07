#pragma once
#include "./OpenGLBase.h"
#include "./Exception.h"
#include <string>


namespace OpenGLBase {

	struct ShaderInformation {
		GLenum type;
		const char* path;
	};
	/*
	ShaderInformation infos[] = {
		{GL_VERTEX_SHADER,assetsPath + "./Shaders/model.vs"},
		{GL_FRAGMENT_SHADER,assetsPath + "./Shaders/model.fs"},
		{GL_NONE,NULL}
	};
	*/

	class ShaderBase {
	protected:
		GLuint* id=nullptr; //which program we want to link
		typedef struct ShaderInformation ShaderInfo;
		/*
		* ShaderInformation infos[] = {
		{GL_VERTEX_SHADER,assetsPath + "./Shaders/model.vs"},
		{GL_FRAGMENT_SHADER,assetsPath + "./Shaders/model.fs"},
		{GL_NONE,NULL}
	};
		*/


		//helper function to read shader
		static const GLchar* ReadShaderFile(const char* path);

	public:
	
		ShaderBase(ShaderInfo* source /*Can have array*/) {
			//inside with GL_NONE
			this->id = new GLuint;
			*(this->id) = ShaderBase::LoadShader(source);
		}
		ShaderBase(ShaderInfo* source /*Can have array*/, int size) {
			OpenGLBase::NotImplement::Print();
		}
		

		void SetInt(std::string name, GLuint index);
		inline GLuint GetLocation(std::string& name) {
			return glGetUniformLocation(*this->id, name.c_str());
		}
		inline GLuint GetLocation(const char* name) {
			return glGetUniformLocation(*this->id, name);
		}
		inline bool isLocationMinusOne(GLuint& loc) {
			return loc == -1;
		}
		inline void PrintSetFailedLocationInfomation(const char* infos) {
			printf("Set location failed %s\n", infos);
		}
		inline void Bind() {
			glUseProgram(*this->id);
		}

		

		//common
		static GLuint LoadShader(ShaderInfo* infos);

		static void UnBind() {
			glUseProgram(0);
		}

		//deconstructor
		~ShaderBase() {
			OpenGLBase::NotImplement::Print();
		}
	};

}