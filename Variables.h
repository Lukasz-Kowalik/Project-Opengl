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
constexpr int countOfLights = 10;
enum {
	EXIT,
	ON,
	OFF,
	ALL,
};
enum textures {
	WALL,
	FRONT_WALL,
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


lights light0Status = L0OFF;
GLfloat light0_position[] = { 0,1.0f, 2, 0.5f };
GLfloat light0_direction[] = { 0,1,0 };

lights light1Status = L1OFF;
GLfloat light1_positionMorning[] = { 2.0f, 0.1f, 0.1f, 1.0f };
GLfloat light1_positionEvning[] = { -2.0f, 0.5f, 0.5f,1.0f };
GLfloat light1_positionMidday[] = { 1.0f, 1.0f, 1.0f,1.0f };
GLfloat *light1_position= light1_positionMidday;

GLfloat morningLight[]=  { 0,1,1,1 };
GLfloat middayLight[]=  { 1,1,1,1 };
GLfloat evningLight[]=  { 1,0,0,1 };

GLfloat directioMorning[] = { 3,-2,-1 };
GLfloat directioMidday[] = { 0,0,-1 };
GLfloat directioEvning[] = { -2,1,-3};

GLfloat *light1_direction=directioMidday;
GLfloat *light1_specular= middayLight;
GLfloat *light1_diffuse= middayLight;
GLfloat *light1_ambient = light1_positionMidday;
GLfloat light1Spot_cutoff = 70.0f;
GLfloat light1Spot_exponent = 2.0f;
//shadow matrices
GLPMatrix ShadowMatrixForLight0;
GLPMatrix ShadowMatrixForLight1;
GLPMatrix ShadowMatrixForLight1AndLight2;
GLPMatrix ShadowMatrixEmpty;

GLPVector3 vPoints[3] = {
	{-1.0f,-1.0f,-1.5f},
	{1.0f ,-1.0f,-1.5f},
	{0.0f ,-1.0f, -3.0f}
};
GLPVector3 vPoints2[3] = {
	{0.0f, -1.5f,  0.0f},
	{10.0f, -1.5f,  0.0f},
	{5.0f, -1.5f, -5.0f}
};
GLPVector3 bezCienia[3] = {
	{0.0f, -50.5f,  0.0f},
	{10.0f, -50.5f,  0.0f},
	{ 5.0f, -50.5f, -5.0f}
};

//camera
GLPFrame frameCamera;

//textures
GLuint textures[amountOfTextures];
const char* textureFile[amountOfTextures] = { "textures/brickwall.tga","textures/brickwall2.tga","textures/road.tga","textures/grass.tga" };

//car movment
GLfloat positionX = 0.0f, positionZ = 0.0f, positionY = 0.0f;
GLint turnCar = 0, turnAngle = 45;;
GLfloat* directionHorizontal = &positionX;
GLfloat* directionVertical = &positionZ;
bool isTheCarFrontFacingLeft = true;
bool rightTurnWasUsed = false;

//fog
GLint fog_hint = GL_NICEST;
GLfloat fog_start = 1, fog_end = 10, fog_density = 0.5,
fog_mode = GL_EXP2;

windowScale aspect = FULL_WINDOW;

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

					    -Sterowanie samochodem-
						-> w - do przody
						-> s - do tylu
						-> a - lewo
						-> d - prawo

						-Oswietlenie-
				-> m - Ustawienie light1 na wartosci swiatla porannego
				-> n - Ustawienie light1 na wartosci swiatla poludniowego
				-> b - Ustawienie light1 na wartosci swiatla wieczornego
				-> , - zwieksza rozwarcie reflektora
				-> . - zmniejsza rozwarcie reflektora
				-> k - zwieksza skupienie reflektora
				-> l - zmniejsza skupienie reflektora

						-Podreczne menu-
		  		-> Skalowanie obrazu:
					-> Cale okno
					-> Proporcjonalne
		  		-> Rzutowanie obrazu:
					-> Frustrum
					-> Perspective
		  		-> Mgla:
					-> Wl
					-> Wyl
		  		-> Wyjscie z programu
		  	-----------------------------------------------------------------
)";
