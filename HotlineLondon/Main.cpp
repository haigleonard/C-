
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle
#include <windows.h>		// Header File For Windows
#include "Image_Loading/nvImage.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "math.h"
#include <time.h>
#include <MMSystem.h>
#include "Map.h"
#include "Player.h"
#include "OBB.h"
#include "Police.h"
Police police1;
Map map;
Player player;
OBB obbplayer, Buildings, policeobb, policeobbBack;
GLuint roadHor, roadVer, roofTex, playerCar, policeTexB, policeTexR;
int	mouse_x=0, mouse_y=0;
bool LeftPressed = false;
int screenWidth=1000, screenHeight=800;
bool keys[256];
float playerMatrix[16], buildingMatrix[16], policeMatrix[16];
//OPENGL FUNCTION PROTOTYPES
void display();				//draws everything to the screen
void reshape(int width, int height);//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();			//called in winmain to process keyboard controls

GLuint loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if(img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}

void init()
{
	roadHor = loadPNG("road.png");
	roadVer = loadPNG("road2.png");
	roofTex = loadPNG("roof.png");
	playerCar = loadPNG("playercar.png");
	policeTexB = loadPNG("policeBlue.png");
	policeTexR = loadPNG("policeRed.png");
	obbplayer.setID("Player");
	policeobb.setID("Police");
	policeobbBack.setID("PoliceBack");
	Buildings.setID("Building");
	obbplayer.vertOriginal[0].x = -2;
	obbplayer.vertOriginal[0].y = -2;

	obbplayer.vertOriginal[1].x = -2;
	obbplayer.vertOriginal[1].y = 2;

	obbplayer.vertOriginal[2].x = 2;
	obbplayer.vertOriginal[2].y = 2;

	obbplayer.vertOriginal[3].x = 2;
	obbplayer.vertOriginal[3].y = -2;

	policeobb.vertOriginal[0].x = -0.5;
	policeobb.vertOriginal[0].y = 0.5;

	policeobb.vertOriginal[1].x = -0.5;
	policeobb.vertOriginal[1].y = 1.5;

	policeobb.vertOriginal[2].x = 0.5;
	policeobb.vertOriginal[2].y = 1.5;

	policeobb.vertOriginal[3].x = 0.5;
	policeobb.vertOriginal[3].y = 0.5;

	policeobbBack.vertOriginal[0].x = -0.5;
	policeobbBack.vertOriginal[0].y = -1.5;

	policeobbBack.vertOriginal[1].x = -0.5;
	policeobbBack.vertOriginal[1].y = -0.5;

	policeobbBack.vertOriginal[2].x = 0.5;
	policeobbBack.vertOriginal[2].y = -0.5;

	policeobbBack.vertOriginal[3].x = 0.5;
	policeobbBack.vertOriginal[3].y = -1.5;
}


