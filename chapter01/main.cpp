#include "GL/glew.h"	// openGL
#include "GLFW/glfw3.h"	// GLFW

#include <iostream>
#include <memory>

#include "charpter_01.h"

// ----------------------------------------------------------------------------
void infoAboutOpenGL()
{
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

#if 0
	printf("GL Vendor            : %s\n", vendor);
	printf("GL Renderer          : %s\n", renderer);
	printf("GL Version (string)  : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version         : %s\n", glslVersion);

	for (int i = 0; i < nExtensions; i++)
		printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
#endif
}
// ----------------------------------------------------------------------------
int width = 1200, height = 1200;
int main(int argc, char **argv)
{	
	// init glfw and create window
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(width, height, "Triangles", NULL, NULL);
	glfwMakeContextCurrent(window);

	// for work functions, as: glCreateBuffers, glNamedBufferStorage
	glewInit();

	// out info abount openGL
	infoAboutOpenGL();

	std::unique_ptr<Introduction> pIntro = std::unique_ptr<Introduction>(new Introduction());

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(-0.5f, (width - 1) + 0.5f,
		//	(height - 1) + 0.5f, -0.5f, 0.0f, 1.0f);

		// Draw some text.
		pIntro->render();

		// End GL rendering, swap the buffer, and poll for events.

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	
	return 0;
}