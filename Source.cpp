//disable warnings
#pragma warning( push )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26451 )

#include "stdafx.h"
#include "Variables.h"

void TextureLoad() {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(AMOUNT_OF_TEXTURES, textures);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < AMOUNT_OF_TEXTURES; i++)
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

void TurnOnLight0() {
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);

	glLightModeli(GL_LIGHT_MODEL_AMBIENT, light0Status);
	glutPostRedisplay();
}
void TurnOnLight1() {
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, powerfulLight);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);
	glLightModeli(GL_LIGHT_MODEL_AMBIENT, light1Status);

	/*glColorMaterial(GL_FRONT, GL_SPECULAR);*/
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	/*glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);*/
	glutPostRedisplay();
}

void DrawWheel(GLfloat radiuse, GLfloat shiftByX, GLfloat shiftByY) {
	GLfloat x, y, angle;
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0.0f; angle < (2.0f * GL_PI);
		angle += (GL_PI / 32.0f))
	{
		x = radiuse * sin(angle) + shiftByX;
		y = radiuse * cos(angle) + shiftByY;
		glVertex2f(x, y);
	}glEnd();
	glPopMatrix();
}
void DrawRoad() {
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
	glVertex3f(-GROUND_WIDTH, GROUND_Y, GROUND_HEIGHT);

	glTexCoord2f(0, 0);
	glVertex3f(GROUND_WIDTH, GROUND_Y, GROUND_HEIGHT);

	glTexCoord2f(1, 0);
	glVertex3f(GROUND_WIDTH, GROUND_Y, -GROUND_HEIGHT);

	glTexCoord2f(1, 1);
	glVertex3f(-GROUND_WIDTH, GROUND_Y, -GROUND_HEIGHT);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void DrawGrass() {
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
	glVertex3f(-GROUND_WIDTH, GROUND_Y, GROUND_HEIGHT);

	glTexCoord2f(0, 0);
	glVertex3f(GROUND_WIDTH, GROUND_Y, GROUND_HEIGHT);

	glTexCoord2f(1, 0);
	glVertex3f(GROUND_WIDTH, GROUND_Y, -GROUND_HEIGHT);

	glTexCoord2f(1, 1);
	glVertex3f(-GROUND_WIDTH, GROUND_Y, -GROUND_HEIGHT);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void DrawBody() {
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
	glVertex3f(x2r, y2u, zb);
	glVertex3f(-x2r, y2u, zb);
	glVertex3f(-x2r, yu, zb);
	glVertex3f(x2r, yu, zb);

	//front wall
	glVertex3f(xl, yu, -zf);
	glVertex3f(xr, yu, -zf);
	glVertex3f(xr, yd, -zf);
	glVertex3f(xl, yd, -zf);
	glVertex3f(x2r, y2u, zf);
	glVertex3f(-x2r, y2u, zf);
	glVertex3f(-x2r, yu, zf);
	glVertex3f(x2r, yu, zf);

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

	//left wall
	glVertex3f(-x2r, yu, zb);
	glVertex3f(-x2r, yu, zf);
	glVertex3f(-x2r, y2u, zf);
	glVertex3f(-x2r, y2u, zb);
	glVertex3f(xl, yu, zb);
	glVertex3f(xl, yd, zb);
	glVertex3f(xl, yd, zf);
	glVertex3f(xl, yu, zf);

	// right wall
	glVertex3f(x2r, yu, zb);
	glVertex3f(x2r, yu, zf);
	glVertex3f(x2r, y2u, zf);
	glVertex3f(x2r, y2u, zb);
	glVertex3f(xr, yu, zb);
	glVertex3f(xr, yd, zb);
	glVertex3f(xr, yd, zf);
	glVertex3f(xr, yu, zf);

	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
void DrawCar() {
	const GLfloat scale = 0.5;
	glPushMatrix();
	glTranslatef(2, -0.45f, -2);
	glScalef(scale, scale, scale);

	DrawBody();
	//glColor3fv(White);

	//glTranslatef(0, 0, -1.3);
	//DrawWheel(0.2,-0.4,0);
	//glTranslatef(0, 0, +1.3);
	glPopMatrix();
}
void DrawHouse() {
	const float x = 1, y = -1, z = GROUND_HEIGHT / 2;

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
void DrawLights() {
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
		glTranslatef(startPositionX + i * LIGHT_MULTIPLAYER, -0.3f, dystanceZ);
		glColor4fv(LightGoldenrodYellow2);
		glTranslatef(0.3f, -0.5f, -0.5f);
		glutSolidSphere(0.15, 20, 20);
		glDisable(GL_BLEND);

		glPopMatrix();
		glPushMatrix();
		glScalef(sacale, sacale, sacale);
		glTranslatef(startPositionX + 0.3f + i * LIGHT_MULTIPLAYER, -1.7f, dystanceZ - 0.5f);
		glScaled(0.2, 3, 0.15);
		glColor3fv(DarkGray);
		glutSolidCube(0.5);

		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}
void Draw() {
	DrawGrass();
	DrawRoad();

	glutSolidSphere(0.15, 20, 20);

	DrawHouse();
	DrawCar();
	DrawLights();

	TurnOnLight0();
	TurnOnLight1();
}
void SetLights(unsigned char key) {
	switch (key)
	{
	case '1':
	{
		if (light0Status == L0OFF) {
			light0Status = L0ON;
			glEnable(GL_LIGHT0);
		}
		else
		{
			light0Status = L0OFF;
			glDisable(GL_LIGHT0);
		}
	}
	break;
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
	}break;
	default:
		break;
	}
}

//projection begin
void projectionFrustrum(int width, int height)
{
	// parametry bry³y obcinania
	if (Aspect == ASPECT_1_1)
	{
		// wysokoœæ okna wiêksza od wysokoœci okna
		if (width < height && width > 0)
			glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1.0, WIEV_DISTANCE);
		else

			// szerokoœæ okna wiêksza lub równa wysokoœci okna
			if (width >= height && height > 0)
				glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1.0, WIEV_DISTANCE);
	}
	else
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, WIEV_DISTANCE);
}
void projectionPerspective(int width, int height) {
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble)height;
	gluPerspective(FOV, aspect, 1.0, WIEV_DISTANCE);
}
//projection end

