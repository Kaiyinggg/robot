#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

//projection
bool isOrtho = true;
float ty = 0, tx = 0, tz = 0, tSpeed = 1;
float ONear = -3, OFar = 3;
float ptx = 0, pty = 0, ptSpeed = 0.1;
float prx = 0, pry = 0, prSpeed = 1;
float zoom = -7;
float rotateX = 0;
float rotateY = 0;
int textureChange = 1;
bool changing = false;

//Shoot and Fly
float radius = 2.0f;
int stacks = 20;
int slices = 20;
int boneLength;
float xPosition = 0.0f, yPosition = 0.0f, zPosition = 0.05f;
bool shootKeyPressed = false;
float maxSize = 0.2f; // Adjust as needed
float ballSizeIncrement = 0.001f; // Adjust as needed
bool eKeyDown = false;
float bodyAngle = 0;
float movingDirection = 0.0f;
bool fly = false;
float xLimitLeft = -0.3;
float xLimitRight = 0.3;
float yLimitTop = 0.5;
float yLimitDown = -0.3;
float wingAngle = 0;

//Cannon toggles
bool cKeyDown = false, vKeyDown = false;
bool cannonOn = false, shootCannon = false;
bool cannonToggle = false;
float cannonRotateAngle = 0.0f;
float cannonAngle = 0.0f;

//Cannon animation
float ballXPosition = 0.0f, ballYPosition = 0.0f, ballZPosition = 0.15f;
float ballRotateAngle = 0.0f, ballSize = 0.0f;
bool shootToggle = false;
void drawShooting(GLUquadricObj* var);
void flying();

//head movement
bool nod = false;
float headAngle = 0.0;

//hand movement
float handAngle = 0.0;
float hy1 = 0.0, hz1 = 0.0;
float armAngle = 10;
float ay1 = 0.0, az1 = -0.043, az2 = -0.043;
float upperFingerAngle1 = -30;
float lowerFingerAngle1 = 10;
float upperFingerAngle2 = 20;
float upperFingerAngle3 = -20;
int r = 1, g = 1, b = 1;

//leg movement
float legAngle = 0.0;
float ly1 = 0.0, lz1 = 0.0;
float lowerLegAngle1 = 0.0;
float lly1 = 0.0, llz1 = 0.0;

//walking
bool walk = false;
bool leftHandForward = true, rightHandForward = false;
float leftHandAngle = 0.0, rightHandAngle = 0.0;
float lhy = 0, lhz = 0;
float rhy = 0, rhz = 0;
bool leftLegForward = false, rightLegForward = true;
float leftLegAngle = 0.0, rightLegAngle = 0.0;
float lly = 0, llz = 0;
float rly = 0, rlz = 0;

//weapon
bool isWeaponOn = true;
bool rotationOn = false;
int rotateAngle = 0;
int rotateArm = 0;
bool clockwiseRotation = true;
float POSArm = 0;
float armMoveInFront = 0;

bool isWeaponOn2 = false;
bool forwardAnimation = false;

//Lighting
bool isLightOn = false;
float lSpeed = 1;
float ambL[3] = { 1.0, 0.0, 0.0 };
float posA[3] = { 0,0,0 };
float difL[3] = { 1.0,1.0,0.0 };
float posD[3] = { 0,5,0 };

