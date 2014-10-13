#pragma once

#include "GLFW\glfw3.h"

class GLAHInput
{
public:
	void Initialise(GLFWwindow* window_);
	static GLAHInput* Instance();
	~GLAHInput(void);

	//////////////////////////////////////////////////////////////////////////

// Input Handling Functionality

//////////////////////////////////////////////////////////////////////////

 bool			IsKeyDown( int a_iKey );

 void			GetMouseLocation( double& a_iMouseX, double& a_iMouseY );

 bool			GetMouseButtonDown( int a_iMouseButtonToTest );

 bool			GetMouseButtonReleased( int a_iMouseButtonToTest );


private:
	GLAHInput();
	GLFWwindow* window;
	static GLAHInput* instance;
};