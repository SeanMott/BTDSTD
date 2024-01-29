#include <BTDSTD/Input/Input.hpp>

#include <GLFW/glfw3.h>

//polls input for the OS
void BTD::Input::PollInput()
{
	glfwPollEvents();
}