BITMAP BMP;				//bitmap structure
HBITMAP hBMP = NULL;	//bitmap handle 
int textureSelect = 2;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);

		else if (wParam == VK_UP)           //move robot up
		{
			if (isOrtho)
			{
				if (ty < 3)
				{
					ty += tSpeed;
				}
			}
			else
			{
				if (ty < 8)
				{
					ty += tSpeed;
				}
			}
		}
		else if (wParam == VK_DOWN)         //move robot down
		{
			if (isOrtho)
			{
				if (ty > -3)
				{
					ty -= tSpeed;
				}
			}
			else
			{
				if (ty > -8)
				{
					ty -= tSpeed;
				}
			}
		}
		else if (wParam == VK_LEFT)         //move robot left
		{
			if (isOrtho)
			{
				if (tx < 3)
				{
					tx += tSpeed;
				}
			}
			else
			{
				if (tx < 8)
				{
					tx += tSpeed;
				}
			}
		}
		else if (wParam == VK_RIGHT)        //move robot right
		{
			if (isOrtho)
			{
				if (tx > -3)
				{
					tx -= tSpeed;
				}
			}
			else
			{
				if (tx > -8)
				{
					tx -= tSpeed;
				}
			}
		}
		else if (wParam == 'O')
		{
			isOrtho = true;
			tx = 0, ty = 0, ptx = 0, pty = 0, prx = 0, pry = 0;
		}
		else if (wParam == 'P')
		{
			isOrtho = false;
			tx = 0, ty = 0, ptx = 0, pty = 0, prx = 0, pry = 0;
			zoom = -7;
		}
		else if (wParam == 'A')              //move projection left
		{
			if (isOrtho)
			{
				if (ptx > -0.35)
				{
					ptx -= ptSpeed;
				}
			}
			else
			{
				if (ptx > -0.8)
				{
					ptx -= ptSpeed;
				}
			}

		}
		else if (wParam == 'D')              //move projection right
		{
			if (isOrtho)
			{
				if (ptx < 0.35)
				{
					ptx += ptSpeed;
				}
			}
			else
			{
				if (ptx < 0.8)
				{
					ptx += ptSpeed;
				}
			}
		}
		else if (wParam == 'W')              //move projection up
		{
			if (isOrtho)
			{
				if (pty < 0.35)
				{
					pty += ptSpeed;
				}
			}
			else
			{
				if (pty < 0.8)
				{
					pty += ptSpeed;
				}
			}
		}
		else if (wParam == 'S')              //move projection down
		{
			if (isOrtho)
			{
				if (pty > -0.35)
				{
					pty -= ptSpeed;
				}
			}
			else {
				if (pty > -0.8)
				{
					pty -= ptSpeed;
				}
			}
		}
		else if (wParam == 0xBE)              //rotate up for projection
		{
			prx += prSpeed;
		}
		else if (wParam == 0xBF)              //rotate down for projection
		{
			prx -= prSpeed;
		}
		else if (wParam == 'F')              //rotate left for projection
		{
			pry += prSpeed;
		}
		else if (wParam == 'H')              //rotate right for projection
		{
			pry -= prSpeed;
		}
		else if (wParam == 'T')              //move robot nearer to view
		{
			if (!isOrtho)
			{
				if (zoom < -2.5)
				{
					zoom += 0.5;
				}
			}
		}
		else if (wParam == 'G')              //move robot farther to view
		{
			if (!isOrtho)
			{
				if (zoom > -14)
				{
					zoom -= 0.5;
				}
			}
		}

		else if (wParam == 'Z') {
			rotateY -= 1.5;
		}
		else if (wParam == 'X') {
			rotateY += 1.5;
		}
		else if (wParam == 0xBD) { // "-"
			rotateX += 1.5;
		}
		else if (wParam == 0xBB) { // "="
			rotateX -= 1.5;
		}

		else if (wParam == 'I') {
			if (handAngle < 40) {
				handAngle += 1;
				if (handAngle >= 0)
				{
					hy1 += 0.0077;
					hz1 -= 0.0077;
				}
				else {
					hy1 -= 0.001;
					hz1 -= 0.01;
				}
			}
		}
		else if (wParam == 'K') {
			if (handAngle > -23)
			{
				handAngle -= 1;
				if (handAngle >= 0)
				{
					hy1 -= 0.0077;
					hz1 += 0.0077;
				}
				else {
					hy1 += 0.001;
					hz1 += 0.01;
				}
			}
		}

		else if (wParam == 'J') {
			if (armAngle < 80) {
				armAngle += 1;
				ay1 += 0.0045;
				az1 -= 0.0005;
				az2 += 0.0005;
			}
		}
		else if (wParam == 'L') {
			if (armAngle > 0) {
				armAngle -= 1;
				ay1 -= 0.0045;
				az1 += 0.0005;
				az2 -= 0.0005;
			}
		}

		else if (wParam == 'C') {
			upperFingerAngle1 = -70;
			lowerFingerAngle1 = -40;
			upperFingerAngle2 = 75;
			upperFingerAngle3 = -90;
		}
		else if (wParam == 'V') {
			upperFingerAngle1 = -30;
			lowerFingerAngle1 = 10;
			upperFingerAngle2 = 20;
			upperFingerAngle3 = -20;
		}

		else if (wParam == 'B') {
			if (legAngle < 50)
			{
				legAngle += 1;
				if (legAngle > 0)
				{
					ly1 += 0.0009;
					lz1 += 0.005;
				}
				else {
					ly1 += 0.005;
					lz1 += 0.004;
				}
			}
		}
		else if (wParam == 'N') {
			if (legAngle > -50)
			{
				legAngle -= 1;
				if (legAngle > 0)
				{
					ly1 -= 0.0009;
					lz1 -= 0.005;
				}
				else {
					ly1 -= 0.005;
					lz1 -= 0.004;
				}
			}
		}

		else if (wParam == 'Q') {
			if (lowerLegAngle1 > -50)
			{
				lowerLegAngle1 -= 1;
				if (lowerLegAngle1 > -10)
				{
					lly1 -= 0.005;
					llz1 -= 0.02;
				}
				else if (lowerLegAngle1 > -20) {
					lly1 -= 0.005;
					llz1 -= 0.025;
				}
				else if (lowerLegAngle1 > -30) {
					lly1 -= 0.009;
					llz1 -= 0.015;
				}
				else if (lowerLegAngle1 > -40) {
					lly1 -= 0.013;
					llz1 -= 0.013;
				}
				else {
					lly1 -= 0.015;
					llz1 -= 0.001;
				}
			}
		}
		else if (wParam == 'E') {
			if (lowerLegAngle1 < 0)
			{
				lowerLegAngle1 += 1;
				if (lowerLegAngle1 > -10)
				{
					lly1 += 0.005;
					llz1 += 0.02;
				}
				else if (lowerLegAngle1 > -20) {
					lly1 += 0.005;
					llz1 += 0.025;
				}
				else if (lowerLegAngle1 > -30) {
					lly1 += 0.009;
					llz1 += 0.015;
				}
				else if (lowerLegAngle1 > -40) {
					lly1 += 0.013;
					llz1 += 0.013;
				}
				else {
					lly1 += 0.015;
					llz1 += 0.001;
				}
			}
		}

		else if (wParam == 0x31) {
			walk = true;
			if (walk)
			{
				if (leftHandForward) {
					leftHandAngle += 1;

					if (leftHandAngle >= 0)
					{
						lhy += 0.0077;
						lhz -= 0.0077;
					}
					else {
						lhy -= 0.001;
						lhz -= 0.01;
					}

					if (leftHandAngle >= 20) {
						leftHandForward = false;
					}
				}
				else {
					leftHandAngle -= 1;
					if (leftHandAngle >= 0)
					{
						lhy -= 0.0077;
						lhz += 0.0077;
					}
					else {
						lhy += 0.001;
						lhz += 0.01;
					}

					if (leftHandAngle <= -20) {
						leftHandForward = true;
					}
				}

				if (rightHandForward)
				{
					rightHandAngle += 1;
					if (rightHandAngle >= 0)
					{
						rhy += 0.0077;
						rhz -= 0.0077;
					}
					else {
						rhy -= 0.001;
						rhz -= 0.01;
					}

					if (rightHandAngle >= 20)
					{
						rightHandForward = false;
					}
				}
				else
				{
					rightHandAngle -= 1;
					if (rightHandAngle >= 0)
					{
						rhy -= 0.0077;
						rhz += 0.0077;
					}
					else {
						rhy += 0.001;
						rhz += 0.01;
					}

					if (rightHandAngle <= -20)
					{
						rightHandForward = true;
					}
				}

				if (leftLegForward) {
					leftLegAngle += 1;

					if (leftLegAngle > 0)
					{
						lly += 0.0009;
						llz += 0.005;
					}
					else {
						lly += 0.005;
						llz += 0.004;
					}

					if (leftLegAngle >= 20) {
						leftLegForward = false;
					}
				}
				else {
					leftLegAngle -= 1;
					if (leftLegAngle > 0)
					{
						lly -= 0.0009;
						llz -= 0.005;
					}
					else {
						lly -= 0.005;
						llz -= 0.004;
					}

					if (leftLegAngle <= -20) {
						leftLegForward = true;
					}
				}

				if (rightLegForward) {
					rightLegAngle += 1;

					if (rightLegAngle > 0)
					{
						rly += 0.0009;
						rlz += 0.005;
					}
					else {
						rly += 0.005;
						rlz += 0.004;
					}

					if (rightLegAngle >= 20) {
						rightLegForward = false;
					}
				}
				else {
					rightLegAngle -= 1;
					if (rightLegAngle > 0)
					{
						rly -= 0.0009;
						rlz -= 0.005;
					}
					else {
						rly -= 0.005;
						rlz -= 0.004;
					}

					if (rightLegAngle <= -20) {
						rightLegForward = true;
					}
				}
			}

			if (zoom < -3)
			{
				zoom += 0.005;
			}
			else {
				walk = false;
			}
		}
		else if (wParam == 0x32) {
			textureSelect = 2;
		}
		else if (wParam == 0x33) {
			textureSelect = 1;
		}
		else if (wParam == 0x34) {
			nod = true;
		}
		else if (wParam == 0x35) {
			isLightOn = !isLightOn;
		}
		else if (wParam == 0x36) {
			if (rotateY >= 360) {
				rotateAngle -= 360;
			}
			rotationOn = !rotationOn;
		}
		else if (wParam == 0x37) {
			fly = true;
			flying();
		}

		else if (wParam == 0x38) {
			cannonOn = !cannonOn;
		}
		else if (wParam == 0x39) {
			if (!vKeyDown) {
				vKeyDown = true;
				ballSizeIncrement = 0.1f;
			}
			else {
				if (ballSize < maxSize) {
					ballSize += ballSizeIncrement;
				}
				else {
					shootToggle = true;
					ballRotateAngle = -cannonRotateAngle * 2.0f;
				}
			}

		}
		else if (wParam == 0x30) {

			if (clockwiseRotation) {
				rotateArm += 5;

				if (rotateArm >= 30) {
					clockwiseRotation = false;
				}
			}
			else {
				rotateArm -= 5;
				if (rotateArm <= -30) {
					clockwiseRotation = true;
				}
			}

			if (rotateArm > 30) {
				rotateArm = 30;
			}
			else if (rotateArm < -30) {
				rotateArm = -30;
			}

			POSArm = -0.14f * (rotateArm / 15.0f);
		}
		else if (wParam == 'U') {
			walk = false;
		}

		else if (wParam == 'M') {
			changing = true;
			if (textureChange < 6) {
				textureChange += 1;
			}
			else {
				textureChange = 1;
			}
		}

		else if (wParam == 'Y') {
			isWeaponOn = !isWeaponOn;
			/*
			if (isWeaponOn2) {
				isWeaponOn = !isWeaponOn;
			}*/
			break;
		}
		else if (wParam == 'R') {
			if (isWeaponOn) {
				isWeaponOn2 = !isWeaponOn2;
			}
			isWeaponOn2 = !isWeaponOn2;
		}

		else if (wParam == VK_F1) {
			if (isLightOn) {
				posA[0] += lSpeed;
			}
		}
		else if (wParam == VK_F2) {
			if (isLightOn) {
				posA[0] -= lSpeed;
			}
		}
		else if (wParam == VK_F3) {
			if (isLightOn) {
				posA[1] -= lSpeed;
			}
		}
		else if (wParam == VK_F4) {
			if (isLightOn) {
				posA[1] += lSpeed;
			}
		}
		else if (wParam == VK_F5) {
			if (isLightOn) {
				posA[2] += lSpeed;
			}
		}
		else if (wParam == VK_F6) {
			if (isLightOn) {
				posA[2] -= lSpeed;
			}
		}
		else if (wParam == VK_F7) {
			if (isLightOn) {
				posD[0] += lSpeed;
			}
		}
		else if (wParam == VK_F8) {
			if (isLightOn) {
				posD[0] -= lSpeed;
			}
		}
		else if (wParam == VK_F9) {
			if (isLightOn) {
				posD[1] -= lSpeed;
			}
		}
		else if (wParam == 0xDB) {    // "{"
			if (isLightOn) {
				posD[1] += lSpeed;
			}
		}
		else if (wParam == 0xDD) {   // "}"
			if (isLightOn) {
				posD[2] += lSpeed;
			}
		}
		else if (wParam == 0xDC) {  // "\"
			if (isLightOn) {
				posD[2] -= lSpeed;
			}
		}

		else if (wParam == VK_SPACE)
		{
			isOrtho = true;
			ty = 0, tx = 0, tz = 0, tSpeed = 1;
			ONear = -3, OFar = 3;
			ptx = 0, pty = 0, ptSpeed = 0.1;
			prx = 0, pry = 0, prSpeed = 1;
			zoom = -7;
			rotateX = 0;
			rotateY = 0;

			radius = 2.0f;
			stacks = 20;
			slices = 20;
			xPosition = 0.0f, yPosition = 0.0f, zPosition = 0.05f;
			shootKeyPressed = false;
			maxSize = 0.2f;
			ballSizeIncrement = 0.001f;
			eKeyDown = false;
			bodyAngle = 0;
			movingDirection = 0.0f;
			fly = false;
			xLimitLeft = -0.3;
			xLimitRight = 0.3;
			yLimitTop = 0.5;
			yLimitDown = -0.3;
			wingAngle = 0;

			cKeyDown = false, vKeyDown = false;
			cannonOn = false, shootCannon = false;
			cannonToggle = false;
			cannonRotateAngle = 0.0f;
			cannonAngle = 0.0f;

			ballXPosition = 0.0f, ballYPosition = 0.0f, ballZPosition = 0.15f;
			ballRotateAngle = 0.0f, ballSize = 0.0f;
			shootToggle = false;

			nod = false;
			headAngle = 0.0;

			handAngle = 0.0;
			hy1 = 0.0, hz1 = 0.0;
			armAngle = 10;
			ay1 = 0.0, az1 = -0.043, az2 = -0.043;
			upperFingerAngle1 = -30;
			lowerFingerAngle1 = 10;
			upperFingerAngle2 = 20;
			upperFingerAngle3 = -20;

			legAngle = 0.0;
			ly1 = 0.0, lz1 = 0.0;
			lowerLegAngle1 = 0.0;
			lly1 = 0.0, llz1 = 0.0;

			walk = false;
			leftHandForward = true, rightHandForward = false;
			leftHandAngle = 0.0, rightHandAngle = 0.0;
			lhy = 0, lhz = 0;
			rhy = 0, rhz = 0;
			leftLegForward = false, rightLegForward = true;
			leftLegAngle = 0.0, rightLegAngle = 0.0;
			lly = 0, llz = 0;
			rly = 0, rlz = 0;
			isWeaponOn = true;
			isWeaponOn2 = false;

			isLightOn = false;
			lSpeed = 1;
			ambL[0] = 1;
			ambL[1] = 0;
			ambL[2] = 0;

			posA[0] = 0;
			posA[1] = 0;
			posA[2] = 0;

			difL[0] = 1;
			difL[1] = 1;
			difL[2] = 0;

			posD[0] = 0;
			posD[1] = 5;
			posD[2] = 0;

			textureSelect = 2;
			changing = false;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawCube(float size) {
	glBegin(GL_QUADS);

	// Face 1 : BOTTOM
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);

	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, size);

	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);

	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 : LEFT
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);

	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);

	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);

	// Face 3 : FRONT
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);

	glTexCoord2f(1, 0);
	glVertex3f(size, size, size);

	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, size);

	// Face 4 : RIGHT
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);

	glTexCoord2f(1, 1);
	glVertex3f(size, size, size);

	glTexCoord2f(1, 0);
	glVertex3f(size, size, 0.0f);

	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, 0.0f);

	// Face 5 : BACK
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, 0.0f);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, 0.0f);

	glTexCoord2f(0, 0);
	glVertex3f(size, size, 0.0f);

	// Face 6 : TOP
	glTexCoord2f(0, 1);
	glVertex3f(size, size, 0.0f);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);

	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);

	glTexCoord2f(0, 0);
	glVertex3f(size, size, size);
	glEnd();
}

