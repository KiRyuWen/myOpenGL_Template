#pragma once
#include "./../../Include/OpenGLBase/OpenGLCommon.h"

namespace OpenGLBase {
	class TextureImage :public OpenGLBase::TextureBase {

	public:
		TextureImage(const char* filePath) :OpenGLBase::TextureBase(filePath, false) {
			this->BindTexture(0);
			this->SetTextureParameter();
			this->UnBindTexture();
		}

		TextureImage(const char* filePath,bool isMirrored) :OpenGLBase::TextureBase(filePath,isMirrored) {

			this->BindTexture(0);
			this->SetTextureParameter();
			this->UnBindTexture();
		}
		TextureImage(const char* filePath, bool isMirrored, bool wantMipMap):OpenGLBase::TextureBase(filePath, isMirrored) {
			this->BindTexture(0);
			this->SetTextureParameter(wantMipMap);
			this->UnBindTexture();
		}

		virtual void SetTextureParameter() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
			std::cout << "Texture only accept rgba not just rgb\n";

			std::cout << "Not test it in Texture constructor with file path may have bugs\n";
		}
		virtual void SetTextureParameter(bool wantMipMap) {
			if (wantMipMap) {
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
			std::cout << "Texture only accept rgba not just rgb\n";

			std::cout << "Not test it in Texture constructor with file path may have bugs\n";
		}
	};
}