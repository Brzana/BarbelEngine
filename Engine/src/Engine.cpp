#include "Engine.h"
#include "Window.h"
#include <iostream>

namespace Engine {
	Engine::Engine(int windowWidth, int windowHeight, const char* windowTitle)
	: window(std::make_unique<Window>(windowWidth, windowHeight, windowTitle))
{}
	Engine::~Engine() = default;
	void Engine::Run() {
		while (!window->ShouldClose()) {
			window->SwapBuffers();
			window->PollEvents();
		}
	}
	} // namespace Engine
