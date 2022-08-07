/*
* Create by Lo, wenYi 2022/07/31
* is for simple setting init windows
*/
#include "./../Include/ToInclude.h"


class GLUTWindow {

public:
	enum class RegisterType {
		DISPLAY,
		RESHAPE,
		MOUSE,
		KEYBOARD,
		SPEICAL,
		TIMER,
		PASSIVEMOTION,
		MOTION
	};

	static const int WindowWidth = 600;
	static const int WindowHeight = 600;
	static void DefaultSetting(int argc, char* argv[]) {
		GLUTWindow::Init(argc, argv);
		//copy from Yao's project SimpleApp
#ifdef _MSC_VER
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#else
		glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(600, 600);
		glutCreateWindow("Default GLUT Window"); // You cannot use OpenGL functions before this line; The OpenGL context must be created first by glutCreateWindow()!
#ifdef _MSC_VER
		glewInit();
#endif
		//end
		GLUTWindow::DumpInformation();
	}

	static void Init(int argc, char* argv[])
	{
		// Initialize GLUT and GLEW, then create a window.
		////////////////////
		glutInit(&argc, argv);
	}

	static void DumpInformation(void) {
		printf("Vendor: %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version: %s\n", glGetString(GL_VERSION));
		printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
	static int CreateMenu(void (*name)(int)/*Function pointer*/) //using return's id to set current menu
	{
		return glutCreateMenu(name);
	}

	static void RegisterFunction(void (*ptr)(void), GLUTWindow::RegisterType type) {
		typedef GLUTWindow::RegisterType REGISTERTYPE;
		switch (type) {
		case REGISTERTYPE::DISPLAY:
			glutDisplayFunc( (void (*)())ptr);
			break;
		case REGISTERTYPE::MOUSE:
			glutMouseFunc((void (*)(int,int,int,int))ptr);
			break;
		case REGISTERTYPE::TIMER:
			glutTimerFunc(16, (void (*)(int))ptr, 0);
			break;
		case REGISTERTYPE::RESHAPE:
			glutReshapeFunc((void (*)(int,int))ptr);
			break;
		case REGISTERTYPE::KEYBOARD:
			glutKeyboardFunc((void (*)(unsigned char, int, int))ptr);
			break;
		case REGISTERTYPE::SPEICAL:
			glutSpecialFunc((void (*)(int, int, int))ptr);
			break;
		default:
			printf("Didn't write yet plz check GLUTWindow.h\n");
			break;
		}


	}
	static void RegisterTimerFunction(unsigned int time, void (*ptr)(int), int value) {
		glutTimerFunc(time, ptr, value);
	}

	static void GLUTMainLoop() {
		// Enter main event loop.
		glutMainLoop();
	}




private:
	GLUTWindow() 
	{

	}


};