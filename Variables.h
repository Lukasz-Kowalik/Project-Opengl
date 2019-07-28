#pragma once

#define WINOWO_WIDTH  600
#define WINDOW_HEIGHT  600
#define AMOUNT_OF_TEXTURES 4
#define WALL 0
#define WALL2 1
#define ROAD 2
#define GRASS 3
#define WIEV_DISTANCE 10
#define LIGHT_MULTIPLAYER 1.75
#define GROUND_WIDTH 9
#define GROUND_HEIGHT 3
#define GROUND_Y -1

enum { EXIT, ON, OFF, ALL };
enum scale {
	FULL_WINDOW,
	ASPECT_1_1
};
enum projection {
	frustum,
	perspective
};
//light
enum lights { L0ON, L0OFF, L1ON, L1OFF};
enum state{O,F};
lights light0Status = L0OFF;
GLfloat light0_position[] = { 0,-0.1f, -1, 0.5f };
GLfloat light0_direction[]={0,1,0};

lights light1Status = L1OFF;
//GLfloat light1_position[] = {1.5,1.55,-2.375 ,1.0 };
GLfloat light1_position[] = {1,-0.75,-2.5,1 };
GLfloat light1_direction[]={1,0,0 };
GLfloat light1_specular[]={1,1,1,1};

GLfloat weakLight[] = { 0.01f, 0.01f, 0.01f, 1.0f };
GLfloat mediumLight[] = { 0.5f, 0.5f, 0.5f,1.0f };
GLfloat powerfulLight[] = { 1.0f, 1.0f, 1.0f,1.0f };

// macierze cieni typu matrix
GLPMatrix Macierz_cieni;
GLPMatrix Macierz_cieni2;
// kolor cienia
GLfloat fKolor_cienia[] = { 0.0f,0.0f,0.0f,0.0f };
// cien powinien znajdowac sie troszke nad podloga
GLPVector3 vPoints[3] = { {0.0f, -1.9f,  0.0f},
						 {10.0f, -1.9f,  0.0f},
						  {5.0f, -1.9f, -5.0f} };
GLPVector3 vPoints2[3] = { {0.0f, -1.5f,  0.0f},
						  {10.0f, -1.5f,  0.0f},
						   {5.0f, -1.5f, -5.0f} };
GLPVector3 bezCienia[3] = { {0.0f, -50.5f,  0.0f},
						   {10.0f, -50.5f,  0.0f},
						   { 5.0f, -50.5f, -5.0f} };

//camera
GLPFrame frameCamera;
//textures
GLuint textures[AMOUNT_OF_TEXTURES];
const char* textureFile[AMOUNT_OF_TEXTURES] = { "textures/brickwall.tga","textures/brickwall2.tga","textures/road.tga","textures/grass.tga" };

//variables begin
int Aspect = FULL_WINDOW;
int depthStatuse = ON;
//projection
projection activeProjection = perspective;
GLdouble FOV = 90;
GLfloat scale = 1.0;
float translatex = 0.0, translatey = 0.0;
//mouse motion
int button_state = GLUT_UP;
int button_x, button_y;
GLfloat right = 3, left = -3, top = 3, bottom = -3;
//variables end
const static GLfloat GL_PI = 3.1415f;
//Control info
const static int countOfLights = 10;
const char* Info = R"(
						STEROWANIE
		  	-----------------------------------------------------------------
		  				 -Strzalki-
		  		->	Lewo/Prawo - ruch kamery
		  		->	Gora/Dol - obrot sceny

		  				-Klawiatura-
		  		-> 1-2 - wl/wyl oswietlenie 1-2

						   -MYSZ-
		  		-> mysz - przemieszczanie szceny
				-> strza³ki lewo/prawo ruch kamery w lewo/prawo
		  			Reszta sterowania odbywa sie poprzez menu
		  	-----------------------------------------------------------------
)";
