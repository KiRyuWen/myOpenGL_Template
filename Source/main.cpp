//built-in
#include <Windows.h>
//To include many openglbase
#include "./../Include/ToInclude.h"
#include "./GLUTWindow.h"
#include "./../Include/OpenGLBase/ScreenQuad.h"
//to include my app
#include "./Application by base/DrawSimpleModel.h"
#include "./Application by base/TextureImage.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./../Include/OpenGLBase/stb_image_write.h"


//variables
OpenGLBase::DrawSimpleModelShader* modelShader;
OpenGLBase::ScreenQuad* screenQuad;
OpenGLBase::TextureImage* screenImage;
static bool isPause = false;
static float myTime = 0.0f;
static float ScreenWidth = 600.0f;
static float ScreenHeight = 600.0f;
static float aspect = ScreenWidth * 1.0f / ScreenHeight; // w()/h() -> aspect ratio
//Functions 
std::string replacePathSlash(std::string path);//helper function
std::string current_working_directory();//helper function
void Init();
void My_Display();
void My_Reshape(int width,int height);
void My_Mouse(int button, int state, int x, int y);
void My_Timer(int val);
void My_Keyboard(unsigned char key, int x, int y);
void My_SpecialKeys(int key, int x, int y);
int main(int argc, char* argv[]) {
	//print some information!
	GLUTWindow::DefaultSetting(argc, argv);

	//Your Init function
	Init();
	//Register glut function (at least one)
	GLUTWindow::RegisterFunction((void(*)())My_Display, GLUTWindow::RegisterType::DISPLAY);
	GLUTWindow::RegisterFunction((void(*)())My_Mouse, GLUTWindow::RegisterType::MOUSE);
	GLUTWindow::RegisterFunction((void(*)())My_Timer, GLUTWindow::RegisterType::TIMER);
	GLUTWindow::RegisterFunction((void(*)())My_Keyboard, GLUTWindow::RegisterType::KEYBOARD); //wasd
	GLUTWindow::RegisterFunction((void(*)())My_SpecialKeys, GLUTWindow::RegisterType::SPEICAL); //f12 f1 ...


	//main loop for openGL
	GLUTWindow::GLUTMainLoop();
	return 0;
}



//functions
std::string replacePathSlash(std::string path) {
	for (int i = 0; i < path.size(); ++i) {
		if (path[i] == '\\') {
			path = path.substr(0, i) +"/"+path.substr(i + 1);
		}
	}

	return path;
}
std::string current_working_directory()
{
	char* cwd = _getcwd(0, 0); // **** microsoft specific ****
	std::string working_directory(cwd);
	std::free(cwd);
	return replacePathSlash(working_directory);
}


void Init() {
	//First windows look like
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	using namespace OpenGLBase;
	
	//Shaders setting
	{
		std::string assets_path = current_working_directory();
		std::string file_vs = (assets_path + "/./Shaders/model.vs");
		std::string file_fs = (assets_path + "/./Shaders/model.fs");
		//Shader infomations
		ShaderInformation model_shaders[] = {
			{GL_VERTEX_SHADER,file_vs.c_str()},
			{GL_FRAGMENT_SHADER,file_fs.c_str()},
			{GL_NONE,NULL}
		};
		//Shader
		modelShader = new OpenGLBase::DrawSimpleModelShader(model_shaders);
	}
	//Models setting
	{
		std::string assets_path = current_working_directory();
		std::string file_KIRA_YOSHIKAGE = (assets_path + "/./Images/Kira Yoshikage.jpg");
		screenImage = new TextureImage(file_KIRA_YOSHIKAGE.c_str());
		screenQuad = new ScreenQuad();
	}
	
}

void My_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//openGL 1.1
	//glBegin(GL_TRIANGLES);

	//glColor3f(0.5, 0, 0);
	//glVertex3f(0, 0.5, -1);
	//glVertex3f(-0.5,0, -1);
	//glVertex3f(0.5, 0,- 1);
	//glEnd();

	
	modelShader->Bind();
	modelShader->SetInt("Image", 0);
	//modelShader->SetResolution(glm::vec2(GLUTWindow::WindowWidth, GLUTWindow::WindowHeight)); Don't use because in shader we didn't use it so set location will be failed.
	modelShader->SetTime(myTime);
	screenImage->BindTexture(0);

	screenQuad->Draw();

	screenImage->UnBindTexture();
	modelShader->UnBind();

	glutSwapBuffers();
}

void My_Reshape(int width, int height)
{
	ScreenWidth = width;
	ScreenHeight = height;
	glViewport(0,0,width, height);
}

//Mouse event
void My_Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			printf("Mouse %d is pressed at (%d, %d)\n", button, x, y);
		}
		else if (state == GLUT_UP)
		{
			printf("Mouse %d is released at (%d, %d)\n", button, x, y);
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		printf("Mouse %d is pressed\n", button);
	}
	printf("%d %d %d %d\n", button, state, x, y);
}

//Timer event
void My_Timer(int val)
{
	glutPostRedisplay();
	if(!isPause)
		myTime += 16 * 0.001f;
	glutTimerFunc(16, My_Timer, val);
}

void My_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ': //pause
		isPause = !isPause;
		break;
	case 'q'://quit
	case 'Q':
		exit(1);
		break;

	}
}

void My_SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_F5) //reload some informations
	{
		printf("Not Done\n");
	}
	else if (key==GLUT_KEY_F6)//f6
	{
		std::string path = current_working_directory()+"/screenshot.png";
		printf("Saving the screenshot at %s\n", path.c_str());
		
		//referenced by https://github.com/tsoding/opengl-template/blob/master/main.c Tsoding Daily Youtuber!
		int rgbaSize = 4;
		int rgbSize = 3;
		void* pixels = malloc(4 * ScreenWidth * ScreenHeight);
		if (pixels == NULL) {
			fprintf(stderr, "ERROR: could not allocate memory for pixels to make a screenshot: %s\n",
				strerror(errno));
			return;
		}
		glReadPixels(0, 0, ScreenWidth, ScreenHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		unsigned char* image = new unsigned char[rgbaSize * ScreenWidth * ScreenHeight];
		memcpy(image, pixels, rgbaSize * ScreenWidth * ScreenHeight);
		////vertical mirrored
		//for (int i = 0; i < ScreenHeight; ++i) {
		//	for (int j = 0; j < ScreenWidth/2; ++j) {
		//		for (int k = 0; k < 4; ++k) {	
		//			//vertical swap
		//			//(i*width+j)*rgbaSize+k
		//			//(i*width+width-1-j)*rgbasize+k
		//			std::swap(image[((int)((i * ScreenWidth+j)* rgbaSize+ k))], image[((int)((i * ScreenWidth+ScreenWidth-1-j)* rgbaSize+ k))]);

		//		}
		//	}
		//}
		//horizontal mirrored
		for (int i = 0; i < ScreenHeight / 2; ++i) {
			for (int j = 0; j < ScreenWidth; ++j) {
				for (int k = 0; k < 4; ++k) {
					//horizontal swap 
					//(i*w+j)*rgba+k
					//((h-i-1)*w+j)*rgba+k
					std::swap(image[(int)((i * ScreenWidth + j) * rgbaSize + k)], image[(int)(((ScreenHeight - i - 1) * ScreenWidth+j) * rgbaSize + k)]);
				}
			}
		}
							



		if (!stbi_write_png(path.c_str(), ScreenWidth, ScreenHeight, 4, image, ScreenWidth * 4)) {
			fprintf(stderr, "ERROR: could not save %s: %s\n", path.c_str(), strerror(errno));
		}
		free(pixels);
	}
	
}
