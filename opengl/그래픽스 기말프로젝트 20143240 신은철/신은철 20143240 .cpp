#include <windows.h>
#include <glut.h> 
#include <glu.h> 
#include <gl.h>
#include <time.h>
#include <stdio.h>
#include <mmsystem.h>
#include <stdlib.h>
#pragma comment(lib,"winmm.lib")

#define _C 260.502
//TO DO �Ҹ��ֱ�

GLfloat X = 0, Y = 0, Z = 0;
int randFace;
int middle = 0;
int front = 0;
int input;
bool start;
bool R_turn, L_turn;
bool derail = 0;
int MenuChk = 0;
GLfloat x, y;

void ect() {
	if (input != randFace) {
		derail = 1;
	}
}

void DrawMoon() {
	glColor3f(1.0f, 0.894f, 0.0f);
	glPushMatrix();
	glTranslatef(3.0f, 2.0f, 1.0f);
	glutSolidSphere(0.2, 30, 45);
	glPopMatrix();
}

void DrawCloud() {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0, 2.0, 1.0);
	glutSolidSphere(.07, 30, 45);
	glTranslatef(0.0, 0.0, 0.1);
	glutSolidSphere(.1, 30, 45);
	glTranslatef(0.0, 0.0, 0.1);
	glutSolidSphere(.07, 30, 45);
	glPopMatrix();
}

void DrawField() {

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0f, -0.7f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(10.0, 0.0, 3.0);
	glVertex3f(10.0, 0.0, -3.0);
	glVertex3f(-10.0, 0.0, -3.0);
	glVertex3f(-10.0, 0.0, 3.0);
	glEnd();
	glPopMatrix();

}

void DrawTrain() {

	glPushMatrix();
	glTranslatef(-3.3 + (GLfloat)X, Y, 1.5 + Z); //LookAt ���̰��ϱ�

	glPushMatrix(); //���� �պκ�
	glTranslatef(0.5, 0.0, 0.0);
	glScalef(3, 1, 1);
	glRotatef(front, (GLfloat)derail, 1.0, 0.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidCube(0.2);
	glTranslatef(-0.21f, 0.0f, 0.0f);

	glPushMatrix(); //���� �޺κ�
	glRotatef(middle, (GLfloat)derail, 1.0, 0.0);
	glutSolidCube(0.2);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}

void MyDisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.749f, 1.0f, 0.0f);  //�ϴû�
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (MenuChk == 11) { //��
		GLfloat sourceLight[] = { 0.55f, 0.55f, 0.55f, 1.0f };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

		glPushMatrix();
		DrawCloud();
		glTranslatef(4.0, 0.0, 0.0);
		DrawCloud();
		glTranslatef(-8.0, 0.0, 1.0);
		DrawCloud();
		glPopMatrix();

	}

	if (MenuChk == 12) {
		GLfloat sourceLight[] = { 0.15f, 0.15f, 0.15f, 1.0f };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lightPos[] = { 10.0f, 5.0f, 5.0f, -10.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

		glClearColor(0.0f, 0.133f, 0.4f, 0.0f); //����
		glPushMatrix();
		DrawMoon();
		glPopMatrix();

	}

	if (X >5) {
		GLfloat sourceLight[] = { 0.65f, 0.65f, 0.75f, 1.0f };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	}
	DrawField();
	DrawTrain();
	ect();
	glutSwapBuffers();
}

void MyReshape(int w, int h) {
	GLfloat nRange = 1.0f;
	if (h == 0)   h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w,
			nRange*h / w, nRange, -nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange,
			nRange, -nRange, nRange);

	gluPerspective(45.0, (GLsizei)w / (GLsizei)h, 0.0, 100); //ī�޶�� ������ ��ü�� �̷�� ��ǥ�� ����

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(-5.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void TrainMove(int value) {

	if (start == 1 && derail == 0) {
		if (X < 5.0) {
			X += (GLfloat)0.1;
			if (R_turn == 1 && X > 1.2) { //���� �ٲٱ�
				Z += 0.1f;
			}
			if (L_turn == 1 && X > 1.2) {
				Z -= 0.1f;
			}
		}
	}

	if (start == 1 && derail == 1) {
		if (X < 2.0) {
			X += (GLfloat)0.1;
			if (R_turn == 1 && X > 1.2) { //���� �ٲٱ�
				Z += 0.1f;
			}
			if (L_turn == 1 && X > 1.2) {
				Z -= 0.1f;
			}
		}
	}

	if (X>0.5&&R_turn == 1) {
		front = -20;
		middle = 10;
	}

	if (X > 1.2&&R_turn == 1) {
		front = 0;
		middle = -30;
	}
	if (X > 1.4&&R_turn == 1) {
		middle = 0;
		R_turn = 0;
	}

	if (X > 0.3&&R_turn == 1) {
		x += 0.008f;
	}

	if (X > 0.4 && L_turn == 1) {
		x += 0.006f;
	}

	if (X >= 0.500000&&X<0.5001&&L_turn == 1) {
		front = 20;
		middle = -10;
	}

	if (X > 1.2&&L_turn == 1) {
		front = 0;
		middle = 30;
	}

	if (X > 1.4&&L_turn == 1) {
		middle = 0;
		L_turn = 0;
	}

	if (X <2.0&&derail == 1) {
		front += 10;
		middle += 10;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TrainMove, 1);

}

void SpecialKey(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		input = 2;
		start = 1;
		front = 0;
		middle = 0;
		Beep(_C, 500);
		Sleep(200);
		Beep(_C, 800);
	}

	if (key == GLUT_KEY_RIGHT) {
		input = 3;
		start = 1;
		R_turn = 1;
		Beep(_C, 500);
		Sleep(200);
		Beep(_C, 800);
	}

	if (key == GLUT_KEY_LEFT) {
		input = 1;
		start = 1;
		L_turn = 1;
		Beep(_C, 500);
		Sleep(200);
		Beep(_C, 800);
	}
	glutPostRedisplay();
	/*if (start == 1) {
	PlaySound(TEXT("�������.wav"), NULL, SND_ASYNC);
	}*/
}