void Display()
{
	// kolor t³a - zawartoœæ bufora koloru
	//glClearColor(0.25, 0.25, 0.25, 0.25);
	//glColor3fv(DimGray);
	// czyszczenie bufora koloru
//	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH);
	glpApplyCameraTransform(&frameCamera);

	glTranslatef(translatex, translatey, 0.0);
	glScalef(scale, scale, scale);

	Draw();

	glFlush();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH);
	glutSwapBuffers();
}

void Reshape(int width, int height) {
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
void Menu(int value)
{
	if (value == EXIT) {
		glDeleteTextures(AMOUNT_OF_TEXTURES, textures);
		exit(0);
	}
}
void MouseButton(int button, int state, int x, int y)
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
void MouseMotion(int x, int y)
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
void Keyboard(unsigned char key, int x, int y)
{
	if (activeProjection == frustum)
	{
		if (key == '+')
			scale += 0.1f;
		else
			if (key == '-' && scale > 0.1f)
				scale -= 0.1f;
	}
	else if (activeProjection == perspective)
	{
		if (key == '-' && FOV < 180)
			FOV++;
		else
			if (key == '+' && FOV > 0)
				FOV--;
	}
	SetLights(key);
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
void SpecialKeys(int key, int x, int y)
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
void ScaleMenu(int sc) {
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
void ProjectionMenu(int p) {
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

void MainMenu() {
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
void static Controls(bool t = true) {
	if (t) {
		FreeConsole();
		return;
	}
	std::cout << Info;
}
int main(int argc, char* argv[])
{
	Controls();

	glutInit(&argc, argv);

	glutInitWindowSize(WINOWO_WIDTH, WINDOW_HEIGHT);
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