//disable warnings
#pragma warning( disable : 4305 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26451 )

#include "stdafx.h"
#include "Variables.h"

void SetLight0()
{
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
	glLightModeli(GL_LIGHT_MODEL_AMBIENT, light0Status);

	glutPostRedisplay();
	glpMakeShadowMatrix(vPoints, light0_position, ShadowMatrixForLight0);
	glpMakeShadowMatrix(vPoints, light0_position, ShadowMatrixForLight1AndLight2);
}
void SetLight1()
{
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1Spot_cutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light1Spot_exponent);
	glLightModeli(GL_LIGHT_MODEL_AMBIENT, light1Status);

	glpMakeShadowMatrix(vPoints, light1_position, ShadowMatrixForLight1);
	glpMakeShadowMatrix(vPoints, light1_position, ShadowMatrixForLight1AndLight2);

	glutPostRedisplay();
}
void SetMorningLight()
{
	glClearColor(LightBlue[0], LightBlue[1], LightBlue[2], LightBlue[3]);
	light1Spot_cutoff = 70;
	light1Spot_exponent = 2.0f;
	light1_direction = directioMorning;
	light1_position = light1_positionMorning;
	light1_ambient = ambientMorning;
	light1_diffuse = light1_specular = morningLight;
}
void SetMiddayLight()
{
	glClearColor(LightGoldenrodYellow[0], LightGoldenrodYellow[1], LightGoldenrodYellow[2], LightGoldenrodYellow[3]);
	light1Spot_cutoff = 70;
	light1Spot_exponent = 2.0f;
	light1_direction = directioMidday;
	light1_position = light1_positionMidday;
	light1_ambient = ambientMidday;
	light1_diffuse = light1_specular = middayLight;
}
void SetEvningLight()
{
	glClearColor(OrangeRed[0], OrangeRed[1], OrangeRed[2], OrangeRed[3]);
	light1Spot_cutoff = 70;
	light1Spot_exponent = 2.0f;
	light1_direction = directioEvning;
	light1_position = light1_positionEvning;
	light1_ambient = ambientEavning;
	light1_diffuse = light1_specular = evningLight;
}

