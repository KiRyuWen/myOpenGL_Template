# Some include tips
**References https://www.796t.com/content/1547206862.html**

1. $(SolutionDir) -> sln directory
2. $(ProjectDir) -> xxx.vcxproj
**3. Use x86!!!**
# What I did
1. Using vs 2019 to include library path
2. Using .h to include glew,glm, freeglut, myOpenGLBase
3. Include Assets directory for dlls
4. create a GLUTWindow.h 2022/07/31 
5. create textureImage.h .cpp 2022/08/07
6. update register function 
# RegisterFunction
You can use RegisterFunction(void (*ptr)(void), GLUTWindow::RegisterType type);

only to cast function type then will transfer back to original.
** Timer is more speical**
has RegisterTimerFunction