void drawCubeLine(float size) {
	glBegin(GL_LINE_LOOP);
	// Face 1 : BOTTOM
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);

	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0f, size);

	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0f, 0.0f);

	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Face 2 : LEFT
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);

	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);

	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, size);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Face 3 : FRONT
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, size);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, size);

	glTexCoord2f(1, 0);
	glVertex3f(size, size, size);

	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, size);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Face 4 : RIGHT
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, size);

	glTexCoord2f(1, 1);
	glVertex3f(size, size, size);

	glTexCoord2f(1, 0);
	glVertex3f(size, size, 0.0f);

	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Face 5 : BACK
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0f, 0.0f);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, 0.0f);

	glTexCoord2f(0, 0);
	glVertex3f(size, size, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Face 6 : TOP
	glTexCoord2f(0, 1);
	glVertex3f(size, size, 0.0f);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, size, 0.0f);

	glTexCoord2f(1, 0);
	glVertex3f(0.0f, size, size);

	glTexCoord2f(0, 0);
	glVertex3f(size, size, size);
	glEnd();
}

void drawTriangle(float size) {
	float halfSize = size / 2.0f;

	//glColor3f(1, 1, 1); // White color
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5, 0);
	glVertex3f(0, -halfSize, 0);
	glVertex3f(0, halfSize, 0);
	glVertex3f(0, 0, halfSize);
	glEnd();

	//glColor3f(1, 1, 0); // Yellow color
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -halfSize, 0);
	glVertex3f(0, halfSize, 0);
	glVertex3f(-halfSize, halfSize, 0);
	glVertex3f(-halfSize, -halfSize, 0);
	glEnd();

	//glColor3f(1, 0, 1); // Magenta color
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0);
	glVertex3f(-halfSize, -halfSize, 0);
	glVertex3f(-halfSize, halfSize, 0);
	glVertex3f(-halfSize, 0, halfSize);
	glEnd();

	//glColor3f(0, 1, 1); // Cyan color
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, -halfSize, 0);
	glVertex3f(0, 0, halfSize);
	glVertex3f(-halfSize, 0, halfSize);
	glVertex3f(-halfSize, -halfSize, 0);
	glEnd();

	//glColor3f(0, 0, 1); // Blue color
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, halfSize);
	glVertex3f(-halfSize, 0, halfSize);
	glVertex3f(-halfSize, halfSize, 0);
	glVertex3f(0, halfSize, 0);
	glEnd();
}

void drawTriangleLine(float size) {
	float halfSize = size / 2.0f;

	//glColor3f(1, 1, 1); // White color
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -halfSize, 0);
	glVertex3f(0, halfSize, 0);
	glVertex3f(0, 0, halfSize);
	glEnd();

	//glColor3f(1, 1, 1); // Yellow color
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -halfSize, 0);
	glVertex3f(0, halfSize, 0);
	glVertex3f(-halfSize, halfSize, 0);
	glVertex3f(-halfSize, -halfSize, 0);
	glEnd();

	//glColor3f(1, 1, 1); // Magenta color
	glBegin(GL_LINE_LOOP);
	glVertex3f(-halfSize, -halfSize, 0);
	glVertex3f(-halfSize, halfSize, 0);
	glVertex3f(-halfSize, 0, halfSize);
	glEnd();

	//glColor3f(1, 1, 1); // Cyan color
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -halfSize, 0);
	glVertex3f(0, 0, halfSize);
	glVertex3f(-halfSize, 0, halfSize);
	glVertex3f(-halfSize, -halfSize, 0);
	glEnd();

	//glColor3f(1, 1, 1); // Blue color
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, halfSize);
	glVertex3f(-halfSize, 0, halfSize);
	glVertex3f(-halfSize, halfSize, 0);
	glVertex3f(0, halfSize, 0);
	glEnd();
}

void drawSphere(double radius) {
	GLUquadricObj* sphere = NULL;             // create quadric obj pointer
	sphere = gluNewQuadric();			      // create quadric obj in the memory
	gluQuadricDrawStyle(sphere, GLU_FILL);    // set draw style to use line
	gluSphere(sphere, radius, 30, 30);	      // draw sphere
	gluDeleteQuadric(sphere);
}

void drawSphereLine(double radius) {
	GLUquadricObj* sphere = NULL;             // create quadric obj pointer
	sphere = gluNewQuadric();			      // create quadric obj in the memory
	gluQuadricDrawStyle(sphere, GLU_LINE);    // set draw style to use line
	gluSphere(sphere, radius, 15, 15);	      // draw sphere
	gluDeleteQuadric(sphere);
}

void drawPyramid() {
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, -0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, -0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, 0.1, 0.0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, -0.1, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, 0.1, 0.0);
	glEnd();
}

void drawPyramidLine() {
	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, -0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glEnd();

	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, -0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glEnd();

	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, 0.1, 0.0);
	glEnd();

	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glEnd();

	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, -0.1, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, 0.1, 0.0);
	glEnd();
}

void drawSemiSphere(GLfloat radius) {
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	int sliceNo = 30, stackNo = 30;

	for (sliceA = 0; sliceA <= (PI); sliceA += (PI) / sliceNo)
	{
		glBegin(GL_TRIANGLE_FAN);
		for (stackA = 0; stackA <= (PI); stackA += (PI) / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glTexCoord2f(stackA / PI, sliceA / (PI / 2)); // Texture coordinates
			glVertex3f(x, y, z);

			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glTexCoord2f(stackA / PI, (sliceA + PI / sliceNo) / (PI / 2)); // Texture coordinates
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void drawSemiSphereLine(GLfloat radius) {
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	int sliceNo = 15, stackNo = 15;

	for (sliceA = 0; sliceA <= (PI); sliceA += (PI) / sliceNo)
	{
		glBegin(GL_LINE_LOOP);
		for (stackA = 0; stackA <= (PI); stackA += (PI) / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glTexCoord2f(stackA / PI, sliceA / (PI / 2)); // Texture coordinates
			glVertex3f(x, y, z);

			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glTexCoord2f(stackA / PI, (sliceA + PI / sliceNo) / (PI / 2)); // Texture coordinates
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void drawCylinder(double br, double tr, double h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, br, tr, h, 30, 30);
	gluDeleteQuadric(cylinder);
}

void drawCylinderLine(double br, double tr, double h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, br, tr, h, 15, 15);
	gluDeleteQuadric(cylinder);
}

void drawCone(double tr, double h) {
	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluQuadricTexture(cone, true);
	gluCylinder(cone, 0, tr, h, 30, 30);
	gluDeleteQuadric(cone);
}

void drawConeLine(double tr, double h) {
	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_LINE);
	gluQuadricTexture(cone, true);
	gluCylinder(cone, 0, tr, h, 15, 15);
	gluDeleteQuadric(cone);
}

void drawDisk(double inr, double outr) {
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_FILL);
	gluQuadricTexture(disk, true);
	gluDisk(disk, inr, outr, 20, 20);
	gluDeleteQuadric(disk);
}

void drawDiskLine(double inr, double outr) {
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_LINE);
	gluQuadricTexture(disk, true);
	gluDisk(disk, inr, outr, 8, 1);
	gluDeleteQuadric(disk);
}

void drawPrismaTriangular() {
	glBegin(GL_QUADS);
	// Face 1 : FRONT
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.2, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.2, 0.1, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.3, 0.0, 0.1);

	// Face 2 : BOTTOM
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.3, 0.0, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.1);

	// Face 3 : BACK
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);

	// Face 4 : TOP
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.2, 0.1, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.2, 0.1, 0.1);

	// Face 5 : LEFT
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.2, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.3, 0.0, 0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);
	glEnd();

	// Face 6 : RIGHT
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.2, 0.1, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawPrismaTriangularLine() {
	glBegin(GL_LINE_LOOP);
	// Face 1 : FRONT
	//glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.2, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.2, 0.1, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.3, 0.0, 0.1);
	glEnd();

	// Face 2 : BOTTOM
	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.3, 0.0, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.1);
	glEnd();

	// Face 3 : BACK
	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);
	glEnd();

	// Face 4 : TOP
	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.2, 0.1, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.2, 0.1, 0.1);
	glEnd();

	// Face 5 : LEFT
	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.2, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.3, 0.0, 0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);
	glEnd();

	// Face 6 : RIGHT
	//glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.2, 0.1, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void cylinderC(float br, float tr, float h, float csl, float cst) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, br, tr, h, csl, cst);
}

void cylinderFrame(float br, float tr, float h, int segments) {
	const float PI = 3.141592f;
	glBegin(GL_LINES);
	// Draw the top circle
	for (int i = 0; i < segments; ++i) {
		float theta1 = 2.0f * PI * (float)i / (float)segments;
		float theta2 = 2.0f * PI * (float)(i + 1) / (float)segments;
		glVertex3f(tr * sin(theta1), tr * cos(theta1), 0.0f);
		glVertex3f(tr * sin(theta2), tr * cos(theta2), 0.0f);
		glVertex3f(tr * sin(theta1), tr * cos(theta1), 0.0f); // Top vertex
		glVertex3f(br * sin(theta1), br * cos(theta1), h); // Bottom vertex
	}
	// Draw the bottom circle
	for (int i = 0; i < segments; ++i) {
		float theta1 = 2.0f * PI * (float)i / (float)segments;
		float theta2 = 2.0f * PI * (float)(i + 1) / (float)segments;
		glVertex3f(br * sin(theta1), br * cos(theta1), h); // Bottom vertex
		glVertex3f(br * sin(theta2), br * cos(theta2), h); // Next bottom vertex
	}
	glEnd();
}

void sphereC(float rad, int sl, int st) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);


	gluQuadricTexture(sphere, true);

	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
}


void drawRectangleOutline() {
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);    // Vertex a
	glVertex3f(0.0, 0.0, -0.1);   // Vertex b
	glVertex3f(0.12, 0.0, -0.1);  // Vertex c
	glVertex3f(0.12, 0.0, 0.0);   // Vertex d
	glEnd();
}

GLuint loadTexture(LPCSTR filename) {

	//Take from step 1
	GLuint texture = 0;		//texture name

	//STEP 3: Initialise texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4: Assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//take from step 5
	DeleteObject(hBMP);

	return texture;

}

