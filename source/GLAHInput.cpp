#include "GLAHInput.h"
#include "GLFW\glfw3.h"

GLAHInput* GLAHInput::instance = nullptr;

GLAHInput::GLAHInput(void)
{
}


GLAHInput::~GLAHInput(void)
{
}

GLAHInput*
GLAHInput::Instance()
{
	if ( instance == nullptr )
	{
		instance = new GLAHInput();    
	}
	return instance;
}

void GLAHInput::Initialise(GLFWwindow* window_)
{		
	instance->window = window_;
}

//INPUT HANDLING-------------------------------------------------------
///////////////////////////////////////////////////////////////////////
bool GLAHInput::IsKeyDown( int key_ )
{
	if (glfwGetKey(window,key_))
		return true;
	return false;
}

bool GLAHInput::GetMouseButtonDown( int a_iMouseButtonToTest )
{
	if(glfwGetMouseButton(window, a_iMouseButtonToTest) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

void GLAHInput::GetMouseLocation( double& a_iMouseX, double& a_iMouseY )
{
	glfwGetCursorPos(window, &a_iMouseX, &a_iMouseY);
}
//END INPUT HANDLING
///////////////////////////////////////////////////////////////////////