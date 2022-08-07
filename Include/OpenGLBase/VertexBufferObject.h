#pragma once
#include "./OpenGLBase.h"

namespace OpenGLBase {
	class VBO
	{
	public:
		GLuint* m_VBO=nullptr; // any size you want
		int vbo_size;//how many buffer we want init is 3 vertice, normal, texture
		VBO(int size = 3) : vbo_size(size)
		{
			this->m_VBO = new GLuint[vbo_size];
			glGenBuffers(1, this->m_VBO);

		}
		~VBO()
		{
			glDeleteBuffers(this->vbo_size, m_VBO);
			delete this->m_VBO;
			this->vbo_size = 0;
		}

	public:
		void UseBufferByIndex(int index) //set this by your own
		{
			if (index < this->vbo_size) {
				glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO[index]);
			}
			else {
				printf("Index out of range in MyEffect.h VBO\n");
			}
		}

		void SetBufferData(std::vector<float>& vertices, int index, int nodeSize, int isStaticDraw = 1) //set this by your own accept vector
		{
			if (isStaticDraw) {
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
			}
			else {
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
			}

			//void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,const GLvoid * pointer);
			//given index
			//given every node size such as vertex with 3 data nodesize will be 3
			//init type is GL_FLOAT
			//is going to be normalized?
			//stride means next positin by this offset ex (0,1,2,3,4,5) -> I want 1 3 5 etc. so the offset is 2
			//pointer means start position so we need the address!
			glVertexAttribPointer(index, nodeSize, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(index);
		}
		void SetBufferData(float* vertices, int sizeofArray/*This only accept sizeof function by c*/, int index, int nodeSize, int isStaticDraw = 1) //The second attribute is only accepeted by sizeof(array)
		{
			if (isStaticDraw) {
				glBufferData(GL_ARRAY_BUFFER, sizeofArray, vertices, GL_STATIC_DRAW);
			}
			else {
				glBufferData(GL_ARRAY_BUFFER, sizeofArray, vertices, GL_DYNAMIC_DRAW);
			}
			//void glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,const GLvoid * pointer);
			//given index
			//given every node size such as vertex with 3 data nodesize will be 3
			//init type is GL_FLOAT
			//is going to be normalized?
			//stride means next positin by this offset ex (0,1,2,3,4,5) -> I want 1 3 5 etc. so the offset is 2
			//pointer means start position so we need the address!
			glVertexAttribPointer(index, nodeSize, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(index);
		}

		void UnBind() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};
}