//disable warnings
#pragma warning( push )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26451 )

#include "stdafx.h"
#include "Variables.h"

static void TextureLoad() {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(amountOfTextures, textures);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < amountOfTextures; i++)
	{
		GLubyte* pBytes;
		GLint iWidth, iHeight, iComponents;
		GLenum eFormat;
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		pBytes = glploadtga(textureFile[i], &iWidth, &iHeight, &iComponents, &eFormat);
		gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
		free(pBytes);
	}
}

static void TurnOnLight0() {
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);

	glLightModeli(GL_LIGHT_MODEL_AMBIENT, light0Status);
	glutPostRedisplay();
}
static void TurnOnLight1() {
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, powerfulLight);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 35.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);
	glLightModeli(GL_LIGHT_MODEL_AMBIENT, light1Status);

	glutPostRedisplay();
}

static void DrawWheels() {
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3fv(Gray);

	glTranslatef(-0.5, -0.86, -0.7);
	glutSolidSphere(0.25, 10, 10);

	glTranslatef(0, 0, 0.7);
	glutSolidSphere(0.25, 10, 10);

	glTranslatef(1, 0, 0);
	glutSolidSphere(0.25, 10, 10);

	glTranslatef(0, 0, -0.7);
	glutSolidSphere(0.25, 10, 10);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
static void DrawRoad() {
	glBindTexture(GL_TEXTURE_2D, textures[ROAD]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glColor3fv(White);
	glTranslatef(0, 0, 6);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	//kwadrat
	glBegin(GL_QUADS);
	glColor3fv(White);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 1);  // okreœlenie pierwszej wspó³rzêdnej tekstury
	glVertex3f(-groundWidth, groundY, groundHeight);

	glTexCoord2f(0, 0);
	glVertex3f(groundWidth, groundY, groundHeight);

	glTexCoord2f(1, 0);
	glVertex3f(groundWidth, groundY, -groundHeight);

	glTexCoord2f(1, 1);
	glVertex3f(-groundWidth, groundY, -groundHeight);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
static void DrawGrass() {
	glBindTexture(GL_TEXTURE_2D, textures[GRASS]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glColor3fv(White);
	glTranslatef(0, -1, -4);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	//kwadrat
	glBegin(GL_QUADS);
	glColor3fv(White);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 1);  // okreœlenie pierwszej wspó³rzêdnej tekstury
	glVertex3f(-groundWidth, groundY, groundHeight);

	glTexCoord2f(0, 0);
	glVertex3f(groundWidth, groundY, groundHeight);

	glTexCoord2f(1, 0);
	glVertex3f(groundWidth, groundY, -groundHeight);

	glTexCoord2f(1, 1);
	glVertex3f(-groundWidth, groundY, -groundHeight);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
static void DrawBody() {
	float xr = 1.0f, xl = -1.0f, x2r = 0.4f, yu = 1.0f, yd = 0.1f, y2u = 1.4f, zf = 0.0f, zb = -0.75f;
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3fv(Yellow);
	glTranslatef(0, -1, 0);
	glBegin(GL_QUADS);
	//back wall
	glVertex3f(xl, yu, zb);
	glVertex3f(xr, yu, zb);
	glVertex3f(xr, yd, zb);
	glVertex3f(xl, yd, zb);

	//front wall
	glVertex3f(xl, yu, -zf);
	glVertex3f(xr, yu, -zf);
	glVertex3f(xr, yd, -zf);
	glVertex3f(xl, yd, -zf);

	//wall down
	glVertex3f(xl, yd, zb);
	glVertex3f(xr, yd, zb);
	glVertex3f(xr, yd, zf);
	glVertex3f(xl, yd, zf);

	//car roof
	glVertex3f(xl, yu, zb);
	glVertex3f(-x2r, yu, zb);
	glVertex3f(-x2r, yu, zf);
	glVertex3f(xl, yu, zf);
	glVertex3f(-x2r, y2u, zf);
	glVertex3f(-x2r, y2u, zb);
	glVertex3f(x2r, y2u, zb);
	glVertex3f(x2r, y2u, zf);
	glVertex3f(xr, yu, zb);
	glVertex3f(x2r, yu, zb);
	glVertex3f(x2r, yu, zf);
	glVertex3f(xr, yu, zf);

	// right wall
	glVertex3f(xr, yu, zb);
	glVertex3f(xr, yd, zb);
	glVertex3f(xr, yd, zf);
	glVertex3f(xr, yu, zf);

	//left wall
	glColor3fv(Red);
	glVertex3f(xl, yu, zb);
	glVertex3f(xl, yd, zb);
	glVertex3f(xl, yd, zf);
	glVertex3f(xl, yu, zf);

	//car window
	glColor3fv(Aqua);

	//left
	glVertex3f(-x2r, yu, zb);
	glVertex3f(-x2r, yu, zf);
	glVertex3f(-x2r, y2u, zf);
	glVertex3f(-x2r, y2u, zb);

	//right
	glVertex3f(x2r, yu, zb);
	glVertex3f(x2r, yu, zf);
	glVertex3f(x2r, y2u, zf);
	glVertex3f(x2r, y2u, zb);

	//front
	glVertex3f(x2r, y2u, zf);
	glVertex3f(-x2r, y2u, zf);
	glVertex3f(-x2r, yu, zf);
	glVertex3f(x2r, yu, zf);

	//back
	glVertex3f(x2r, y2u, zb);
	glVertex3f(-x2r, y2u, zb);
	glVertex3f(-x2r, yu, zb);
	glVertex3f(x2r, yu, zb);

	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
static void DrawCar() {
	const GLfloat scale = 0.5;
	glPushMatrix();
	glTranslatef(2.0f, -0.45f, -2.0f);
	glTranslatef(positionX, positionY, positionZ);
	glRotatef(turnCar, 0, 1, 0);
	glScalef(scale, scale, scale);

	DrawBody();
	DrawWheels();
	glPopMatrix();
}
static void DrawHouse() {
	const float x = 1, y = -1, z = groundHeight / 2;

	glBindTexture(GL_TEXTURE_2D, textures[WALL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glColor3fv(White);
	glPushMatrix();
	glTranslatef(0, 0, -5);

	glEnable(GL_TEXTURE_2D);
	//kwadrat
	glBegin(GL_QUADS);
	glColor3fv(White);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);

	glTexCoord2f(1, 0);
	glVertex3f(x, y, -z);

	glTexCoord2f(1, 1);
	glVertex3f(x, -y, -z);

	glTexCoord2f(0, 1);
	glVertex3f(x, -y, z);
	glEnd();
	//left wall
	glBegin(GL_QUADS);
	glColor3fv(White);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-x, y, z);

	glTexCoord2f(1, 0);
	glVertex3f(-x, y, -z);

	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, -z);

	glTexCoord2f(0, 1);
	glVertex3f(-x, -y, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//front wall
	glBindTexture(GL_TEXTURE_2D, textures[WALL2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glColor3fv(White);
	glPushMatrix();
	glTranslatef(0, 0, -5.0f);
	glEnable(GL_TEXTURE_2D);
	//kwadrat
	glBegin(GL_QUADS);
	glColor3fv(White);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, z);

	glTexCoord2f(0, 1);
	glVertex3f(x, -y, z);

	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);

	glTexCoord2f(1, 0);
	glVertex3f(-x, y, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glColor3fv(Gray);
	glBegin(GL_QUADS);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
static void DrawLights() {
	GLfloat startPositionX = -8.3f, startPositionY = -7.5f;
	GLfloat sacale = 0.4f, dystanceZ = -7.5f;

	for (size_t i = 0; i < countOfLights; i++)
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glEnable(GL_COLOR_MATERIAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glScalef(sacale, sacale, sacale);
		glTranslatef(startPositionX + i * lightMultiplayer, -0.3f, dystanceZ);
		glColor4fv(LightGoldenrodYellow2);
		glTranslatef(0.3f, -0.5f, -0.5f);
		glutSolidSphere(0.15, 20, 20);
		glDisable(GL_BLEND);

		glPopMatrix();
		glPushMatrix();
		glScalef(sacale, sacale, sacale);
		glTranslatef(startPositionX + 0.3f + i * lightMultiplayer, -1.7f, dystanceZ - 0.5f);
		glScaled(0.2, 3, 0.15);
		glColor3fv(DarkGray);
		glutSolidCube(0.5);

		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}
static void Draw() {
	DrawGrass();
	DrawRoad();

	glutSolidSphere(0.15, 20, 20);

	DrawHouse();
	DrawCar();
	DrawLights();

	TurnOnLight0();
	TurnOnLight1();
}
static void SetLights(unsigned char key) {
}

//projection begin
static void projectionFrustrum(int width, int height)
{
	// parametry bry³y obcinania
	if (Aspect == ASPECT_1_1)
	{
		// wysokoœæ okna wiêksza od wysokoœci okna
		if (width < height && width > 0)
			glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1.0, wievDistance);
		else

			// szerokoœæ okna wiêksza lub równa wysokoœci okna
			if (width >= height && height > 0)
				glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1.0, wievDistance);
	}
	else
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, wievDistance);
}
static void projectionPerspective(int width, int height) {
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble)height;
	gluPerspective(FOV, aspect, 1.0, wievDistance);
}
//projection end

static void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glpApplyCameraTransform(&frameCamera);

	glTranslatef(translatex, translatey, 0.0);
	glScalef(scale, scale, scale);

	Draw();

	glFlush();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

static void Reshape(int width, int height) {
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (frustum == activeProjection)
	{
		projectionFrustrum(width, height);
		glTranslatef(0, 0, -3);
	}
	else if (perspective == activeProjection)
	{
		projectionPerspective(width, height);
		glTranslatef(0, 0, -3);
	}
	Display();
}
// obsluga menu podrecznego
static void Menu(int value)
{
	if (value == EXIT) {
		glDeleteTextures(amountOfTextures, textures);
		exit(0);
	}
}
static void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiêtanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiêtanie po³o¿enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}
static void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		translatex += 1.1f * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		translatey += 1.1f * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}
static void ResetCarRadiuse() {
	if (turnCar >= 360 || turnCar <= -360)turnCar = 0;
}
static void TurnLeft() {
	turnCar += turnAngle;
	ResetCarRadiuse();

	rightTurnWasUsed = false;
	if (turnCar == 0)
	{
		directionHorizontal = &positionX;
		directionVertical = &positionZ;
		f = true;
	}
	else if (turnCar == 90) {
		directionHorizontal = &positionZ;
		directionVertical = &positionX;
		f = false;
	}
	else if (turnCar == 180)
	{
		directionHorizontal = &positionX;
		directionVertical = &positionZ;
		f = false;
	}
	else if (turnCar == 270)
	{
		directionHorizontal = &positionZ;
		directionVertical = &positionX;
		f = true;
	}
}
static void TurnRight() {
	if (turnCar == 0)turnCar = 360;
	turnCar -= turnAngle;
	ResetCarRadiuse();
	//if (turnCar == 0)
	//{
	//	directionHorizontal = &positionX;
	//	directionVertical = &positionZ;
	//	f = true;
	//}
	//else if (turnCar == 90) {
	//	directionHorizontal = &positionZ;
	//	directionVertical = &positionX;
	//	f = false;
	//}
	//else if (turnCar == 180)
	//{
	//	directionHorizontal = &positionX;
	//	directionVertical = &positionZ;
	//	f = false;
	//}
	//else if (turnCar == 270)
	//{
	//	directionHorizontal = &positionZ;
	//	directionVertical = &positionX;
	//	f = true;
	//}
	rightTurnWasUsed = true;
	switch (turnCar)
	{
	case 0:
	{
		directionHorizontal = &positionX;
		directionVertical = &positionZ;
		f = true;
		break;
	}

	case 90:
	{
		directionHorizontal = &positionZ;
		directionVertical = &positionX;
		f = false;
		break;
	}
	case 180:
	{
		directionHorizontal = &positionX;
		directionVertical = &positionZ;
		f = false;
		break;
	}
	case 270:
	{
		directionVertical = &positionX;
		directionHorizontal = &positionZ;
		f = true;
		break;
	}
	default:
		break;
	}
}
static void MoveForward(const GLfloat carSpeed) {
	if (f)
		* directionHorizontal -= carSpeed;
	else
		*directionHorizontal += carSpeed;
	switch (turnCar)
	{
	case 45: {
		if (rightTurnWasUsed) {
			*directionVertical -= carSpeed;
		}
		else
		{
			*directionHorizontal -= carSpeed;
			*directionVertical += carSpeed;
		}
		break;
	}
	case 135: {
		*directionHorizontal += carSpeed;
		*directionVertical += carSpeed;
		break;
	}
	case 225: {
		if (rightTurnWasUsed) {
			*directionVertical += carSpeed;
		}
		else {
			*directionHorizontal += carSpeed;
			*directionVertical -= carSpeed;
		}
		break;
	}
	case 315: {
		*directionHorizontal -= carSpeed;
		*directionVertical -= carSpeed;
		break;
	}
	default:

		break;
	}
}

static void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'-': {
		if (activeProjection == perspective && FOV < 180) {
			FOV++;
		}
		else if (scale > 0.1f) {
			scale -= 0.1f;
		}
		break;
	}
	case'+': {
		if (activeProjection == perspective && FOV > 0) {
			FOV--;
		}
		else {
			scale += 0.1f;
		}
		break;
	}
	case'w': { MoveForward(carSpeed);	break; }
	case's': { MoveForward(-carSpeed);  break; }
	case'a': { TurnLeft();				break; }
	case'd': { TurnRight();				break; }
	case '1': {
		if (light0Status == L0OFF) {
			light0Status = L0ON;
			glEnable(GL_LIGHT0);
		}
		else
		{
			light0Status = L0OFF;
			glDisable(GL_LIGHT0);
		}
		break;
	}
	case '2': {
		if (light1Status == L1OFF) {
			light1Status = L1ON;
			glEnable(GL_LIGHT1);
		}
		else
		{
			light1Status = L1OFF;
			glDisable(GL_LIGHT1);
		}
		break;
	}
	default:
		break;
	}

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
static void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		glpMoveFrameRight(&frameCamera, 0.02f);
		break;

	case GLUT_KEY_RIGHT:
		glpMoveFrameRight(&frameCamera, -0.02f);
		break;

	case GLUT_KEY_UP:
		glpMoveFrameForward(&frameCamera, 0.02f);
		break;

	case GLUT_KEY_DOWN:
		glpMoveFrameForward(&frameCamera, -0.02f);
		break;
	}
	Display();
}
static void ScaleMenu(int sc) {
	switch (sc)
	{
	case FULL_WINDOW:
		Aspect = FULL_WINDOW;
		break;
	case ASPECT_1_1:
		Aspect = ASPECT_1_1;
		break;
	default:
		break;
	}
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
static void ProjectionMenu(int p) {
	switch (p)
	{
	case frustum:
		activeProjection = frustum;
		break;
	case perspective:
		activeProjection = perspective;
		break;
	default:
		break;
	}
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

static void MainMenu() {
	//-------------------SCALE---------------------
	int menuAspect = glutCreateMenu(ScaleMenu);
#ifdef WIN32
	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - proporcjonalnie", ASPECT_1_1);
#else
	glutAddMenuEntry("Obszar renderingu - cale okno", FULL_WINDOW);
	glutAddMenuEntry("Obszar renderingu - proporcjonalnie", ASPECT_1_1);
#endif
	//-----------------PROJECTION---------------------
	int menuactiveProjection = glutCreateMenu(ProjectionMenu);
#ifdef WIN32
	glutAddMenuEntry("Perspektywiczne Frustum", frustum);
	glutAddMenuEntry("Perspektywiczne Perspective", perspective);
#else
	glutAddMenuEntry("Perspektywiczne Frustum", frustum);
	glutAddMenuEntry("Perspektywiczne Perspective", perspective);
#endif
	//--------------------------MAIN_MENU------------
	glutCreateMenu(Menu);
	glutAddSubMenu("Skala obrazu", menuAspect);
	glutAddSubMenu("Rzutowanie obrazu", menuactiveProjection);
#ifdef WIN32
	glutAddMenuEntry("Wyjscie", EXIT);
#else
	glutAddMenuEntry("Wyjscie", EXIT);
#endif
}
static void Controls(bool t = true) {
	if (t) {
		std::cout << Info;
		return;
	}
	FreeConsole();
}
int main(int argc, char* argv[])
{
	Controls(false);

	glutInit(&argc, argv);

	glutInitWindowSize(windowWidht, windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// utworzenie glownego okna programu
	glutCreateWindow("Projekt £ukasz Kowalik");

	glpInitFrame(&frameCamera);
	TextureLoad();

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);

	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);

	MainMenu();

	// okreœlenie przycisku myszki obslugujacej menu podreczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// wprowadzenie programu do obslugi petli komunikatow
	glutMainLoop();

	return 0;
}

#pragma warning(pop)