void collisionDetection(OBB obb1, OBB obb2, float mat1[16], float mat2[16] )
{
	obb1.transformPoints(mat1);
	obb2.transformPoints(mat2);

	if (obb1.SAT2D(obb2)) {
		if (obb1.idString == "Police" || obb1.idString == "PoliceBack") {
			police1.turn();
			if (obb1.idString == "PoliceBack") {
				police1.crossRoad = true;
			}
			glColor3f(0.0, 0.0, 1.0);
		}
	}
	else {
		glColor3f(1.0, 0.0, 1.0);
	}
	obb1.drawOBB();

	obb2.drawOBB();
}
void drawCar(GLuint tex)
{
	glLoadIdentity();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(player.x, player.y, 0);
	glRotatef(player.a, 0.0, 0.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, playerMatrix);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2f(-2, -2);
	glTexCoord2f(0.0, 1.0); glVertex2f(-2, 2);
	glTexCoord2f(1.0, 1.0); glVertex2f(2, 2);
	glTexCoord2f(1.0, 0.0); glVertex2f(2, -2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}

void drawPolice(GLuint tex)
{
	glLoadIdentity();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(police1.getX()+7, police1.getY()+7, 0);
	glRotatef(police1.getA(), 0.0, 0.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, policeMatrix);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2f(-2, -2);
	glTexCoord2f(0.0, 1.0); glVertex2f(-2, 2);
	glTexCoord2f(1.0, 1.0); glVertex2f(2, 2);
	glTexCoord2f(1.0, 0.0); glVertex2f(2, -2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();
	
}


void drawMap(int i, int e, GLuint tex)
{
	glLoadIdentity();
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	if (tex == roofTex) {
		Buildings.vertOriginal[0].x = i * 5;
		Buildings.vertOriginal[0].y = e * 5;

		Buildings.vertOriginal[1].x = i * 5;
		Buildings.vertOriginal[1].y = e * 5 + 5;

		Buildings.vertOriginal[2].x = i * 5 + 5;
		Buildings.vertOriginal[2].y = e * 5 + 5;

		Buildings.vertOriginal[3].x = i * 5 + 5;
		Buildings.vertOriginal[3].y = e * 5;
	}
	glGetFloatv(GL_MODELVIEW_MATRIX, buildingMatrix);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2f(i*5, e*5);
	glTexCoord2f(0.0, 1.0); glVertex2f(i * 5, e * 5 + 5);
	glTexCoord2f(1.0, 1.0); glVertex2f(i * 5 + 5, e * 5 + 5);
	glTexCoord2f(1.0, 0.0); glVertex2f(i * 5 + 5, e * 5);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	collisionDetection(Buildings, obbplayer, buildingMatrix, playerMatrix);
	
	
	glFlush();
}
void camera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(player.x - player.zoom, player.x + player.zoom, player.y - player.zoom, player.y + player.zoom);
	glMatrixMode(GL_MODELVIEW);
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	camera();
	for (int e = 30; e >= 0; e--) {
		for (int i = 30; i >= 0; i--) {
			if (map.mapCoor[i][e] == 0) {
				//draw(i,e, roadVer);
			}
			if (map.mapCoor[i][e] == 1) {
				drawMap(i, e, roofTex);
				collisionDetection(policeobb, Buildings, policeMatrix, buildingMatrix);
			}
			if (map.mapCoor[i][e] == 2) {
				drawMap(i, e, roadHor);
			}
			if (map.mapCoor[i][e] == 3) {
				drawMap(i, e, roadVer);
			}
			if (map.mapCoor[i][e] == 4) {
				drawMap(i, e, roofTex);
				collisionDetection(policeobbBack, Buildings, policeMatrix, buildingMatrix);
			}

			
		}
	}
	
	drawCar(playerCar);
	if (police1.siren) {
		drawPolice(policeTexB);
	}
	else {
		drawPolice(policeTexR);
	}

	
	police1.updateCar();
	police1.accelerate();
	player.updateCar();
	glFlush();
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth=width; screenHeight = height;           // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluOrtho2D(-100,100,-100,100);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


void processKeys()
{
	if (keys[VK_UP])
	{
		player.accelerate(); 
	}
	else {
		player.pedalOff();
	}
	if (keys[VK_DOWN])
	{
		player.brake();
		player.reverse();
	}
	if (keys[VK_LEFT])
	{
		player.left();
	}
	if (keys[VK_RIGHT])
	{
		player.right();
	}

}

/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done=false;								// Bool Variable To Exit Loop

	// Create Our OpenGL Window
	if (!CreateGLWindow("Hotline London",screenWidth,screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if(keys[VK_ESCAPE])
				done = true;

			processKeys();

			display();					// Draw The Scene
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			reshape(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;

		case WM_LBUTTONDOWN:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight - HIWORD(lParam);
				LeftPressed = true;
			}
		break;

		case WM_LBUTTONUP:
			{
	            LeftPressed = false;
			}
		break;

		case WM_MOUSEMOVE:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight  - HIWORD(lParam);
			}
		break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		break;

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/
 
bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();
	
	return true;									// Success
}