void SetupRC()
{
	GLfloat whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f }; // rgb ���� ��
	GLfloat lightPos[] = { -10.0f, 5.0f, 5.0f, -10.0f };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glFrontFace(GL_CCW); //�ð�ݴ�������� �׸����� �ո�
	glEnable(GL_LIGHTING); // �¾��-> �� ���� ������� ��� ������ ������� //��������

	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight); //AMBIENT - �ֺ���
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight); //DIFFUSE - �л걤
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular); // �ݻ籤
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0); // ���� ����

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

} //����

void MyKeyBoard(unsigned char KeyPress, int x, int y) { //�ʱ�ȭ 
	if (KeyPress == '0') {
		X = 0;
		Y = 0;
		Z = 0;
		start = 0;
		R_turn = 0;
		L_turn = 0;
		input = 0;
		middle = 0;
		front = 0;
		derail = 0;
		randFace = rand() % 3 + 1;
		input = randFace;
		x = 0;
		GLfloat whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
		GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
		GLfloat lightPos[] = { -10.0f, 5.0f, 5.0f, -10.0f };
		GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	}

	if (KeyPress == 27) {
		exit(0);
	}

	switch (randFace) {
	case 1:
		printf("������ ������ �����Դϴ�.\n");
		break;

	case 2:
		printf("������ ������ �����Դϴ�. \n");
		break;

	case 3:
		printf("������ ������ �������Դϴ�.\n");
		break;

	default:
		break;
	}
}

//�ʱ�ȭ 


void MyMenu(int ID) // �޴� ó�� �ݹ��Լ�
{
	if (ID == 3)
	{
		exit(0);
	}

	if (ID == 11) {

		MenuChk = ID;
		glutPostRedisplay();
	}

	if (ID == 12) {

		MenuChk = ID;
		glutPostRedisplay();
	}

	else
	{
		MenuChk = ID;
		glutPostRedisplay();
	}
	glutPostRedisplay();
}

void MenuFunc()
{

	GLint SubMenuID1 = glutCreateMenu(MyMenu); // ���õ� �޴��� ó���ϴ� �ݹ��Լ� ���
	glutAddMenuEntry("��", 11);
	glutAddMenuEntry("��", 12);


	GLint MainMenuID = glutCreateMenu(MyMenu); // ���õ� �޴��� ó���ϴ� �ݹ��Լ� ���
	glutAddSubMenu("�ð�", SubMenuID1);
	glutAddMenuEntry("����", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("������ �̿��� �̴ϰ���");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	srand(time(NULL));
	randFace = rand() % 3 + 1;
	input = randFace;
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(100, TrainMove, 1);
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(MyKeyBoard);
	MenuFunc();


	printf("--------------------------------------------------\n");
	printf("������ ���⿡ ���� ����Ű�� ������ ���۵˴ϴ� !\n");
	printf("���� 0�� ������ �ʱ�ȭ �˴ϴ�!\n");
	printf("�޴��� ���� ���� ���� ������ �� �ֽ��ϴ�! \n");
	printf("--------------------------------------------------\n\n");


	switch (randFace) {
	case 1:
		printf("������ ������ �����Դϴ�.\n");
		break;
	case 2:
		printf("������ ������ �����Դϴ�. \n");
		break;
	case 3:
		printf("������ ������ �������Դϴ�.\n");
		break;
	default:
		break;
	}

	SetupRC();
	glutMainLoop();
	return 0;
}