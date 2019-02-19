#include <iostream>
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

int main(int argc, char const *argv[])
{
	SDL_Window    *m_window;
	SDL_GLContext  m_context;
	char* m_project_title = "OpenGL Zero";
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed to initialize SDL video\n");
		return 1;
	}

	m_window = SDL_CreateWindow(
		m_project_title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_OPENGL);
	if (m_window == NULL) {
		fprintf(stderr, "Failed to create main window\n");
		SDL_Quit();
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_context = SDL_GL_CreateContext(m_window);
	if (m_context == NULL) {
		fprintf(stderr, "Failed to create GL context\n");
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return 1;
	}

	glewExperimental = GL_TRUE;
	const GLubyte *renderer;
	const GLubyte *version;
	
	glewInit();
	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	
	while (true) {
		glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(m_window);
	}

	return 0;
}