#define _USE_MATH_DEFINES


#include "GLAHGame.h"
#include "Matrix.h"
#include <math.h>
#include "GLAHInput.h"

using namespace std;

void GLAH::Run()
{
	while( FrameworkUpdate() )
	{
		Update(GetDeltaTime());
		Draw();
	}
	Shutdown();
}

GLAH::GLAH(int a_iWidth, int a_iHeight, bool a_bFullscreen, const char* a_pWindowTitle)
{
	Initialise(a_iWidth, a_iHeight, a_bFullscreen, a_pWindowTitle);
}

void GLFWErroCallback(int errorCode_, const char *errStr_)
{
	cout << "GLFW error: " << errStr_ << endl;
}

//////////////////////////////////////////////////////////////////////////
/// @brief Call this function to initialise the framework 
/// @param a_iWidth the width in pixels that we want the screen to display for the width of the window
/// @param a_height the width in pixels that we want the screen to display for the height of the window
/// @param a_bFullscreen should this application run in a fullscreen mode.
/// @param a_pWIndowTitle the title that we want to be displayed in the windows title bar
//////////////////////////////////////////////////////////////////////////
int	GLAH::Initialise( int a_iWidth, int a_iHeight, bool a_bFullscreen, const char* a_pWindowTitle)
{
	glfwSetErrorCallback(GLFWErroCallback);

	//Initialise GLFW
    if(!glfwInit())
    {
            return -1;
    }

	//TODO not currently using a_bFullscreen.
    //create a windowed mode window and it's OpenGL context    
    window = glfwCreateWindow(a_iWidth, a_iHeight, a_pWindowTitle, NULL, NULL);

    if(!window)
    {
            glfwTerminate();
            return -1;
    }
 
    //make the window's context current
    glfwMakeContextCurrent(window);

	//initialise input lib
	GLAHInput* input = GLAHInput::Instance();
	input->Initialise(window);
 
    //init glew
    if (glewInit() != GLEW_OK)
    {
            // OpenGL didn't start-up! shutdown GLFW and return an error code
            glfwTerminate();
            return -1;
    }

	//create shader program
    GLuint uiProgramFlat = CreateProgram("resources/VertexShader.glsl", "resources/FlatFragmentShader.glsl");
 
    //find the position of the matrix variable in the shader so we can send info there later
    GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");
 
    //set up the mapping of the screen to pixel co-ordinates. Try changing these values to see what happens.	
    float* orthographicProjection = Matrix4x4::GetOrtho(0, a_iWidth, 0, a_iHeight, 0, 100);
	//float* orthographicProjection2 = getOrtho(0, a_iWidth, 0, a_iHeight, 0, 100);
	//orthographicProjection = getOrtho(-1, 1, -1, 1, 0, 100);

	//GenerateVBO();

	//create VBO/IBO	
    glGenBuffers(1, &VBO);                                                                                                                                  //generate VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                                                                             //Binds VBO once
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, NULL, GL_STREAM_DRAW);                  //Reserves the memory on graphics card
    //glBindBuffer(GL_ARRAY_BUFFER, NULL);                                                                                                  //We won't unbind as we'll pass data using glBufferSubData
    glEnableVertexAttribArray(0);                                                                                                                           //position - location
    glEnableVertexAttribArray(1);              
	glEnableVertexAttribArray(2); //texture coordinates//colour
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector4)*2));	

	//turn on transparency
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
    //if(IBO == NULL)
    //{
    //        glGenBuffers(1, &IBO);                                                                                                                                  //generate IBO
    //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);                                                     //binds IBO
    //        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(char), NULL, GL_STATIC_DRAW);                    //reserves memory on graphics card
    //        GLvoid *iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);                          //Gets pointer to space on graphics card
 
    //        ((char*)iBuffer)[0] = 3;                                                                                                                        //Populate indices - done here as only required once.
    //        ((char*)iBuffer)[1] = 0;
    //        ((char*)iBuffer)[2] = 2;
    //        ((char*)iBuffer)[3] = 1;
 
    //        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(char), iBuffer, GL_STATIC_DRAW);                 //copy data to graphics card
    //        //No need to unbind as IBO is not changing and will be used every call
    //}	

	glUseProgram(uiProgramFlat); 

	glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

	timeBegin = high_resolution_clock::now();

	return 0;
}

//////////////////////////////////////////////////////////////////////////
/// @brief This function is to be called each frame to update the current frame. 
/// @return a boolean value indicating that the framework updated successfully
//////////////////////////////////////////////////////////////////////////
bool GLAH::FrameworkUpdate()
{
	if (glfwWindowShouldClose(window))
		return false;

	CalculateDelta();

	//swap front and back buffers
	glfwSwapBuffers(window);
 
    //poll for and process events
	glfwPollEvents();

	glClearColor(0.25f, 0.25f, 0.25f, 0.25f);
    glClear(GL_COLOR_BUFFER_BIT);
 
	return true;
}






//Calculate Delta time (time in miliseconds since last update)
void GLAH::CalculateDelta()
{
	timeEnd = high_resolution_clock::now();
	delta =  duration_cast<duration<double>>(timeEnd - timeBegin).count();
	timeBegin = high_resolution_clock::now();
}

//Return time in miliseconds since last update
double GLAH::GetDeltaTime()
{
	return delta;
}

double GLAH::FPS()
{
	return 1 / delta;
}

//////////////////////////////////////////////////////////////////////////
/// @brief This function should be called just prior to exiting your program
///			 it will unload all the components of the AIE Framework that have been loaded
//////////////////////////////////////////////////////////////////////////
void GLAH::Shutdown()
{
		glDeleteBuffers( 1, &IBO );
		glDeleteBuffers( 1, &VBO );
        glfwTerminate();
}

