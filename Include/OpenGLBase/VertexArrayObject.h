#pragma once
#include "./OpenGLBase.h"
namespace OpenGLBase {

	class VAO {
	public:
		GLuint* m_VAO=nullptr;
		int vao_size;
		VAO()
		{
			this->m_VAO = new GLuint;
			this->vao_size = 1;
			glGenVertexArrays(1, this->m_VAO);
		}

		VAO(int vaoSize) {
			this->m_VAO = new GLuint[vaoSize];
			this->vao_size = vaoSize;
			glGenVertexArrays(1, this->m_VAO);
		}

	public:
		void UseVAOByIndex(int index) {
			if (index < this->vao_size) {
				glBindBuffer(GL_ARRAY_BUFFER, this->m_VAO[index]);
			}
			else {
				printf("Index out of range in VAO\n");
			}
		}


	public:
		~VAO()
		{
			if (this->m_VAO)
			{
				glDeleteVertexArrays(1, this->m_VAO);
				delete this->m_VAO;
			}
		}

	public:
		void Use()//default is index 0
		{
			glBindVertexArray(*this->m_VAO);
		}
		void UnBind() {
			glBindVertexArray(0);
		}
	};
}