void rectangleC() {
	glBegin(GL_QUADS);
	// Face 1  abdc

	//face 2  bdhf
	glColor3f(1.0, 1.0, 1.0); //magenta  purple
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.12, 0.0, 0.0); //b
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.12, 0.0, -0.14); //d
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.12, 0.15, -0.14); //h
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.12, 0.15, 0.0); //f

	//face 3  fhge
	glColor3f(1.0, 1.0, 1.0); //cyan  green
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.12, 0.15, 0.0); //f
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.12, 0.15, -0.14); //h
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0, 0.15, -0.14); //g
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.15, 0.0); //e

	//face 4 efba top
	glColor3f(1.0, 1.0, 1.0); //white
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.15, 0.0); //e
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.12, 0.15, 0.0); //f
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.12, 0.0, 0.0); //b
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0); //a

	//face 5 aegc
	glColor3f(1.0, 1.0, 1.0); //yellow
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0); //a
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.15, 0.0); //e
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0, 0.15, -0.14); //g
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, -0.14); //c

	//face 6 cdhg
	glColor3f(1.0, 1.0, 1.0);  //blue
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, -0.14); //c
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.12, 0.0, -0.14); //d
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.12, 0.15, -0.14); //h
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0, 0.15, -0.14); //g

	glColor3f(1.0, 1.0, 1.0); //red
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0); //a
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.12, 0.0, 0.0); //b
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.12, 0.0, -0.14); //d
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, -0.14); //c
	glEnd();


}

void wingLine() {
	wingAngle += 0.1;
	//wing 2

	glPushMatrix();
	glTranslatef(0.135, 0.17, 0.45);  // Tz 0.55 true
	glRotatef(90, 0.0, 1.0, 0.0);

	if (fly) {
		glRotatef(sin(wingAngle * 3.14 / 180) * 20, 1.0, 0.0, 0.0); // Apply sinusoidal rotation for flapping
	}
	//glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	//drawCylinderCLine(0.015, 0.015, 0.1, 50, 50);
	//cylinderC(0.015, 0.015, 0.1, 50, 50);
	glColor3f(0, 0, 0);
	cylinderFrame(0.015, 0.015, 0.1, 2);
	glColor3f(1, 1, 1);
	drawCylinder(0.015, 0.015, 0.1);
	glPopMatrix();



	//ball a
	glPushMatrix();
	glTranslatef(0.135, 0.17, 0.45);   //Tz 0.55 
	//glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	glRotatef(sin(wingAngle * 3.14 / 180) * 20, 1.0, 0.0, 0.0); // Apply the same rotation as the wing
	sphereC(0.015, 50, 50);
	glPopMatrix();
}

void wingC() {
	//wing 1
	glPushMatrix();
	glTranslatef(0.01, -0.02, 0.0);
	glScalef(0.8, 1.0, 1.0);
	wingLine();
	glPopMatrix();

	//wing 2
	wingLine();

	//wing 3
	glPushMatrix();
	glTranslatef(-0.03, 0.02, 0.0);
	glScalef(1.3, 1.0, 1.0);
	wingLine();
	glPopMatrix();

	//wing 4
	glPushMatrix();
	glTranslatef(-0.04, 0.04, 0.0);
	glScalef(1.5, 1.0, 1.0);
	wingLine();
	glPopMatrix();

	//wing 5
	glPushMatrix();
	glTranslatef(-0.04, 0.06, 0.0);
	glScalef(1.7, 1.0, 1.0);
	wingLine();
	glPopMatrix();
}

void wingAB() {
	//wingA
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.5);
	glScalef(0.1, 0.6, 0.1);

	glColor3f(1, 1, 1);//light golden rod yellow	#FAFAD2	(250,250,210)
	rectangleC();
	glPopMatrix();

	//wing B
	glPushMatrix();
	glTranslatef(0.1, 0.15, 0.5);
	glScalef(0.3, 0.4, 0.1);
	glColor3f(1, 1, 1);//light golden rod yellow	#FAFAD2	(250,250,210)
	rectangleC();
	glPopMatrix();
}

void wingC1() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	wingC();
	glPopMatrix();
}

void leftWing() {
	wingAB();
	wingC1();
}

void rightWing() {
	glPushMatrix();
	glTranslatef(-0.003, 0.0, 0.99);
	glRotatef(180, 0.0, 1.0, 0.0); //rotate 
	wingAB();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.02);   //Tz 1.0 will be change afterward
	glRotatef(180, 0.0, 1.0, 0.0); //rotate 
	wingC1();
	glPopMatrix();
}

void wholeWing() {
	glPushMatrix();
	glTranslatef(-0.05, 0.1, 0.0);   //Tz 1.0 will be change afterward
	leftWing();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.04, 0.1, 0.0);   //Tz 1.0 will be change afterward
	rightWing();
	glPopMatrix();
}

void drawUpperFinger() {
	// Face 1 : FRONT
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glEnd();

	// Face 2 : TOP
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.2f);
	glEnd();

	// Face 3 : BACK
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glEnd();

	// Face 4 : LEFT
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	// Face 5 : BOTTOM
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();

	// Face 6 : RIGHT
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
}

void drawUpperFingerLine() {
	// Face 1 : FRONT
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glEnd();

	// Face 2 : TOP
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.2f);
	glEnd();

	// Face 3 : BACK
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glEnd();

	// Face 4 : LEFT
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	// Face 5 : BOTTOM
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();

	// Face 6 : RIGHT
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
}

void drawLowerFinger() {
	// Face 1 : FRONT
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glEnd();

	// Face 2 : TOP
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glEnd();

	// Face 3 : BACK
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	// Face 4 : LEFT
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	// Face 5 : BOTTOM
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	// Face 6 : RIGHT
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glEnd();
}

void drawLowerFingerLine() {
	// Face 1 : FRONT
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glEnd();

	// Face 2 : TOP
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glEnd();

	// Face 3 : BACK
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	// Face 4 : LEFT
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	// Face 5 : BOTTOM
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	// Face 6 : RIGHT
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glEnd();
}

void drawFace() {
	glLineWidth(2);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, 0.1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, 0.1, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0, 0);
	glTexCoord2f(0.5f, 0.8f);
	glVertex3f(0.1, -0.1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1, -0.1, 0);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.2, 0, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, 0.1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, 0.1, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0, 0);
	glTexCoord2f(0.5f, 0.8f);
	glVertex3f(0.1, -0.1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1, -0.1, 0);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.2, 0, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.1, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.1, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glRotatef(180, 1, 0, 0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.1, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.1, 0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, -0.01);
	glScalef(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.1, 0);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(0.1, 0, 0);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0, -0.1, 0);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.1, 0, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.1, 0);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(0.1, 0, 0);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0, -0.1, 0);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.1, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.07, 0, -0.02);
	glRotatef(35, 0, 0, 1);
	glScalef(0.8, 0.8, 0.8);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.07, -0.06, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.03, -0.06, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.07, 0, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.07, -0.06, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.03, -0.06, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.07, 0, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-0.05, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.1, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-0.05, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.1, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.07, -0.06, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.03, -0.06, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.03, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.07, 0, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.1, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1, 0.1, 0);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-0.05, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.1, 0);
	glEnd();

	glPopMatrix();
}

void drawHead() {
	glPushMatrix();
	glTranslatef(-0.2, 0.9, 0.03);
	glScaled(2, 1.5, 1.8);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.2, 0.03);
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScaled(3.5, 2, 2);
	glColor3f(0, 0, 0);
	drawTriangleLine(0.2);
	glColor3f(1, 1, 1);
	drawTriangle(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 0.92, 0.04);
	glScalef(0.2, 1.3, 1.6);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.2, 0.92, 0.03);
	glScalef(0.2, 1.3, 1.6);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 1.2, 0.2);
	glRotatef(-40, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.04, 0.04, 0.3);
	glColor3f(1, 1, 1);
	drawCylinder(0.04, 0.04, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.4, 1.2, 0.2);
	glRotatef(-40, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.04, 0.04, 0.3);
	glColor3f(1, 1, 1);
	drawCylinder(0.04, 0.04, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.03, 1.2, 0.025);
	glScalef(0.3, 1.35, 1.8);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 1, 1);
	glTranslatef(1.05, 0.45, -0.55);
	glRotatef(30, 1, 0, 0);
	glRotatef(45, 0, 0, 1);

	glPushMatrix();
	glTranslatef(-0.03, 1.5, 0.025);
	glScalef(0.3, 1.5, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.8, 0.025);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.3, 0.2, 2);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 1, 1);
	glTranslatef(-1.05, 0.45, -0.55);
	glRotatef(30, 1, 0, 0);
	glRotatef(-45, 0, 0, 1);

	glPushMatrix();
	glTranslatef(-0.03, 1.5, 0.025);
	glScalef(0.3, 1.5, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.8, 0.025);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.3, 0.2, 2);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.13, 1.3, 0.1);
	glScalef(0.4, 0.4, 0.4);
	glColor3f(0, 0, 0);
	drawSphereLine(0.1);
	glColor3f(1, 1, 1);
	drawSphere(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.13, 1.3, 0.3);
	glScalef(0.4, 0.4, 0.4);
	glColor3f(0, 0, 0);
	drawSphereLine(0.1);
	glColor3f(1, 1, 1);
	drawSphere(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, 1.13, 0.05);
	glRotatef(90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.7, 1, 1);
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawTriangleLine(0.1);
	glColor3f(1, 1, 1);
	drawTriangle(0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 1.13, 0.05);
	glRotatef(90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.7, 1, 1);
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawTriangleLine(0.1);
	glColor3f(1, 1, 1);
	drawTriangle(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.95, 0.025);
	glScalef(1.1, 0.8, 1);
	drawFace();
	glPopMatrix();
}

