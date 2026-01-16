#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	class Window {
	public:
		Window(int width, int height, const char* title);
		~Window();
		void MakeContextCurrent();
		bool ShouldClose();
		void SwapBuffers();
		void PollEvents();
		int GetWidth() const;
		int GetHeight() const;
	private:
		GLFWwindow* window;
		int width;
		int height;
	};
}