void TextureLoad()
{
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
void DrawGrass()
{
	glBindTexture(GL_TEXTURE_2D, textures[GRASS]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glEnable(GL_TEXTURE_2D);
	glColor3fv(White);
	glTranslatef(0, -1, -4);
	glPushMatrix();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 1);
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
void DrawRoad()
{
	glBindTexture(GL_TEXTURE_2D, textures[ROAD]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glEnable(GL_TEXTURE_2D);
	glColor3fv(White);
	glTranslatef(0, 0, 6);
	glPushMatrix();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 1);
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
void DrawHouse(bool isDrawnShadow = false)
{
	const GLfloat x = 1, y = -1, z = groundHeight / 2;

	glBindTexture(GL_TEXTURE_2D, textures[WALL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glPushMatrix();
	glTranslatef(0, 0, -5);
	isDrawnShadow ? glColor4fv(BlackShadow) : glColor3fv(Wheat);
	glEnable(GL_TEXTURE_2D);

	//right wall
	glBegin(GL_QUADS);

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
	glBindTexture(GL_TEXTURE_2D, textures[FRONT_WALL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glPushMatrix();
	glTranslatef(0, 0, -5.0f);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
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
	//roof
	isDrawnShadow ? glColor4fv(BlackShadow) : glColor3fv(Gray);
	glBegin(GL_QUADS);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glEnd();
	//back wall
	glColor3fv(Black);
	glBegin(GL_QUADS);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glEnd();
	glPopMatrix();
}
void DrawWheels(bool isDrawnShadow = false) {
	isDrawnShadow ? glColor4fv(BlackShadow) : glColor3fv(Wheat);
	glPushMatrix();

	glTranslatef(-0.5f, -0.86f, -0.7f);
	glutSolidSphere(0.25, 10, 10);

	glTranslatef(0, 0, 0.7f);
	glutSolidSphere(0.25, 10, 10);

	glTranslatef(1, 0, 0);
	glutSolidSphere(0.25, 10, 10);

	glTranslatef(0, 0, -0.7f);
	glutSolidSphere(0.25, 10, 10);

	glPopMatrix();
}
void DrawBody(bool isDrawnShadow = false) {
	float xr = 1.0f, xl = -1.0f, x2r = 0.4f, yu = 1.0f, yd = 0.1f, y2u = 1.4f, zf = 0.0f, zb = -0.75f;
	glPushMatrix();

	isDrawnShadow ? glColor4fv(BlackShadow) : glColor3fv(Yellow);
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
	isDrawnShadow ? glColor4fv(BlackShadow) : glColor3fv(Red);
	glVertex3f(xl, yu, zb);
	glVertex3f(xl, yd, zb);
	glVertex3f(xl, yd, zf);
	glVertex3f(xl, yu, zf);

	//car window
	isDrawnShadow ? glColor4fv(BlackShadow) : glColor3fv(Aqua);

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
	glPopMatrix();
}
void DrawCar(bool isDrawnShadow = false) {
	const GLfloat scale = 0.5;
	glPushMatrix();
	glTranslatef(2.0f, -0.45f, -2.0f);
	glTranslatef(positionX, positionY, positionZ);
	glRotatef(turnCar, 0, 1, 0);
	glScalef(scale, scale, scale);
	if (isDrawnShadow) {
		DrawBody(true);
		DrawWheels(true);
	}
	else {
		DrawBody();
		DrawWheels();
	}
	glPopMatrix();
}
void DrawStreetLights(bool isDrawnShadow = false) {
	GLfloat startPositionX = -8.3f, startPositionY = -7.5f;
	GLfloat sacale = 0.4f, dystanceZ = -7.5f;

	for (size_t i = 0; i < countOfLights; i++)
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);

		glScalef(sacale, sacale, sacale);
		glTranslatef(startPositionX + i * lightMultiplayer, -0.3f, dystanceZ);
		isDrawnShadow ? glColor4fv(BlackShadow) : glColor4fv(LightGoldenrodYellow2);
		//light bulb
		glTranslatef(0.3f, -0.5f, -0.5f);
		glutSolidSphere(0.15, 20, 20);

		glPopMatrix();
		glPushMatrix();
		glScalef(sacale, sacale, sacale);
		glTranslatef(startPositionX + 0.3f + i * lightMultiplayer, -1.7f, dystanceZ - 0.5f);
		//light pillar
		glScaled(0.2, 3, 0.15);
		isDrawnShadow ? glColor4fv(BlackShadow) : glColor3fv(DarkGray);
		glutSolidCube(0.5);

		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}
void SetFog()
{
	glHint(GL_FOG_HINT, fog_hint);
	glFogf(GL_FOG_MODE, fog_mode);
	glFogfv(GL_FOG_COLOR, Gray);
	glFogf(GL_FOG_START, fog_start);
	glFogf(GL_FOG_END, fog_end);
	glFogf(GL_FOG_DENSITY, fog_density);
}
void SelectShadowMatrices()
{
	if (light1Status == L1OFF && light0Status == L0ON)
	{
		glMultMatrixf(ShadowMatrixForLight0);
	}
	else if (light1Status == L1ON && light0Status == L0OFF)
	{
		glMultMatrixf(ShadowMatrixForLight1);
	}
	else if (light1Status == L1ON && light0Status == L0ON)
	{
		glMultMatrixf(ShadowMatrixForLight1AndLight2);
	}
	else {
		glClearColor(Black[0], Black[1], Black[2], Black[3]);
		glMultMatrixf(ShadowMatrixEmpty);
	}
}
void DrawShadows() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glPushMatrix();

	SelectShadowMatrices();

	DrawHouse(true);
	DrawCar(true);
	DrawStreetLights(true);

	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
void DrawScene() {
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawGrass();
	DrawRoad();

	DrawShadows();
	DrawHouse();
	DrawCar();
	DrawStreetLights();

	SetLight0();
	SetLight1();

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
}

void ProjectionFrustrum(int width, int height)
{
	if (aspect == ASPECT_1_1)
	{
		if (width < height && width > 0) {
			glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1.0, wievDistance);
		}
		else if (width >= height && height > 0) {
			glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1.0, wievDistance);
		}
	}
	else {
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, wievDistance);
	}
}
void ProjectionPerspective(int width, int height)
{
	GLdouble aspect = 1;
	if (height > 0) {
		aspect = width / (GLdouble)height;
	}
	gluPerspective(FOV, aspect, 1.0, wievDistance);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glpApplyCameraTransform(&frameCamera);

	glTranslatef(translatex, translatey, 0.0);
	glScalef(scale, scale, scale);

	DrawScene();

	glFlush();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	// render full window
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (frustum == activeProjection)
	{
		ProjectionFrustrum(width, height);
		glTranslatef(0, 0, -3);
	}
	else if (perspective == activeProjection)
	{
		ProjectionPerspective(width, height);
		glTranslatef(0, 0, -3);
	}
	Display();
}
void Menu(int value)
{
	if (value == EXIT) {
		glDeleteTextures(amountOfTextures, textures);
		exit(0);
	}
}
void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		button_state = state;
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

void ResetCarRadiuse(bool leftTurn = true)
{
	if (turnCar >= 360 || turnCar <= -360 && leftTurn)
	{
		turnCar = 0;
	}
	else if (turnCar == 0 && !leftTurn)
	{
		turnCar = 360;
	}
}
void SwapHorisontToZ()
{
	directionHorizontal = &positionZ;
	directionVertical = &positionX;
}
void SwapHorisontToX()
{
	directionHorizontal = &positionX;
	directionVertical = &positionZ;
}
void SelectAngle(GLint angle)
{
	switch (angle)
	{
	case 0:
	{
		SwapHorisontToX();
		isTheCarFrontFacingLeft = true;
		break;
	}
	case 90:
	{
		SwapHorisontToZ();
		isTheCarFrontFacingLeft = false;
		break;
	}
	case 180:
	{
		SwapHorisontToX();
		isTheCarFrontFacingLeft = false;
		break;
	}
	case 270:
	{
		SwapHorisontToZ();
		isTheCarFrontFacingLeft = true;
		break;
	}
	default:
		break;
	}
}
void TurnLeft()
{
	turnCar += turnAngle;
	ResetCarRadiuse();
	SelectAngle(turnCar);
	rightTurnWasUsed = false;
}
void TurnRight()
{
	ResetCarRadiuse(false);
	turnCar -= turnAngle;
	SelectAngle(turnCar);
	rightTurnWasUsed = true;
}
void MoveForward(const GLfloat speed)
{
	if (isTheCarFrontFacingLeft)
		* directionHorizontal -= speed;
	else
		*directionHorizontal += speed;

	switch (turnCar)
	{
	case 45:
	{
		if (rightTurnWasUsed)
		{
			*directionVertical -= speed;
		}
		else
		{
			*directionHorizontal -= speed;
			*directionVertical += speed;
		}
		break;
	}
	case 135:
	{
		*directionHorizontal += speed;
		*directionVertical += speed;
		break;
	}
	case 225:
	{
		if (rightTurnWasUsed)
		{
			*directionVertical += speed;
		}
		else
		{
			*directionHorizontal += speed;
			*directionVertical -= speed;
		}
		break;
	}
	case 315:
	{
		*directionHorizontal -= speed;
		*directionVertical -= speed;
		break;
	}
	default:

		break;
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '-': {
		if (activeProjection == perspective && FOV < 180)
		{
			FOV++;
		}
		else if (scale > 0.1f)
		{
			scale -= 0.1f;
		}
		break;
	}
	case '+': {
		if (activeProjection == perspective && FOV > 0)
		{
			FOV--;
		}
		else
		{
			scale += 0.1f;
		}
		break;
	}
	case '1': {
		if (light0Status == L0OFF)
		{
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
		if (light1Status == L1OFF)
		{
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
	case 'w': { MoveForward(carSpeed);	  break; }
	case 's': { MoveForward(-carSpeed);   break; }
	case 'a': { TurnLeft();				  break; }
	case 'd': { TurnRight();			  break; }
	case 'm': {	SetMorningLight();		  break; }
	case 'n': {	SetMiddayLight();		  break; }
	case 'b': {	SetEvningLight();		  break; }
	case ',': { light1Spot_cutoff += 5;   break; }
	case '.': {	light1Spot_cutoff -= 5;   break; }
	case 'k': { light1Spot_exponent += 5; break; }
	case 'l': {	light1Spot_exponent -= 5; break; }
	default:
		break;
	}
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
void ScaleMenu(int sc)
{
	switch (sc)
	{
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		break;
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		break;
	default:
		break;
	}
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
void ProjectionMenu(int p)
{
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

void FogMenu(int s)
{
	if (s == ON)
	{
		glEnable(GL_FOG);
		SetFog();
	}
	else
	{
		glDisable(GL_FOG);
	}
	Display();
}
void MainMenu()
{
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

	//-----------------FOG----------------------------
	int fogState = glutCreateMenu(FogMenu);
#ifdef WIN32
	glutAddMenuEntry("Wl mgle", ON);
	glutAddMenuEntry("Wyl mgle", OFF);
#else
	glutAddMenuEntry("Wl mgle", ON);
	glutAddMenuEntry("Wyl mgle", OFF);
#endif

	//--------------MAIN_MENU-------------------------
	glutCreateMenu(Menu);
	glutAddSubMenu("Skala obrazu", menuAspect);
	glutAddSubMenu("Rzutowanie obrazu", menuactiveProjection);
	glutAddSubMenu("Mgla", fogState);
#ifdef WIN32
	glutAddMenuEntry("Wyjscie", EXIT);
#else
	glutAddMenuEntry("Wyjscie", EXIT);
#endif
}
void ShowControls(bool isShown = true)
{
	if (isShown)
	{
		std::cout << Info;
		return;
	}
	FreeConsole();
}
int main(int argc, char* argv[])
{
	ShowControls();

	glutInit(&argc, argv);
	glClearColor(Black[0], Black[1], Black[2], Black[3]);
	glutInitWindowSize(windowWidht, windowHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}