void drawBodyAndHandConnector() {
	glPushMatrix();
	glTranslatef(0.4, 0.7, 0);
	glScalef(1.5, 0.6, 1.8);
	//glColor3f(0, 0, 0);
	//drawCubeLine(0.2);
	//glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 0.50, 0);
	glScalef(0.6, 1.5, 1.8);
	//glColor3f(0, 0, 0);
	//drawCubeLine(0.2);
	//glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.40, 0.63, 0);
	glRotatef(-45, 0, 0, 1);
	glScalef(0.8, 1.25, 1.8);
	//glColor3f(0, 0, 0);
	//drawCubeLine(0.2);
	//glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.55, 1.05, 0.2);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawConeLine(0.1, 0.25);
	glColor3f(1, 1, 1);
	drawCone(0.1, 0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.55, 0.9, 0.2);
	glRotatef(50, 0, 1, 0);
	glRotatef(70, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawDiskLine(0.06, 0.15);
	glColor3f(1, 1, 1);
	drawDisk(0.06, 0.15);
	glPopMatrix();
}

void drawBody() {
	glLineWidth(2);

	glPushMatrix();
	glTranslatef(0, 0.6, 0);
	glScalef(2, 1.2, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 0.6, 0);
	glScalef(2, 1.2, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.16, 0.36, 0);
	glScalef(1.2, 1.2, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 0.36, 0);
	glScalef(1.2, 1.2, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.71, 0.01);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.6, 0.6, 0.6);
	glColor3f(0, 0, 0);
	drawSemiSphereLine(0.2);
	glColor3f(1, 1, 1);
	drawSemiSphere(0.2);
	glPopMatrix();

	if (cannonOn) {
		glPushMatrix();
		GLUquadricObj* var = gluNewQuadric();
		if (!var) {
			// Handle error if gluNewQuadric() fails
			return;
		}
		gluQuadricNormals(var, GLU_SMOOTH);
		gluQuadricTexture(var, GL_TRUE);
		glTranslatef(0, 0.2, -0.15);
		glScalef(0.7, 0.7, 0.7);
		glRotatef(cannonAngle, 0, 0, 1);

		cannonAngle += 0.5f;  // Increment rotation angle

		if (cannonAngle > 360) {
			cannonAngle -= 360;
		}

		drawShooting(var);
		gluDeleteQuadric(var);

		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0.2, 0.29, 0.05);
	glScalef(0.9, 0.9, 1.7);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.38, 0.29, 0.05);
	glScalef(0.9, 0.9, 1.7);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.19, -0.02, 0.02);
	glScalef(1, 1.6, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.39, -0.02, 0.02);
	glScalef(1, 1.6, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0.02);
	glColor3f(0, 0, 0);
	drawDiskLine(0.1, 0.2);
	glColor3f(1, 1, 1);
	drawDisk(0.1, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0.42);
	glColor3f(0, 0, 0);
	drawDiskLine(0.1, 0.2);
	glColor3f(1, 1, 1);
	drawDisk(0.1, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0.02);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.15, 0.15, 0.4);
	glColor3f(1, 1, 1);
	drawCylinder(0.15, 0.15, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0.2);
	glColor3f(0, 0, 0);
	drawSphereLine(0.07);
	glColor3f(1, 1, 1);
	drawSphere(0.07);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.35, 0.2);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawConeLine(0.13, 0.25);
	glColor3f(1, 1, 1);
	drawCone(0.13, 0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1, -0.07, 0);
	glScalef(1, 0.5, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(10, 0, 0, 1);
	glTranslatef(-0.06, -0.3, 0);
	glScalef(2.4, 1.2, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-10, 0, 0, 1);
	glTranslatef(-0.41, -0.3, 0);
	glScalef(2.4, 1.2, 2);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.07, 0.38);
	glScalef(3, 3.5, 0.4);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);

	glPushMatrix();
	glTranslatef(-0.2, -0.05, -0.55);
	glRotatef(10, 0, 0, 1);
	glScalef(2.5, 3, 0.4);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.11, -0.02, -0.65);
	glRotatef(20, 0, 0, 1);
	glScalef(2.0, 2.5, 0.4);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.03, 0.02, -0.75);
	glRotatef(30, 0, 0, 1);
	glScalef(1.5, 2.0, 0.4);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	//glPushMatrix();
	//glTranslatef(-0.03, -1, 3);
	//glScalef(5.5, 7.0, 7.0);
	//glRotatef(180, 0.0, 1.0, 0.0);
	//wholeWing();
	//glPopMatrix();

	if (textureSelect == 1)
	{
		r = 1;
		g = 1;
		b = 1;
	}
	else {
		g = 0;
		b = 0;
	}

	glLineWidth(1);
	glPushMatrix();
	glTranslatef(0.03, 0.18, -0.76);
	glScalef(0.15, 1, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(r, g, b);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.08, 0.18, -0.76);
	glScalef(0.15, 1, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(r, g, b);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.09, 0.25, -0.76);
	glRotatef(75, 0, 0, 1);
	glScalef(0.15, 1.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(r, g, b);
	drawCube(0.2);
	glPopMatrix();

	glPopMatrix();

	//body line
	glPushMatrix();
	glTranslatef(-0.34, 0.65, -0.015);
	glScalef(0.8, 0.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.37, 0.75, -0.015);
	glScalef(0.5, 0.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.17, 0.65, -0.015);
	glScalef(0.8, 0.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.27, 0.75, -0.015);
	glScalef(0.5, 0.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.4, -0.015);
	glRotatef(45, 0, 0, 1);
	glScalef(0.6, 0.6, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.4, -0.015);
	glRotatef(45, 0, 0, 1);
	glScalef(0.6, 0.6, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0.15, -0.001);
	glRotatef(90, 0, 0, 1);
	glScalef(4, 10, 5);

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, 0.01, 0.0);
	glVertex3f(-0.02, 0.0, 0.0);
	glVertex3f(-0.01, 0.01, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.0, 0.0);
	glVertex3f(-0.01, 0.01, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.01, 0.01, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.01, 0.01, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.01, 0.01, 0.0);
	glVertex3f(0.02, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.01, 0.01, 0.0);
	glVertex3f(0.02, 0.0, 0.0);
	glVertex3f(0.03, 0.01, 0.0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.01, 0.0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-0.02, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.01, 0.01, 0.0);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.01, 0.01, 0.0);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(0.02, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.01, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, 0.15, -0.001);
	glRotatef(-90, 0, 0, 1);
	glScalef(4, 10, 5);

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, 0.01, 0.0);
	glVertex3f(-0.02, 0.0, 0.0);
	glVertex3f(-0.01, 0.01, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.02, 0.0, 0.0);
	glVertex3f(-0.01, 0.01, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.01, 0.01, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.01, 0.01, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.01, 0.01, 0.0);
	glVertex3f(0.02, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.01, 0.01, 0.0);
	glVertex3f(0.02, 0.0, 0.0);
	glVertex3f(0.03, 0.01, 0.0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.03, 0.01, 0.0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-0.02, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.01, 0.01, 0.0);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.01, 0.01, 0.0);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(0.02, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.03, 0.01, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.2, -0.00001);
	glScalef(10, 10, 1);
	glColor3f(0, 0, 0);
	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.03, 0.01, 0.0);
	glVertex3f(-0.02, 0.0, 0.0);
	glVertex3f(-0.01, 0.01, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.01, 0.01, 0.0);
	glVertex3f(0.02, 0.0, 0.0);
	glVertex3f(0.03, 0.01, 0.0);
	glEnd();
	glPopMatrix();

	glLineWidth(2);
	//connect with head
	glPushMatrix();
	glTranslatef(0, 1.1, 0.2);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.15, 0.15, 0.4);
	glColor3f(1, 1, 1);
	drawCylinder(0.15, 0.15, 0.4);
	glPopMatrix();

	//connect with left leg
	glPushMatrix();
	glTranslatef(0.25, -0.25, 0.2);
	glColor3f(0, 0, 0);
	drawSphereLine(0.15);
	glColor3f(1, 1, 1);
	drawSphere(0.15);
	glPopMatrix();

	//connect with right leg
	glPushMatrix();
	glTranslatef(-0.25, -0.25, 0.2);
	glColor3f(0, 0, 0);
	drawSphereLine(0.15);
	glColor3f(1, 1, 1);
	drawSphere(0.15);
	glPopMatrix();

	//connect with left hand
	drawBodyAndHandConnector();

	//connect with right hand
	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	glRotatef(180, 0, 1, 0);
	drawBodyAndHandConnector();
	glPopMatrix();
}

void drawUpperArm() {
	glPushMatrix();
	glTranslatef(0.53, 0.6, 0.2);
	glRotatef(10, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1.3, 1.9);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.1, 0.1, 0.3);
	glColor3f(1, 1, 1);
	drawCylinder(0.1, 0.1, 0.3);
	glPopMatrix();
}

