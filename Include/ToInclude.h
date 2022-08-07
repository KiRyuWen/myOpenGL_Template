#pragma once

#ifdef _MSC_VER
	#include "../Include/GLEW/include/GL/glew.h"
	#include "../Include/FreeGLUT/freeglut.h"
	#include <direct.h>
#else
	#include <OpenGL/gl3.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
#endif



/*The first implementation follows the GLSL convensions accurately. 
It uses macros to achieve this, which might generates name conflicts with system headers or third party libraries. 
Therefore, it is disabled by default. To enable this implementation, GLM_SWIZZLE must be defined before any inclusion of <glm/glm.hpp>.
*/
#define GLM_MESSAGES //This system is disable by default. To enable this system, define GLM_MESSAGES before any inclusion of <glm/glm.hpp>.
#define GLM_SWIZZLE //for glsl language such as A.xy = B.yz like these
//#define GLM_SWIZZLE_XYZW/GLM_SWIZZLE_STQP we can use it partially 
//A safer way to do swizzling is to use the <glm/gtc/swizzle.hpp> extension. This extension provides the GLSL functionality, but uses a different syntax for it. Moreover, the swizzle extension also provides dynamic swizzling.
#include "../Include/GLM/glm/glm.hpp"
#include "../Include/GLM/glm/gtc/matrix_transform.hpp"
//more complicated see this https://glm.g-truc.net/0.9.1/api/a00002.html

#define deg2rad(x) ((x)*((3.1415926f)/(180.0f)))
#define rad2deg(x) ((180.0f) / ((x)*(3.1415926f)))