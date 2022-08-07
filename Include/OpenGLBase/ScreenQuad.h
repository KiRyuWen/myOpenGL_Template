#pragma once
#include "OpenGLCommon.h"

namespace OpenGLBase {
	
	class ScreenQuad {
	private:
		typedef OpenGLBase::VAO VAO;
		typedef OpenGLBase::VBO VBO;
		VAO* vao=nullptr;
		VBO* vbo=nullptr;
	public:
		ScreenQuad(){
			this->vao = new VAO();
			this->vbo = new VBO(2);//only two dimension vertex and texture points
			float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   
			-1.0f,  1.0f,
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			-1.0f,  1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f
			};
			// texCoords
			float texturePoint[] = {
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 0.0f,
				1.0f, 1.0f
			};

			this->vao->Use();

			this->vbo->UseBufferByIndex(0);
			this->vbo->SetBufferData(quadVertices, sizeof(quadVertices), 0, 2);

			this->vbo->UseBufferByIndex(1);
			this->vbo->SetBufferData(texturePoint, sizeof(texturePoint), 1, 2);
		}
		void Draw() {
			this->vao->Use();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			this->vao->UnBind();
		}

		~ScreenQuad() {
			if (this->vao)
				delete this->vao;
			if (this->vbo)
				delete this->vbo;
		}
	};
}