void drawLowerArm() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.85, -0.35, 0.38);
	glRotatef(100, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glScalef(2.7, 3, 2.7);
	glColor3f(0, 0, 0);
	drawPrismaTriangularLine();
	glColor3f(1, 1, 1);
	drawPrismaTriangular();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -0.45, 0.16);
	glRotatef(10, 0, 0, 1);
	glScalef(0.3, 1.5, 1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	//Finger 1
	glPushMatrix();
	glTranslatef(0.63, -0.36, 0.17);
	glScalef(0.12, 0.13, 0.15);
	glRotatef(10, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle2, 0, 1, 0);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();

	//Finger 2
	glPushMatrix();
	glTranslatef(0.63, -0.4, 0.2);
	glScalef(0.12, 0.12, 0.15);
	glRotatef(lowerFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();

	//Finger 3
	glPushMatrix();
	glTranslatef(0.63, -0.4, 0.25);
	glScalef(0.12, 0.10, 0.15);
	glRotatef(lowerFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();

	//Finger 4
	glPushMatrix();
	glTranslatef(0.63, -0.4, 0.3);
	glScalef(0.12, 0.08, 0.15);
	glRotatef(lowerFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();
}

void drawLeftHandCone() {
	glPushMatrix();
	glTranslatef(0.93, 0.24, 0.28);
	glRotatef(10, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glColor3f(0, 0, 0);
	drawConeLine(0.09, 0.20);
	glColor3f(1, 1, 1);
	drawCone(0.09, 0.20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.96, 0.09, 0.17);
	glRotatef(10, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glColor3f(0, 0, 0);
	drawConeLine(0.09, 0.20);
	glColor3f(1, 1, 1);
	drawCone(0.08, 0.20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.99, -0.08, 0.25);
	glRotatef(10, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glColor3f(0, 0, 0);
	drawConeLine(0.09, 0.20);
	glColor3f(1, 1, 1);
	drawCone(0.09, 0.20);
	glPopMatrix();
}

void drawRectangular(GLfloat width, GLfloat height) {
	// Calculate half dimensions for convenience
	GLfloat halfWidth = width / 2.0f;
	GLfloat halfHeight = height / 2.0f;

	glBegin(GL_POLYGON);

	// Define vertices of the rectangle
	glVertex2f(-halfWidth, -halfHeight); // Bottom-left corner
	glVertex2f(halfWidth, -halfHeight);  // Bottom-right corner
	glVertex2f(halfWidth, halfHeight);   // Top-right corner
	glVertex2f(-halfWidth, halfHeight);  // Top-left corner

	glEnd();
}

void drawRectangularLine(GLfloat width, GLfloat height) {
	// Calculate half dimensions for convenience
	GLfloat halfWidth = width / 2.0f;
	GLfloat halfHeight = height / 2.0f;

	glBegin(GL_LINE_LOOP);

	// Define vertices of the rectangle
	glVertex2f(-halfWidth, -halfHeight); // Bottom-left corner
	glVertex2f(halfWidth, -halfHeight);  // Bottom-right corner
	glVertex2f(halfWidth, halfHeight);   // Top-right corner
	glVertex2f(-halfWidth, halfHeight);  // Top-left corner

	glEnd();
}

void drawWeapon() {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 1, 1.5);
	glPushMatrix();
	glColor3f(1, 1, 1.0);
	glTranslatef(0.68, -0.35, -0.4);
	glScalef(0.5, 0.5, 0.5);

	glColor3f(0, 0, 0);
	drawCylinderLine(0.1, 0.1, 1.2);
	glColor3f(1, 1, 1);
	drawCylinder(0.1, 0.1, 1.2);

	glColor3f(0, 0, 0);
	drawCylinderLine(0.15, 0.1, 0.5);
	glColor3f(1, 1.0, 1.0);
	drawCylinder(0.15, 0.1, 0.5);

	glColor3f(0, 0, 0);
	drawCylinderLine(0.4, 0.1, 0.3);
	glColor3f(1, 1, 1.0);
	drawCylinder(0.4, 0.1, 0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1.0);
	glTranslatef(0.68, -0.25, -0.1);
	glRotatef(90, 20, 0, 1);
	glScalef(0.5, 0.5, 0.5);

	glColor3f(0, 0, 0);
	drawCylinderLine(0.1, 0.1, 0.45);
	glColor3f(1, 1, 1.0);
	drawCylinder(0.1, 0.1, 0.45);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.68, -0.35, -0.5);
	glRotatef(90, 0, 0, 1);

	glColor3f(0, 0, 0);
	drawCylinderLine(0.1, 0.1, 0.45);
	glColor3f(1, 1, 1.0);
	drawCylinder(0.10, 0.20, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.68, -0.34, -0.50);
	glScalef(1, 1, 1);
	glColor3f(0, 0, 0);
	drawSphereLine(0.12);
	glColor3f(1, 1, 1);
	drawSphere(0.12);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.65, -0.25, -0.15);
	glScalef(0.5, 0.5, 0.5);

	glColor3f(0, 0, 0);
	drawCubeLine(0.18);
	glColor3f(1, 1, 1);
	drawCube(0.18);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.65, -0.15, -0.15);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	drawCubeLine(0.18);
	glColor3f(1, 1.0, 1);
	drawCube(0.18);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.65, -0.15, -0.23);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	drawCubeLine(0.18);
	glColor3f(1, 1.0, 1);
	drawCube(0.18);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.68, -0.55, -0.15);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	drawCubeLine(0.18);
	glColor3f(1, 1.0, 1);
	drawCube(0.18);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.68, -0.63, -0.15);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	drawCubeLine(0.18);
	glColor3f(1, 1, 1.0);
	drawCube(0.18);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.68, -0.63, -0.23);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	drawCubeLine(0.18);
	glColor3f(1, 1, 1);
	drawCube(0.18);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.70, -0.33, -1);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	drawConeLine(0.4, 0.8);
	glColor3f(1, 1, 1);
	drawCone(0.4, 0.8);
	glPopMatrix();

	glPopMatrix();

}

