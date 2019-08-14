#pragma once

constexpr GLint windowHeight = 600;
constexpr GLint windowWidht = 600;
constexpr GLint amountOfTextures = 4;
constexpr GLfloat wievDistance = 10.0f;
constexpr GLfloat lightMultiplayer = 1.75f;
constexpr GLfloat groundY = -1.0f;
constexpr GLfloat groundHeight = 3.0f;
constexpr GLfloat groundWidth = 9.0f;
constexpr GLfloat carSpeed = 0.5f;
enum {
	EXIT,
	ON,
	OFF,
	ALL,
};
enum textures {
	WALL,
	WALL2,
	ROAD,
	GRASS
};

enum windowScale {
	FULL_WINDOW,
	ASPECT_1_1
};
enum projection {
	frustum,
	perspective
};
//light
enum lights {
	L0ON,
	L0OFF,
	L1ON,
	L1OFF
};
GLfloat weakLight[] = { 0.01f, 0.01f, 0.01f, 1.0f };
GLfloat mediumLight[] = { 0.5f, 0.5f, 0.5f,1.0f };
GLfloat powerfulLight[] = { 1.0f, 1.0f, 1.0f,1.0f };

lights light0Status = L0OFF;
GLfloat light0_position[] = { 0,-0.1f, -1, 0.5f };
GLfloat light0_direction[] = { 0,1,0 };

lights light1Status = L1OFF;
//GLfloat light1_position[] = {1.5,1.55,-2.375 ,1.0 };
GLfloat light1_position[] = { -1,-0.75,-2.5,1 };
GLfloat light1_direction[] = { 1,0,0 };
GLfloat light1_specular[] = { 1,1,1,1 };

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
GLuint textures[amountOfTextures];
const char* textureFile[amountOfTextures] = { "textures/brickwall.tga","textures/brickwall2.tga","textures/road.tga","textures/grass.tga" };

const static int countOfLights = 10;
//car movment
GLfloat positionX = 0.0f, positionZ = 0.0f, positionY = 0.0f, turnAngle = 45.0f;
GLint turnCar = 0;
GLfloat *directionHorizontal = &positionX;
GLfloat *directionVertical = &positionZ;
GLint lastAngle = turnCar;
bool f = true;
bool swapFlag = false;
bool rightTurnWasUsed = false;
bool leftTurnWasUsed = false;
windowScale Aspect = FULL_WINDOW;
//projection
projection activeProjection = perspective;
GLdouble FOV = 90;
GLfloat scale = 1.0;
float translatex = 0.0, translatey = 0.0;
//mouse motion
int button_state = GLUT_UP;
int button_x, button_y;
GLfloat right = 3, left = -3, top = 3, bottom = -3;

const static GLfloat GL_PI = 3.1415f;

const char* Info = R"(
						STEROWANIE
		  	-----------------------------------------------------------------
		  				 -Strzalki-
		  		->	Lewo/Prawo/Gora/Dol - ruch kamery

		  				-Klawiatura-
				-> +/- - przyblizenie/oddalenie kamery
		  		-> 1-2 - wl/wyl oswietlenie 1-2

					    Sterowanie samochodem:
						x w - do przody
						x s - do tylu
						x a - lewo
						x d - prawo

						   -MYSZ-
		  		-> mysz - przemieszczanie szceny
				-> strzalki lewo/prawo ruch kamery w lewo/prawo
		  			Reszta sterowania odbywa sie poprzez menu
		  	-----------------------------------------------------------------
)";
