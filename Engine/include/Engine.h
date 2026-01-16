#pragma once

#include <memory>

namespace Engine
{
	class Engine
	{
	  public:
		Engine(int windowWidth, int windowHeight, const char* windowTitle);
		~Engine();
		void Run();

	  private:
		std::unique_ptr<class Window> window;
	};
}
