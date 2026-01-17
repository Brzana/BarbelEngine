#include <Engine.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "Sandbox";

int main() {

	Engine::Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	engine.Run();

	return 0;
}
