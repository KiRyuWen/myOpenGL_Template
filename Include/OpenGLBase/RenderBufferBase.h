#pragma once

#include "./OpenGLBase.h"

namespace OpenGLBase {
	class RenderBufferObject {
	public:
		GLuint* rboID=nullptr;
		int rboNum;
		void GenerateRBO(int num = 1) {
			this->rboID = new GLuint;
			glGenRenderbuffers(num, this->rboID);
		}
	public:
		RenderBufferObject() {
			this->GenerateRBO();
		}
		RenderBufferObject(int num) {
			GenerateRBO(num);
		}

		void SetRBOStorage(int w, int h) {
			//can be changed?
			//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);

			//changed for depth component32
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32,w, h);
		}
		void BindToFramebuffer() {
			//can be changed?
			// attach it to framebuffer
			//bind render buffer with depth and stencil attachment
			//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *(this->rboID));

			//changed for depth component32
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *(this->rboID));
		}

		void BindRBO() {
			glBindRenderbuffer(GL_RENDERBUFFER, *(this->rboID));
		}
		void UnBindRBO() {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

		~RenderBufferObject() {
			if (this->rboID) {
				glDeleteRenderbuffers(rboNum, this->rboID);
				delete this->rboID;
			}
		}
	};
}