void drawWeapon2() {

	//cylinder
	glPushMatrix();
	glTranslatef(-0.02, 0, -0.68);
	glScalef(1, 1, 1.6);
	glPushMatrix();

	glTranslatef(0.68, -0.35, 0.05);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.15, 0.15, 1.2);
	glColor3f(1, 1, 1.0);
	drawCylinder(0.15, 0.15, 1.2);
	glPopMatrix();

	//handle connector
	glPushMatrix();
	glTranslatef(0.7, -0.35, 0.25);
	glScalef(0.5, 0.5, 1.8);
	glColor3f(0, 0, 0);
	drawDiskLine(0.05, 0.25);
	glColor3f(1, 1, 1.0);
	drawDisk(0.05, 0.25);
	glPopMatrix();

	//first cross
	glPushMatrix();
	glTranslatef(0.7, -0.35, 0.4);
	glRotatef(60, 0, 0, 1);
	glScalef(0.5, 0.5, 1.8);
	glColor3f(0, 0, 0);
	drawRectangularLine(0.5, 0.65);
	glColor3f(1, 1, 1.0);
	drawRectangular(0.5, 0.65);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -0.35, 0.4);
	glRotatef(-65, 0, 0, 1);
	glScalef(0.5, 0.5, 1.8);
	glColor3f(0, 0, 0);
	drawRectangularLine(0.5, 0.65);
	glColor3f(1, 1, 1.0);
	drawRectangular(0.5, 0.65);
	glPopMatrix();

	//second cross
	glPushMatrix();
	glTranslatef(0.7, -0.35, 0.35);
	glRotatef(60, 0, 0, 1);
	glScalef(0.5, 0.5, 1.8);
	glColor3f(0, 0, 0);
	drawRectangularLine(0.5, 0.65);
	glColor3f(1, 1, 1.0);
	drawRectangular(0.5, 0.65);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -0.35, 0.35);
	glRotatef(-65, 0, 0, 1);
	glScalef(0.5, 0.5, 1.8);
	glColor3f(0, 0, 0);
	drawRectangularLine(0.5, 0.65);
	glColor3f(1, 1, 1.0);
	drawRectangular(0.5, 0.65);
	glPopMatrix();

	//third cross
	glPushMatrix();
	glTranslatef(0.7, -0.35, 0.3);
	glRotatef(60, 0, 0, 1);
	glScalef(0.5, 0.5, 1.8);
	glColor3f(0, 0, 0);
	drawRectangularLine(0.5, 0.65);
	glColor3f(1, 1, 1.0);
	drawRectangular(0.5, 0.65);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -0.35, 0.3);
	glRotatef(-65, 0, 0, 1);
	glScalef(0.5, 0.5, 1.8);
	glColor3f(0, 0, 0);
	drawRectangularLine(0.5, 0.65);
	glColor3f(1, 1, 1.0);
	drawRectangular(0.5, 0.65);
	glPopMatrix();

	//sphere
	glPushMatrix();
	glTranslatef(0.68, -0.34, 0); // Translate to the center position for rotation
	if (rotationOn) {
		rotateAngle += 3;
	}
	glRotatef(rotateAngle, 0, 0, 1); // Rotate the sphere and cones around the center
	glTranslatef(-0.68, 0.34, 0);

	glPushMatrix();
	glTranslatef(0.68, -0.34, 0);
	glRotatef(rotateAngle, 0, 0, 1);
	glScalef(1, 1, 0.8);
	glColor3f(0, 0, 0);
	drawSphereLine(0.3);
	glColor3f(1, 1, 1);
	drawSphere(0.3);
	glPopMatrix();

	//front cone
	glPushMatrix();
	glTranslatef(0.70, -0.33, -0.2);
	glRotatef(180, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1.0, 1);
	drawPyramid();
	glPopMatrix();

	//top right cone
	glPushMatrix();
	glTranslatef(0.6, -0.1, 0.0);
	glRotatef(30, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	//glTranslatef(0.70, -0.33, -0.2);
	glRotatef(180, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1.0, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();


	//top left cone
	glPushMatrix();
	glTranslatef(0.825, -0.125, 0.0);
	glRotatef(330, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	//glTranslatef(0.70, -0.33, -0.2);
	glRotatef(180, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1.0, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();


	//bottom left cone
	glPushMatrix();
	glTranslatef(0.85, -0.525, 0.0);
	glRotatef(-130, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	//glTranslatef(0.70, -0.33, -0.2);
	glRotatef(180, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1.0, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();


	//left cone
	glPushMatrix();
	glTranslatef(0.93, -0.32, 0.0);
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();
	//glTranslatef(0.70, -0.33, -0.2);
	glRotatef(180, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1.0, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();


	//right cone
	glPushMatrix();
	glTranslatef(0.43, -0.3, 0.0);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	//glTranslatef(0.70, -0.33, -0.2);
	glRotatef(180, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1.0, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();


	//bottom right cone
	glPushMatrix();
	glTranslatef(0.55, -0.55, 0.0);
	glRotatef(-30, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glPushMatrix();
	//glTranslatef(0.70, -0.33, -0.2);
	glRotatef(180, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1.0, 1);
	drawPyramid();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();


}

void drawRightHandBox() {
	glPushMatrix();
	glTranslatef(-0.95, -0.15, 0.1);
	glRotatef(-10, 0, 0, 1);
	glScalef(0.7, 2, 1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.88, 0.15, 0.13);
	glRotatef(-10, 0, 0, 1);
	glScalef(0.5, 1, 0.7);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();
}

void drawLeftHand() {
	glPushMatrix();
	glRotatef(rotateArm, 1, 0, 0);
	glTranslatef(0, 0, POSArm);
	drawUpperArm();
	glPushMatrix();
	glTranslatef(0, ay1, az1);
	glRotatef(armAngle, 1, 0, 0);
	drawLowerArm();
	drawLeftHandCone();

	if (isWeaponOn) {

		if (forwardAnimation) {
			glTranslatef(0, 0, -0.2);
		}
		drawWeapon();

	}
	if (isWeaponOn2) {
		drawWeapon2();
	}


	if (forwardAnimation) {
		glTranslatef(0, 0, -0.2);
	}
	glPopMatrix();
	glPopMatrix();

}

void drawRightHand() {
	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	glRotatef(180, 0, 1, 0);
	drawUpperArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, ay1, az2);
	glRotatef(armAngle, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	glRotatef(180, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0.59, -0.45, 0.01);
	glRotatef(100, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glScalef(2.7, 3, 2.7);
	glColor3f(0, 0, 0);
	drawPrismaTriangularLine();
	glColor3f(1, 1, 1);
	drawPrismaTriangular();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -0.5, 0.04);
	glRotatef(10, 0, 0, 1);
	glScalef(0.3, 1.5, 1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	//Finger 1
	glPushMatrix();
	glTranslatef(0.63, -0.41, 0.20);
	glScalef(0.12, 0.13, 0.15);
	glRotatef(10, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle3, 0, 1, 0);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();

	//Finger 2
	glPushMatrix();
	glTranslatef(0.63, -0.45, 0.07);
	glScalef(0.12, 0.12, 0.15);
	glRotatef(lowerFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();

	//Finger 3
	glPushMatrix();
	glTranslatef(0.63, -0.45, 0.12);
	glScalef(0.12, 0.10, 0.15);
	glRotatef(lowerFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();

	//Finger 4
	glPushMatrix();
	glTranslatef(0.63, -0.45, 0.17);
	glScalef(0.12, 0.08, 0.15);
	glRotatef(lowerFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawLowerFingerLine();
	glColor3f(1, 1, 1);
	drawLowerFinger();
	glPushMatrix();
	glRotatef(upperFingerAngle1, 0, 0, 1);
	glColor3f(0, 0, 0);
	drawUpperFingerLine();
	glColor3f(1, 1, 1);
	drawUpperFinger();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	drawRightHandBox();
	glPopMatrix();
}

void drawUpperLeg() {
	glPushMatrix();
	glTranslatef(0.26, -0.33, 0.2);
	glRotatef(5, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.08, 0.13, 0.35);
	glColor3f(1, 1, 1);
	drawCylinder(0.08, 0.13, 0.35);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.29, -0.67, 0.2);
	glRotatef(5, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.13, 0.08, 0.45);
	glColor3f(1, 1, 1);
	drawCylinder(0.13, 0.08, 0.45);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.35, -0.7, 0.2);
	glRotatef(-90, 1, 0, 0);
	glScalef(1.5, 1, 2.7);
	glColor3f(0, 0, 0);
	drawPyramidLine();
	glColor3f(1, 1, 1);
	drawPyramid();
	glPopMatrix();
}

void drawLowerLeg() {
	glPushMatrix();
	glTranslatef(0.35, -1.2, 0.2);
	glRotatef(5, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	drawCylinderLine(0.1, 0.1, 0.6);
	glColor3f(1, 1, 1);
	drawCylinder(0.1, 0.1, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.27, -1.79, 0.05);
	glScalef(1.3, 0.7, 1.5);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1, 1);
	glTranslatef(0.24, -1.83, 0.5);
	glRotatef(90, 0, 1, 0);
	glScalef(2, 1.3, 3.2);
	glColor3f(0, 0, 0);
	drawPrismaTriangularLine();
	glColor3f(1, 1, 1);
	drawPrismaTriangular();
	glPopMatrix();

	//glPushMatrix();
	//glColor3f(1.0f, 0.5f, 0.0f);
	//glTranslatef(0.38, -1, 0.2);
	//glRotatef(180, 1, 0, 0);
	//glRotatef(-90, 1, 0, 0);
	//glScalef(1.5, 1, 3);
	//drawPyramid();
	//glPopMatrix();
}

void drawLegLine() {
	glPushMatrix();
	glTranslatef(0.27, -1.1, 0.04);
	glRotatef(5, 0, 0, 1);
	glScalef(0.6, 0.7, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.42, -1.14, 0.04);
	glRotatef(5, 0, 0, 1);
	glScalef(0.1, 1.1, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.22, -1.15, 0.04);
	glRotatef(5, 0, 0, 1);
	glScalef(0.1, 1.1, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.27, -1.15, 0.04);
	glRotatef(5, 0, 0, 1);
	glScalef(0.6, 0.1, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, -1.25, 0.04);
	glRotatef(5, 0, 0, 1);
	glScalef(1, 0.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, -1.33, 0.04);
	glRotatef(5, 0, 0, 1);
	glScalef(1, 0.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, -1.41, 0.04);
	glRotatef(5, 0, 0, 1);
	glScalef(1, 0.2, 0.1);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();
}

void drawLeftLeg() {
	drawUpperLeg();

	glPushMatrix();
	glTranslatef(0, lly1, llz1);
	glRotatef(lowerLegAngle1, 1, 0, 0);

	drawLowerLeg();

	glPushMatrix();
	glTranslatef(0.24, -1.5, 0.05);
	glRotatef(90, 0, 1, 0);
	glRotatef(-5, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(2.0, 2.5, 2.6);
	glColor3f(0, 0, 0);
	drawPrismaTriangularLine();
	glColor3f(1, 1, 1);
	drawPrismaTriangular();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.45, -1.3, 0.07);
	glRotatef(5, 0, 0, 1);
	glScalef(0.5, 1, 0.9);
	glColor3f(0, 0, 0);
	drawCubeLine(0.2);
	glColor3f(1, 1, 1);
	drawCube(0.2);
	glPopMatrix();

	drawLegLine();
	glPopMatrix();
}

void drawRightLeg() {
	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	glRotatef(180, 0, 1, 0);
	drawUpperLeg();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, lly1, llz1);
	glRotatef(lowerLegAngle1, 1, 0, 0);

	glPushMatrix();
	glTranslatef(-0.5, -1.5, 0.05);
	glRotatef(90, 0, 1, 0);
	glRotatef(5, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(2.0, 2.5, 2.6);
	glColor3f(0, 0, 0);
	drawPrismaTriangularLine();
	glColor3f(1, 1, 1);
	drawPrismaTriangular();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.4);
	glRotatef(180, 0, 1, 0);
	drawLowerLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.47, 0, 0);
	glRotatef(-10, 0, 0, 1);
	drawLegLine();
	glPopMatrix();

	glPopMatrix();
}

void drawFingerArmor(GLUquadricObj* var) {
	glPushMatrix(); {
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

		glTranslatef(-0.15f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		gluCylinder(var, radius / 5.5f, radius / 5.5f, 0.50f, 4, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.5f);
			gluDisk(var, 0.0f, radius / 5.5f, 4, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.5f);
				gluDisk(var, 0.0f, radius / 5.5f, 4, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawBone(GLUquadricObj* var) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		gluCylinder(var, radius / 28, radius / 28, boneLength, 6, stacks);
	}
	glPopMatrix();

}

void drawHingeJoint(GLUquadricObj* var) {
	glPushMatrix();
	{
		gluSphere(var, radius / 25.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawHingeJointArmor(GLUquadricObj* var) {
	glPushMatrix();
	{
		glTranslatef(-0.17f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);

		gluCylinder(var, radius / 7.0f, radius / 7.0f, 0.30f, 8, stacks);
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.30f);
			gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.30f);
				gluDisk(var, 0.0f, radius / 7.0f, 8, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawFinger(GLUquadricObj* var, float fingerAngle1, float fingerAngle2) {
	glPushMatrix();
	{
		boneLength = 0.35f;
		drawBone(var);
		glPushMatrix();
		{
			glScalef(0.9f, 0.7f, 0.9f);
			drawFingerArmor(var);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -0.1f);
			glRotatef(fingerAngle1, 0.0f, 1.0f, 0.0f);
			radius = 0.5f;
			drawHingeJoint(var);
			glPushMatrix();
			{
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.8f, 1.7f, 1.7f);
				drawHingeJointArmor(var);
			}
			glPopMatrix();

			radius = 1.0f;
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				glTranslatef(0.0f, 0.0f, 0.0f);
				boneLength = 0.30f;
				drawBone(var);
				glPushMatrix();
				{
					glScalef(-1.0f, 1.0f, 1.0f);
					glScalef(0.8f, 0.6f, 0.8f);
					drawFingerArmor(var);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f);
					glRotatef(fingerAngle2, 0.0f, 1.0f, 0.0f);
					radius = 0.5f;
					drawHingeJoint(var);
					glPushMatrix();
					{
						glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
						glScalef(0.8f, 1.7f, 1.7f);
						drawHingeJointArmor(var);
					}
					glPopMatrix();
					radius = 1.0f;
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, -0.4f);
						glTranslatef(0.0f, 0.0f, 0.0f);
						boneLength = 0.30f;
						drawBone(var);
						glPushMatrix();
						{
							glScalef(0.7f, 0.5f, 0.7f);
							drawFingerArmor(var);
						}
						glPopMatrix();
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawShooting(GLUquadricObj* var) {

	glPushMatrix(); {
		glRotatef(180, 0, 1, 0);

		//draw cannon
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -0.25f);
			glColor3f(0, 0, 0);
			drawCylinderLine(radius / 4.8f, radius / 4.9f, 0.05f);
			gluCylinder(var, radius / 4.8f, radius / 4.9f, 0.05f, 12, stacks);
			glColor3f(1, 1, 1);
			glTranslatef(0.0f, 0.0f, 0.05f);
			gluCylinder(var, radius / 5.0f, radius / 8.0f, 0.25f, slices, stacks);
			gluDisk(var, 0.0f, radius / 5.0f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.25f);
				glColor3f(0, 0, 0);
				drawDiskLine(radius / 11.0f, radius / 8.0f);
				glColor3f(1, 1, 1);
				gluDisk(var, radius / 11.0f, radius / 8.0f, slices, stacks);
				glTranslatef(0.0f, 0.0f, 0.001f);
				gluDisk(var, radius / 9.5f, radius / 8.5f, slices, stacks);
			}
			glPopMatrix();
			glTranslatef(0.0f, 0.0f, 0.20f);
			glColor3f(0, 0, 0);
			drawCylinderLine(radius / 10.0f, radius / 10.0f, 0.10f);
			glColor3f(1, 1, 1);
			gluCylinder(var, radius / 10.0f, radius / 10.0f, 0.10f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.10f);
				glColor3f(0, 0, 0);
				drawDiskLine(radius / 11.5f, radius / 10.0f);
				glColor3f(1, 1, 1);
				gluDisk(var, radius / 11.5f, radius / 10.0f, slices, stacks);
			}
			glPopMatrix();
			glTranslatef(0.0f, 0.0f, 0.02f);
			glColor3f(0, 0, 0);
			drawCylinderLine(radius / 11.5f, radius / 11.5f, 0.10f);
			glColor3f(1, 1, 1);
			gluCylinder(var, radius / 11.5f, radius / 11.5f, 0.10f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.10f);
				glRotatef(-cannonRotateAngle, 0.0f, 0.0f, 1.0f);
				glColor3f(0, 0, 0);
				drawCylinderLine(radius / 16.0f, radius / 11.5f, 0.01f);
				glColor3f(1, 1, 1);
				gluCylinder(var, radius / 16.0f, radius / 11.5f, 0.01f, slices, stacks);
			}
			glPopMatrix();
			glTranslatef(0.0f, 0.0f, 0.02f);
			glColor3f(0, 0, 0);
			drawCylinderLine(radius / 16.0f, radius / 16.0f, 0.10f);
			glColor3f(1, 1, 1);
			gluCylinder(var, radius / 16.0f, radius / 16.0f, 0.10f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.10f);
				glColor3f(0, 0, 0);
				drawDiskLine(radius / 18.0f, radius / 16.0f);
				glColor3f(1, 1, 1);
				gluDisk(var, radius / 18.0f, radius / 16.0f, slices, stacks);
			}
			glPopMatrix();


			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.07f);
				glRotatef(cannonRotateAngle, 0.0f, 0.0f, 1.0f);
				glColor3f(0, 0, 0);
				drawCylinderLine(0.015f, radius / 18.0f, 0.01f);
				glColor3f(1, 1, 1);
				gluCylinder(var, 0.015f, radius / 18.0f, 0.01f, slices, stacks);
			}
			glPopMatrix();


		}
		glPopMatrix();

		//draw transformed fingers
		glPushMatrix();
		{
			if (vKeyDown) {
				ballRotateAngle = cannonRotateAngle * 2.0f;
				if (ballSize < 0.2f)
					ballSize += 0.0010f;
			}
			else {
				ballRotateAngle = -cannonRotateAngle;
			}

			glRotatef(ballRotateAngle, 0.0f, 0.0f, 1.0f);
			glPushMatrix();
			{
				glTranslatef(0.0f, -0.25f, 0.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.1f, -0.20f, 0.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.2f, 0.10f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.17f, 0.17f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.2f, 0.10f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.17f, 0.17f, 0.0f);
				glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.3f, 0.3f, -0.3f);
				drawFinger(var, 90.0f, 140.0f);
			}
			glPopMatrix();
		}
		glPopMatrix();


		//draw cannon ball 
		GLfloat light_position1[] = { (xPosition * 0.05f) + ballXPosition, ballYPosition, (-yPosition * 0.025f) + ballZPosition, 0.0 };

		glPushMatrix();
		{
			glTranslatef(light_position1[0], light_position1[1], light_position1[2]);
			glRotatef(-cannonRotateAngle * 5, 1.0f, 1.0f, 1.0f);
			glColor3f(1, 0, 0);
			gluSphere(var, ballSize, slices, stacks);
		}
		glPopMatrix();

	}
	glPopMatrix();

}

void projection() {
	glMatrixMode(GL_PROJECTION);			 //refer to the projection matrix
	glLoadIdentity();						 //reset the projection matrix
	glTranslatef(ptx, pty, 0);				 //translate x and y for projection
	glRotatef(pry, 0, 1, 0);				 //rotate y for projection	
	glRotatef(prx, 1, 0, 0);

	if (isOrtho)
	{
		glRotatef(180, 0, 1, 0);
		glOrtho(-3, 3, -3, 3, ONear, OFar);	//ortho 
	}
	else
	{
		gluPerspective(70, 1, 0.6, 21);
		glTranslatef(0, 0, zoom);
		glRotatef(180, 0, 1, 0);
	}
}

void lighting() {
	if (isLightOn) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambL);
	glLightfv(GL_LIGHT0, GL_POSITION, posA);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, difL);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glEnable(GL_LIGHT1);
}

void flying() {

	bodyAngle = -15.0f;
	legAngle = -15.0f;
	rotateY = 310;


	if (movingDirection == 0.0f) {
		if (xPosition <= xLimitLeft) {

			movingDirection = -1.0f; // Change direction to down
		}
		else if (yPosition >= yLimitTop) {
			movingDirection = 1.0f;  // Change direction to right
		}
		else if (yPosition <= yLimitDown) {
			movingDirection == 0;
			fly = false;
			xPosition = 0;
			yPosition = 0;
		}
		else {
			xPosition += 0.01f;
			yPosition += 0.005f;

		}
	}
	else if (movingDirection == 1.0f) {
		if (xPosition >= xLimitRight) {
			movingDirection == 0;
			fly = false;
		}
	}
	else if (movingDirection == -1.0f) {
		yPosition -= 0.005f;
		if (yPosition == yLimitDown) {
			// Stop movement
			movingDirection = 0.0f;
		}
	}
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.53f, 0.80f, 0.90f, 0.0f);

	projection();
	glMatrixMode(GL_MODELVIEW);        //refer to the model view matrix
	glLoadIdentity();			       //reset the model view matrix
	glTranslatef(tx, ty, tz);

	glPushMatrix();
	lighting();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(xPosition, yPosition, zPosition);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateX, 1, 0, 0);

	GLuint textureArr[10];
	switch (textureSelect) {
	case 1:

		glDeleteTextures(1, &textureArr[0]);

		if (walk)
		{
			glPushMatrix();
			glTranslatef(0, lhy, lhz);
			glRotatef(leftHandAngle, 1, 0, 0);

			drawLeftHand();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, rhy, rhz);
			glRotatef(rightHandAngle, 1, 0, 0);
			drawRightHand();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, lly, llz);
			glRotatef(leftLegAngle, 1, 0, 0);
			drawLeftLeg();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, rly, rlz);
			glRotatef(rightLegAngle, 1, 0, 0);
			drawRightLeg();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef(0, hy1, hz1);
			glRotatef(handAngle, 1, 0, 0);
			drawLeftHand();
			drawRightHand();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, ly1, lz1);
			glRotatef(legAngle, 1, 0, 0);
			drawLeftLeg();
			drawRightLeg();
			glPopMatrix();
		}

		glPushMatrix();
		glRotatef(bodyAngle, 1, 0, 0);
		drawBody();

		glPushMatrix();
		if (nod) {
			if (headAngle > -2.1) {
				headAngle -= 0.03;
			}
			else {
				nod = false;
			}
		}
		else {
			if (headAngle < 0.0) {
				headAngle += 0.03;
			}
		}
		glRotatef(headAngle, 1, 0, 0);
		drawHead();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.03, -0.82, 4);
		glScalef(5.5, 7.0, 7.0);
		glRotatef(180, 0.0, 1.0, 0.0);
		wholeWing();
		glPopMatrix();

		glPopMatrix();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		break;

	case 2:
		//textureChange = 1;

		//glDisable(GL_COLOR_MATERIAL);
		textureArr[1] = loadTexture("road_texture.bmp");
		textureArr[2] = loadTexture("mechanical.bmp");
		textureArr[3] = loadTexture("sea_texture.bmp");
		textureArr[4] = loadTexture("glossy_metal.bmp");
		textureArr[5] = loadTexture("SnowIce.bmp");
		textureArr[6] = loadTexture("marble.bmp");

		if (walk)
		{
			//textureArr[1] = loadTexture("road_texture.bmp");
			if (changing) {
				glBindTexture(GL_TEXTURE_2D, textureArr[textureChange]);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, textureArr[1]);
			}

			glPushMatrix();
			glTranslatef(0, lhy, lhz);
			glRotatef(leftHandAngle, 1, 0, 0);

			drawLeftHand();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, rhy, rhz);
			glRotatef(rightHandAngle, 1, 0, 0);
			drawRightHand();
			glPopMatrix();

			//textureArr[2] = loadTexture("mechanical.bmp");
			if (changing) {
				glBindTexture(GL_TEXTURE_2D, textureArr[textureChange]);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, textureArr[2]);
			}
			glPushMatrix();
			glTranslatef(0, lly, llz);
			glRotatef(leftLegAngle, 1, 0, 0);
			drawLeftLeg();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, rly, rlz);
			glRotatef(rightLegAngle, 1, 0, 0);
			drawRightLeg();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef(0, hy1, hz1);
			glRotatef(handAngle, 1, 0, 0);

			//textureArr[1] = loadTexture("road_texture.bmp");
			if (changing) {
				glBindTexture(GL_TEXTURE_2D, textureArr[textureChange]);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, textureArr[1]);
			}
			drawLeftHand();

			drawRightHand();

			glPopMatrix();

			//textureArr[2] = loadTexture("mechanical.bmp");
			if (changing) {
				glBindTexture(GL_TEXTURE_2D, textureArr[textureChange]);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, textureArr[2]);
			}
			glPushMatrix();
			glTranslatef(0, ly1, lz1);
			glRotatef(legAngle, 1, 0, 0);
			drawLeftLeg();
			drawRightLeg();
			glPopMatrix();
		}
		glPushMatrix();
		glRotatef(bodyAngle, 1, 0, 0);

		//textureArr[3] = loadTexture("sea_texture.bmp");
		if (changing) {
			glBindTexture(GL_TEXTURE_2D, textureArr[textureChange]);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, textureArr[3]);
		}
		drawBody();
		//textureArr[4] = loadTexture("glossy_metal.bmp");
		if (changing) {
			glBindTexture(GL_TEXTURE_2D, textureArr[textureChange]);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, textureArr[4]);
		}

		glPushMatrix();
		if (nod) {
			if (headAngle > -2.1) {
				headAngle -= 0.03;
			}
			else {
				nod = false;
			}
		}
		else {
			if (headAngle < 0.0) {
				headAngle += 0.03;
			}
		}
		glRotatef(headAngle, 1, 0, 0);
		drawHead();
		glPopMatrix();

		//textureArr[5] = loadTexture("SnowIce.bmp");
		//textureArr[6] = loadTexture("marble.bmp");
		if (changing) {
			glBindTexture(GL_TEXTURE_2D, textureArr[textureChange]);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, textureArr[5]);
		}
		glPushMatrix();
		glTranslatef(-0.03, -0.82, 4);
		glScalef(5.5, 7.0, 7.0);
		glRotatef(180, 0.0, 1.0, 0.0);
		wholeWing();
		glPopMatrix();

		glPopMatrix();

		//glDisable(GL_TEXTURE_2D);
		//glDeleteTextures(2, &textureArr[1]);
		glPopMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glDeleteTextures(1, &textureArr[0]);
		glDeleteTextures(1, &textureArr[1]);
		glDeleteTextures(1, &textureArr[2]);
		glDeleteTextures(1, &textureArr[3]);
		glDeleteTextures(1, &textureArr[4]);
		glDeleteTextures(1, &textureArr[5]);
		glDeleteTextures(1, &textureArr[6]);
		glDisable(GL_TEXTURE_2D);
		break;
	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		10, 0, 700, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (shootToggle && cannonOn) {
			if (ballZPosition <= 15.0f) { // Change condition to check if ballZPosition is within the desired range
				ballZPosition += 0.5f; // Change direction of movement by subtracting from ballZPosition
			}
			else {
				shootToggle = false;
				ballZPosition = 0.15f;
				ballSize = radius / 23.0f;
			}
		}


		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------