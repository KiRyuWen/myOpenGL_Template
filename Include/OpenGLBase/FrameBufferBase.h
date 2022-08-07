#pragma once
#include "./OpenGLBase.h"
#include "Exception.h"
namespace OpenGLBase {
	
	class FrameBufferBase {
	protected:
		int windowWidth;
		int windowHeight;
		GLuint* id=nullptr;
		int fboNum;
		void GenerateFBO(int num = 1) {
			this->fboNum = num;
			this->id = new GLuint;
			glCreateFramebuffers(this->fboNum, this->id);
		}
	public:
		FrameBufferBase() {
			this->id = nullptr;
			OpenGLBase::NotImplement::Print();
		}
		FrameBufferBase(int w, int h) :windowHeight(h), windowWidth(w) {
			this->id = nullptr;
			this->GenerateFBO();
		}
		virtual void SetFBOParameter(int& w, int& h) = 0;
		virtual void EnableFBOFunc() = 0;
		virtual void DisableFBOFunc() = 0;
		virtual void ClearFramebuffer() = 0;
		void UseFBO() {
			if (this->id==nullptr) {

				std::cout << "You didn't create fbo yet\n";
				return;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, *this->id);
		}
		void UnBindFBO() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void CheckFramebufferStatus() {
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}
		~FrameBufferBase() {
			if (this->id) {
				glDeleteFramebuffers(this->fboNum, this->id);
				delete this->id;
			}
		}
	};
}
