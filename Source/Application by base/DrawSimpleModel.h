#pragma once


#include "./../../Include/OpenGLBase/OpenGLCommon.h"

namespace OpenGLBase {

	class DrawSimpleModelShader:public OpenGLBase::ShaderBase {

	public:
		DrawSimpleModelShader(ShaderInfo* info):OpenGLBase::ShaderBase(info) {

		}
		

		void SetTime(float time) {
			GLuint loc =this->GetLocation("time");
			if (isLocationMinusOne(loc)) {
				this->PrintSetFailedLocationInfomation("time");
				return;
			}
			glUniform1f(loc, time);
		}
		void SetResolution(glm::vec2 resolution) {
			GLuint loc = this->GetLocation("resolution");
			if (isLocationMinusOne(loc)) {
				this->PrintSetFailedLocationInfomation("resolution");
				return;
			}
			glUniform2fv(loc, 1, &resolution[0]);
		}
		
	};
}