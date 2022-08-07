#pragma once
#include "./OpenGLBase.h"

//very important step https://github.com/nothings/stb/issues/3

namespace OpenGLBase {
	class TextureBase {
	public:
		int textureNum;
		GLuint* id=nullptr;
		int width;
		int height;

		unsigned char* data = nullptr;
	private:
		void GenerateTextures(int num = 1) {
			glGenTextures(num, this->id);
			this->textureNum = num;
		}
	public:
		//constructor
		TextureBase() {
			std::cout << "Not implment by texture default constructor\n";
		}
		TextureBase(int w, int h) {
			this->width = w;
			this->height = h;
			this->id = new GLuint;
			this->GenerateTextures();
		}
		TextureBase(const char* filePath, bool isMirrored);

	public:
		//method
		GLuint GetID() { return *this->id; }

		void UseTexture();
		void BindTexture(GLenum bind_unit);
		void UnBindTexture() {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		//need to implement
		virtual void SetTextureParameter() = 0;//https://www.khronos.org/registry/OpenGL-Refpages/es3.0/html/glTexImage2D.xhtml

		//deconstructor
		~TextureBase() {
			if (this->id != nullptr) {
				glDeleteTextures(this->textureNum, this->id);
				delete this->id;
			}

		}

	};
}