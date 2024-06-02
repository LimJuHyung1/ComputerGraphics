#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#define _CRT_SECURE_NO_WARNINGS
#define PLAY_SOUND(filename) PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);

int width = 800;   // 초기 가시 부피의 가로 길이
int height = 800;  // 초기 가시 부피의 세로 길이

GLfloat MARIOrot[4] = { 0.0f };
bool MARIOPixelTrigger = false;
GLfloat xrot = 1.0f, yrot = 0.0f, zrot = 0.0f;

int CameraMode = 1;
GLfloat R = 1.0f, G = 1.0f, B = 1.0f;

GLuint tex[4];
AUX_RGBImageRec* texRec[4]; //<1>
unsigned int MyTextureObject[1];

// 큐브를 그리는 함수
//-----------------------------------------------------------------------//
void MARIO_BlackCube(float xpos, float ypos, float zpos, GLfloat srot);
void MARIO_WhiteCube(float xpos, float ypos, float zpos, GLfloat srot);
void MARIO_RedCube(float xpos, float ypos, float zpos, GLfloat srot);
void MARIO_OrangeCube(float xpos, float ypos, float zpos, GLfloat srot);
void MARIO_BrownCube(float xpos, float ypos, float zpos, GLfloat srot);
void MARIO_SkinCube(float xpos, float ypos, float zpos, GLfloat srot);
void MARIO_BlueCube(float xpos, float ypos, float zpos, GLfloat srot);
//-----------------------------------------------------------------------//
void DrawTextTopFace();
void DrawTextFrontFace();
void DrawTextRightFace();
void DrawTextLeftFace();
void DrawTextBottomFace();
void DrawTextBackFace();
//-----------------------------------------------------------------------//
void END_Block(float xPos, float yPos, float zPos);
void END_Ground(float xPos, float yPos, float zPos);
void END_Box(float xPos, float yPos, float zPos);
void END_Logo(float xPos, float yPos, float zPos);
//-----------------------------------------------------------------------//


void WaitTimer(int value);

AUX_RGBImageRec* LoadBMP(const char* szFilename);
int LoadGLTextures(char* szFilePath);
bool setting();

// OpenGL 초기화 함수
void Initialize() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 배경색을 검은색으로 설정
    glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
}

void MARIOCut1(int i) {
    MARIO_WhiteCube(0.2, 2.0, -10, MARIOrot[i]);
    MARIO_RedCube(0.4, 2.0, -10, MARIOrot[i]);

    MARIO_RedCube(0.2, 1.8, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.4, 1.8, -10, MARIOrot[i]);
    MARIO_RedCube(0.6, 1.8, -10, MARIOrot[i]);
    MARIO_RedCube(0.8, 1.8, -10, MARIOrot[i]);

    MARIO_WhiteCube(0.2, 1.6, -10, MARIOrot[i]);
    MARIO_RedCube(0.4, 1.6, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.6, 1.6, -10, MARIOrot[i]);
    MARIO_RedCube(0.8, 1.6, -10, MARIOrot[i]);
    MARIO_RedCube(1.0, 1.6, -10, MARIOrot[i]);

    MARIO_WhiteCube(0.2, 1.4, -10, MARIOrot[i]);
    MARIO_RedCube(0.4, 1.4, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.6, 1.4, -10, MARIOrot[i]);
    MARIO_RedCube(0.8, 1.4, -10, MARIOrot[i]);
    MARIO_RedCube(1.0, 1.4, -10, MARIOrot[i]);
    MARIO_RedCube(1.2, 1.4, -10, MARIOrot[i]);

    MARIO_WhiteCube(0.2, 1.2, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.4, 1.2, -10, MARIOrot[i]);
    MARIO_RedCube(0.6, 1.2, -10, MARIOrot[i]);
    MARIO_RedCube(0.8, 1.2, -10, MARIOrot[i]);
    MARIO_RedCube(1.0, 1.2, -10, MARIOrot[i]);
    MARIO_RedCube(1.2, 1.2, -10, MARIOrot[i]);
    MARIO_RedCube(1.4, 1.2, -10, MARIOrot[i]);

    MARIO_OrangeCube(0.2, 1.0, -10, MARIOrot[i]);
    MARIO_OrangeCube(0.4, 1.0, -10, MARIOrot[i]);
    MARIO_OrangeCube(0.6, 1.0, -10, MARIOrot[i]);
    MARIO_OrangeCube(0.8, 1.0, -10, MARIOrot[i]);
    MARIO_RedCube(1.0, 1.0, -10, MARIOrot[i]);
    MARIO_RedCube(1.2, 1.0, -10, MARIOrot[i]);
    MARIO_RedCube(1.4, 1.0, -10, MARIOrot[i]);

    MARIO_RedCube(0.2, 0.8, -10, MARIOrot[i]);
    MARIO_RedCube(0.4, 0.8, -10, MARIOrot[i]);
    MARIO_RedCube(0.6, 0.8, -10, MARIOrot[i]);
    MARIO_RedCube(0.8, 0.8, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.0, 0.8, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.2, 0.8, -10, MARIOrot[i]);
    MARIO_RedCube(1.4, 0.8, -10, MARIOrot[i]);
    MARIO_RedCube(1.6, 0.8, -10, MARIOrot[i]);

    MARIO_OrangeCube(0.2, 0.6, -10, MARIOrot[i]);
    MARIO_OrangeCube(0.4, 0.6, -10, MARIOrot[i]);
    MARIO_OrangeCube(0.6, 0.6, -10, MARIOrot[i]);
    MARIO_OrangeCube(0.8, 0.6, -10, MARIOrot[i]);
    MARIO_RedCube(1.0, 0.6, -10, MARIOrot[i]);
    MARIO_RedCube(1.2, 0.6, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.4, 0.6, -10, MARIOrot[i]);
    MARIO_RedCube(1.6, 0.6, -10, MARIOrot[i]);
}
void MARIOCut2(int i) {
        MARIO_OrangeCube(0, 0.6, -10, MARIOrot[i]);
        MARIO_RedCube(0, 0.8, -10, MARIOrot[i]);
        MARIO_OrangeCube(0, 1.0, -10, MARIOrot[i]);
        MARIO_WhiteCube(0, 1.2, -10, MARIOrot[i]);
        MARIO_RedCube(0, 1.4, -10, MARIOrot[i]);
        MARIO_RedCube(0, 1.6, -10, MARIOrot[i]);
        MARIO_WhiteCube(0, 1.8, -10, MARIOrot[i]);
        MARIO_WhiteCube(0, 2.0, -10, MARIOrot[i]);

        MARIO_WhiteCube(-0.2, 2.0, -10, MARIOrot[i]);
        MARIO_RedCube(-0.4, 2.0, -10, MARIOrot[i]);

        MARIO_RedCube(-0.2, 1.8, -10, MARIOrot[i]);
        MARIO_WhiteCube(-0.4, 1.8, -10, MARIOrot[i]);
        MARIO_RedCube(-0.6, 1.8, -10, MARIOrot[i]);
        MARIO_RedCube(-0.8, 1.8, -10, MARIOrot[i]);

        MARIO_WhiteCube(-0.2, 1.6, -10, MARIOrot[i]);
        MARIO_RedCube(-0.4, 1.6, -10, MARIOrot[i]);
        MARIO_WhiteCube(-0.6, 1.6, -10, MARIOrot[i]);
        MARIO_RedCube(-0.8, 1.6, -10, MARIOrot[i]);
        MARIO_RedCube(-1.0, 1.6, -10, MARIOrot[i]);

        MARIO_WhiteCube(-0.2, 1.4, -10, MARIOrot[i]);
        MARIO_RedCube(-0.4, 1.4, -10, MARIOrot[i]);
        MARIO_WhiteCube(-0.6, 1.4, -10, MARIOrot[i]);
        MARIO_RedCube(-0.8, 1.4, -10, MARIOrot[i]);
        MARIO_RedCube(-1.0, 1.4, -10, MARIOrot[i]);
        MARIO_RedCube(-1.2, 1.4, -10, MARIOrot[i]);

        MARIO_WhiteCube(-0.2, 1.2, -10, MARIOrot[i]);
        MARIO_WhiteCube(-0.4, 1.2, -10, MARIOrot[i]);
        MARIO_RedCube(-0.6, 1.2, -10, MARIOrot[i]);
        MARIO_RedCube(-0.8, 1.2, -10, MARIOrot[i]);
        MARIO_RedCube(-1.0, 1.2, -10, MARIOrot[i]);
        MARIO_RedCube(-1.2, 1.2, -10, MARIOrot[i]);
        MARIO_RedCube(-1.4, 1.2, -10, MARIOrot[i]);

        MARIO_OrangeCube(-0.2, 1.0, -10, MARIOrot[i]);
        MARIO_OrangeCube(-0.4, 1.0, -10, MARIOrot[i]);
        MARIO_OrangeCube(-0.6, 1.0, -10, MARIOrot[i]);
        MARIO_OrangeCube(-0.8, 1.0, -10, MARIOrot[i]);
        MARIO_RedCube(-1.0, 1.0, -10, MARIOrot[i]);
        MARIO_RedCube(-1.2, 1.0, -10, MARIOrot[i]);
        MARIO_RedCube(-1.4, 1.0, -10, MARIOrot[i]);

        MARIO_RedCube(-0.2, 0.8, -10, MARIOrot[i]);
        MARIO_RedCube(-0.4, 0.8, -10, MARIOrot[i]);
        MARIO_RedCube(-0.6, 0.8, -10, MARIOrot[i]);
        MARIO_RedCube(-0.8, 0.8, -10, MARIOrot[i]);
        MARIO_OrangeCube(-1.0, 0.8, -10, MARIOrot[i]);
        MARIO_OrangeCube(-1.2, 0.8, -10, MARIOrot[i]);
        MARIO_RedCube(-1.4, 0.8, -10, MARIOrot[i]);
        MARIO_RedCube(-1.6, 0.8, -10, MARIOrot[i]);

        MARIO_OrangeCube(-0.2, 0.6, -10, MARIOrot[i]);
        MARIO_OrangeCube(-0.4, 0.6, -10, MARIOrot[i]);
        MARIO_OrangeCube(-0.6, 0.6, -10, MARIOrot[i]);
        MARIO_OrangeCube(-0.8, 0.6, -10, MARIOrot[i]);
        MARIO_RedCube(-1.0, 0.6, -10, MARIOrot[i]);
        MARIO_RedCube(-1.2, 0.6, -10, MARIOrot[i]);
        MARIO_OrangeCube(-1.4, 0.6, -10, MARIOrot[i]);
        MARIO_RedCube(-1.6, 0.6, -10, MARIOrot[i]);    
}
void MARIOCut3(int i) {
    MARIO_SkinCube(-0.2, 0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0, 0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0.2, 0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.2, 0, -10, MARIOrot[i]);
    MARIO_SkinCube(0, 0, -10, MARIOrot[i]);
    MARIO_SkinCube(0.2, 0, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.2, -0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0, -0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0.2, -0.2, -10, MARIOrot[i]);

    MARIO_SkinCube(-0.4, 0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.2, 0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(0.0, 0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(0.2, 0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, 0.4, -10, MARIOrot[i]);
    MARIO_BlackCube(-0.4, 0.2, -10, MARIOrot[i]);
    MARIO_BlackCube(0.4, 0.2, -10, MARIOrot[i]);
    MARIO_WhiteCube(-0.4, 0.0, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.4, 0.0, -10, MARIOrot[i]);
    MARIO_BlackCube(-0.4, -0.2, -10, MARIOrot[i]);
    MARIO_BlackCube(0.4, -0.2, -10, MARIOrot[i]);
    MARIO_BlackCube(-0.4, -0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.2, -0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(0.0, -0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(0.2, -0.4, -10, MARIOrot[i]);
    MARIO_BlackCube(0.4, -0.4, -10, MARIOrot[i]);

    MARIO_SkinCube(-0.4, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.2, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(0, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(0.2, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, -0.6, -10, MARIOrot[i]);

    MARIO_SkinCube(0, -0.8, -10, MARIOrot[i]);
    MARIO_SkinCube(0, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(0, -1.2, -10, MARIOrot[i]);
    MARIO_RedCube(0, -1.6, -10, MARIOrot[i]);
    MARIO_RedCube(0, -1.8, -10, MARIOrot[i]);
    MARIO_SkinCube(0, -2.0, -10, MARIOrot[i]);
    MARIO_SkinCube(0, -2.2, -10, MARIOrot[i]);

    for (float j = -0.2; j > -1.6; j -= 0.2) {
        MARIO_SkinCube(j, -0.8, -10, MARIOrot[i]);
    }
    MARIO_SkinCube(-1.8, -0.8, -10, MARIOrot[i]);

    MARIO_SkinCube(-0.2, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.4, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.6, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.4, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.8, -1.0, -10, MARIOrot[i]);

    MARIO_SkinCube(-0.2, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.4, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.2, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.4, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.6, -1.2, -10, MARIOrot[i]);

    MARIO_BlackCube(-0.2, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.4, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.8, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.0, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.2, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.4, -1.4, -10, MARIOrot[i]);

    MARIO_RedCube(-0.2, -1.6, -10, MARIOrot[i]);
    MARIO_RedCube(-0.4, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.6, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.8, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.0, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.2, -1.6, -10, MARIOrot[i]);

    MARIO_RedCube(-0.2, -1.8, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.4, -1.8, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.6, -1.8, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.8, -1.8, -10, MARIOrot[i]);

    MARIO_SkinCube(-0.2, -2.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.4, -2.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.6, -2.0, -10, MARIOrot[i]);

    MARIO_SkinCube(-0.2, -2.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.4, -2.2, -10, MARIOrot[i]);
    //-----------------------------------------------------//
    for (float j = 0.2; j <= 1.6; j += 0.2) {
        MARIO_SkinCube(j, -0.8, -10, MARIOrot[i]);
    }
    MARIO_SkinCube(1.8, -0.8, -10, MARIOrot[i]);

    MARIO_SkinCube(0.2, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(0.6, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(1.4, -1.0, -10, MARIOrot[i]);
    MARIO_SkinCube(1.8, -1.0, -10, MARIOrot[i]);

    MARIO_SkinCube(0.2, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(1.2, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(1.4, -1.2, -10, MARIOrot[i]);
    MARIO_SkinCube(1.6, -1.2, -10, MARIOrot[i]);

    MARIO_BlackCube(0.2, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(0.8, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(1.0, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(1.2, -1.4, -10, MARIOrot[i]);
    MARIO_SkinCube(1.4, -1.4, -10, MARIOrot[i]);

    MARIO_RedCube(0.2, -1.6, -10, MARIOrot[i]);
    MARIO_RedCube(0.4, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(0.6, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(0.8, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(1.0, -1.6, -10, MARIOrot[i]);
    MARIO_SkinCube(1.2, -1.6, -10, MARIOrot[i]);

    MARIO_RedCube(0.2, -1.8, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, -1.8, -10, MARIOrot[i]);
    MARIO_SkinCube(0.6, -1.8, -10, MARIOrot[i]);
    MARIO_SkinCube(0.8, -1.8, -10, MARIOrot[i]);

    MARIO_SkinCube(0.2, -2.0, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, -2.0, -10, MARIOrot[i]);
    MARIO_SkinCube(0.6, -2.0, -10, MARIOrot[i]);

    MARIO_SkinCube(0.2, -2.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0.4, -2.2, -10, MARIOrot[i]);

    MARIO_RedCube(-1.6, 0.4, -10, MARIOrot[i]);
    MARIO_OrangeCube(-1.4, 0.4, -10, MARIOrot[i]);
    MARIO_RedCube(-1.2, 0.4, -10, MARIOrot[i]);
    MARIO_OrangeCube(-1.0, 0.4, -10, MARIOrot[i]);
    MARIO_OrangeCube(-0.8, 0.4, -10, MARIOrot[i]);

    MARIO_RedCube(-1.6, 0.2, -10, MARIOrot[i]);
    MARIO_OrangeCube(-1.4, 0.2, -10, MARIOrot[i]);
    MARIO_OrangeCube(-1.2, 0.2, -10, MARIOrot[i]);
    MARIO_OrangeCube(-1.0, 0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.8, 0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-0.6, 0.2, -10, MARIOrot[i]);

    MARIO_RedCube(-1.8, 0.0, -10, MARIOrot[i]);
    MARIO_BrownCube(-1.6, 0.0, -10, MARIOrot[i]);
    MARIO_BrownCube(-1.4, 0.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.2, 0.0, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.0, 0.0, -10, MARIOrot[i]);
    MARIO_WhiteCube(-0.8, 0.0, -10, MARIOrot[i]);
    MARIO_WhiteCube(-0.6, 0.0, -10, MARIOrot[i]);

    MARIO_OrangeCube(-1.8, -0.2, -10, MARIOrot[i]);
    MARIO_BrownCube(-1.6, -0.2, -10, MARIOrot[i]);
    MARIO_BrownCube(-1.4, -0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.2, -0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.0, -0.2, -10, MARIOrot[i]);
    MARIO_WhiteCube(-0.8, -0.2, -10, MARIOrot[i]);
    MARIO_BlueCube(-0.6, -0.2, -10, MARIOrot[i]);

    MARIO_OrangeCube(-1.6, -0.4, -10, MARIOrot[i]);
    MARIO_BrownCube(-1.4, -0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.2, -0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.0, -0.4, -10, MARIOrot[i]);
    MARIO_WhiteCube(-0.8, -0.4, -10, MARIOrot[i]);
    MARIO_BlueCube(-0.6, -0.4, -10, MARIOrot[i]);

    MARIO_SkinCube(-1.8, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.6, -0.6, -10, MARIOrot[i]);
    MARIO_BrownCube(-1.4, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.2, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(-1.0, -0.6, -10, MARIOrot[i]);
    MARIO_WhiteCube(-0.8, -0.6, -10, MARIOrot[i]);
    MARIO_BlueCube(-0.6, -0.6, -10, MARIOrot[i]);
    //--------------------------------------------//
    MARIO_RedCube(1.6, 0.4, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.4, 0.4, -10, MARIOrot[i]);
    MARIO_RedCube(1.2, 0.4, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.0, 0.4, -10, MARIOrot[i]);
    MARIO_OrangeCube(0.8, 0.4, -10, MARIOrot[i]);

    MARIO_RedCube(1.6, 0.2, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.4, 0.2, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.2, 0.2, -10, MARIOrot[i]);
    MARIO_OrangeCube(1.0, 0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0.8, 0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(0.6, 0.2, -10, MARIOrot[i]);

    MARIO_RedCube(1.8, 0.0, -10, MARIOrot[i]);
    MARIO_BrownCube(1.6, 0.0, -10, MARIOrot[i]);
    MARIO_BrownCube(1.4, 0.0, -10, MARIOrot[i]);
    MARIO_SkinCube(1.2, 0.0, -10, MARIOrot[i]);
    MARIO_SkinCube(1.0, 0.0, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.8, 0.0, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.6, 0.0, -10, MARIOrot[i]);

    MARIO_OrangeCube(1.8, -0.2, -10, MARIOrot[i]);
    MARIO_BrownCube(1.6, -0.2, -10, MARIOrot[i]);
    MARIO_BrownCube(1.4, -0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(1.2, -0.2, -10, MARIOrot[i]);
    MARIO_SkinCube(1.0, -0.2, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.8, -0.2, -10, MARIOrot[i]);
    MARIO_BlueCube(0.6, -0.2, -10, MARIOrot[i]);

    MARIO_OrangeCube(1.6, -0.4, -10, MARIOrot[i]);
    MARIO_BrownCube(1.4, -0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(1.2, -0.4, -10, MARIOrot[i]);
    MARIO_SkinCube(1.0, -0.4, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.8, -0.4, -10, MARIOrot[i]);
    MARIO_BlueCube(0.6, -0.4, -10, MARIOrot[i]);

    MARIO_SkinCube(1.8, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(1.6, -0.6, -10, MARIOrot[i]);
    MARIO_BrownCube(1.4, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(1.2, -0.6, -10, MARIOrot[i]);
    MARIO_SkinCube(1.0, -0.6, -10, MARIOrot[i]);
    MARIO_WhiteCube(0.8, -0.6, -10, MARIOrot[i]);
    MARIO_BlueCube(0.6, -0.6, -10, MARIOrot[i]);



}
void Ending() {
    for (float z = -3.0f; z <= 3.2f; z += 0.2f) {
        END_Ground(10.0f, -2.0f, z);
        END_Ground(10.0f, -2.2f, z);
        END_Ground(10.0f, -2.4f, z);
        END_Ground(10.0f, -2.6f, z);
        END_Ground(10.0f, -2.8f, z);
        END_Ground(10.0f, -3.0f, z);
    }

    END_Box(10.0f, -0.4f, -1.6f);

    END_Block(10.0f, -1.2f, -2.4f);
    END_Block(10.0f, -1.2f, -2.2f);
    END_Box(10.0f, -1.2f, -2.0f);
    END_Block(10.0f, -1.2f, -1.8f);
    END_Block(10.0f, -1.2f, -1.6f);
    END_Block(10.0f, -1.2f, -1.4f);

    END_Block(10.0f, -0.8f, -0.6f);
    END_Block(10.0f, -0.8f, -0.4f);
    END_Block(10.0f, -0.8f, -0.2f);
    END_Block(10.0f, -0.8f, 0.0f);
    END_Block(10.0f, -0.8f, 0.2f);
    END_Block(10.0f, -0.8f, 0.4f);

    END_Block(10.0f, -1.8f, 1.4f);
    END_Block(10.0f, -1.8f, 1.6f);
    END_Block(10.0f, -1.8f, 2.2f);
    END_Block(10.0f, -1.8f, 2.4f);
    END_Block(10.0f, -1.6f, 1.4f);
    END_Block(10.0f, -1.6f, 1.6f);
    END_Block(10.0f, -1.6f, 2.2f);
    END_Block(10.0f, -1.6f, 2.4f);
    END_Block(10.0f, -1.4f, 1.4f);
    END_Block(10.0f, -1.4f, 1.6f);
    END_Block(10.0f, -1.4f, 2.2f);
    END_Block(10.0f, -1.4f, 2.4f);
    END_Block(10.0f, -1.2f, 1.4f);
    END_Block(10.0f, -1.2f, 1.6f);
    END_Block(10.0f, -1.2f, 1.8f);
    END_Block(10.0f, -1.2f, 2.0f);
    END_Block(10.0f, -1.2f, 2.2f);
    END_Block(10.0f, -1.2f, 2.4f);

    END_Block(10.0f, -1.0f, 1.4f);
    END_Block(10.0f, -1.0f, 1.9f);
    END_Block(10.0f, -1.0f, 2.4f);

    END_Logo(10.0f, 1.5f, 0.0f);
}

void Light() {
    // 조명 활성화
    glEnable(GL_LIGHTING);

    // 조명 설정
    GLfloat light_position[] = { 10.0f, 0.0f, 0.0f, 0.0f };
    GLfloat light_ambient[] = { R, G, B, 1.0f };   
    GLfloat white_light[] = { R, G, B, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);

    // 조명 사용
    glEnable(GL_LIGHT0);
}


// 디스플레이 콜백 함수
void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0.0f, 0.0f, 0.0f, // 카메라 위치
        0.0f, 0.0f, -10.0f,  // 목표 위치
        0.0f, 1.0f, 0.0f); // 카메라의 위쪽 방향

    // 카메라 설정    
    if (CameraMode == 1) {
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.2, 3.2, 1, 4, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPopMatrix();
    }

    else if (CameraMode == 2) {
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-3, 0, 1, 4, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPopMatrix();
    }

    else if (CameraMode == 3) {
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -4, 0, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPopMatrix();
    }

    else if (CameraMode == 4) {
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-3, 3, -3, 3, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPopMatrix();        
    }

    else if (CameraMode == 5) {
        setting(); Light();
        gluLookAt(0.0f, 0.0f, 0.0f, // 카메라 위치
            10.0f, 0.0f, 0.0f,  // 목표 위치
            0.0f, 1.0f, 0.0f); // 카메라의 위쪽 방향

        glPushMatrix();                
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();        
        glOrtho(-3, 3, -3, 3, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();        
        glPopMatrix();
    }


    MARIOCut1(0);
    MARIOCut2(1);
    MARIOCut3(2);
    Ending();
    glFlush();
    glutSwapBuffers();
}

// 윈도우 크기 변경 콜백 함수
void Reshape(int w, int h) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    float cubeSize = 5.0f;
    glOrtho(-cubeSize * aspectRatio, cubeSize * aspectRatio, -cubeSize, cubeSize, -100.0f, 100.0f); // 직교 투영 설정
}
//---------------------------------------//
bool IsMARIOCut1() {
    return MARIOrot[1] > -180 && MARIOrot[0] <= -180 ? true : false;
}
bool IsMARIOCut2() {
    return MARIOrot[2] > -180 && MARIOrot[1] <= -180 ? true : false;
}
bool IsMARIOCut3() {
    return MARIOrot[3] > -180 && MARIOrot[2] <= -180 ? true : false;
}
void PlusMARIORot() {
    MARIOrot[0] -= 2;
    MARIOrot[1] -= 2;
    MARIOrot[2] -= 2;
}

void MARIOTimer1(int value) {
    if (MARIOrot[0] == -180) {
        glutTimerFunc(1000, WaitTimer, 1);
        CameraMode += 1;
    }

    if (MARIOrot[0] > -180) {
        MARIOrot[0] -= 1;
        glutPostRedisplay();
        glutTimerFunc(10, MARIOTimer1, 1);
    }
}

void MARIOTimer2(int value) {
    if (MARIOrot[1] == -180) {
        glutTimerFunc(1000, WaitTimer, 1);
        CameraMode += 1;        
    }

    if (IsMARIOCut1() == true) {
        MARIOrot[1] -= 1;
        glutPostRedisplay();
        glutTimerFunc(10, MARIOTimer2, 1);
    }
}

void MARIOTimer3(int value) {
    if (MARIOrot[2] == -180) {   
        glutTimerFunc(1000, WaitTimer, 1);
        CameraMode += 1;
    }

    if (IsMARIOCut2() == true) {
        MARIOrot[2] -= 1;
        glutPostRedisplay();
        glutTimerFunc(10, MARIOTimer3, 1);
    }
}

void MARIOTimer4(int value) {
    if (MARIOrot[2] == -360) {
        glutTimerFunc(1000, WaitTimer, 1);
        CameraMode += 1;
    }

    if (MARIOrot[2] > -360) { MARIOPixelTrigger = true; }
    else { MARIOPixelTrigger = false; }

    if (MARIOPixelTrigger == true) {
        PlusMARIORot();
        glutPostRedisplay();
        glutTimerFunc(10, MARIOTimer4, 1);
    }
    else if (MARIOPixelTrigger == true) {
        PlusMARIORot();
        glutPostRedisplay();
        glutTimerFunc(1000, MARIOTimer4, 1);
    }
}

void MinusRGB() {
    R -= 0.05f;
    G -= 0.05f;
    B -= 0.05f;
}

void MARIOTimer5(int value) {
    if (R != 0) { 
        MinusRGB();
        glutPostRedisplay();
        glutTimerFunc(50, MARIOTimer5, 1);
    }
    if (R < 0) { CameraMode++; }
}

void ENDTimer(int value) {
    exit(0);
}

void WaitTimer(int value) {
    glutPostRedisplay();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("2019305061 임주형");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glEnable(GL_COLOR_MATERIAL);
    Initialize();
    PLAY_SOUND("SuperMario.wav");

    switch (CameraMode) {
    case 1:
        glutTimerFunc(0, MARIOTimer1, 0);
    case 2:
        glutTimerFunc(5000, MARIOTimer2, 0);
    case 3:
        glutTimerFunc(9000, MARIOTimer3, 0);
    case 4:
        glutTimerFunc(15000, MARIOTimer4, 0);
    case 5:
        glutTimerFunc(21000, MARIOTimer5, 0);
    case 6:
        glutTimerFunc(24000, ENDTimer, 0);
    }

    glutMainLoop();
    return 0;
}

void Front() {
    glVertex3f(-0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, 0.1f);
    glVertex3f(0.1f, 0.1f, 0.1f);
    glVertex3f(-0.1f, 0.1f, 0.1f);
}
void Back(){
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(-0.1f, 0.1f, -0.1f);
    glVertex3f(0.1f, 0.1f, -0.1f);
    glVertex3f(0.1f, -0.1f, -0.1f);
}
void Top() {
    glVertex3f(-0.1f, 0.1f, -0.1f);
    glVertex3f(-0.1f, 0.1f, 0.1f);
    glVertex3f(0.1f, 0.1f, 0.1f);
    glVertex3f(0.1f, 0.1f, -0.1f);
}
void Bottom() {
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(0.1f, -0.1f, -0.1f);
    glVertex3f(0.1f, -0.1f, 0.1f);
    glVertex3f(-0.1f, -0.1f, 0.1f);
}
void Right() {
    glVertex3f(0.1f, -0.1f, -0.1f);
    glVertex3f(0.1f, 0.1f, -0.1f);
    glVertex3f(0.1f, 0.1f, 0.1f);
    glVertex3f(0.1f, -0.1f, 0.1f);
}
void Left() {
    glVertex3f(-0.1f, -0.1f, -0.1f);
    glVertex3f(-0.1f, -0.1f, 0.1f);
    glVertex3f(-0.1f, 0.1f, 0.1f);
    glVertex3f(-0.1f, 0.1f, -0.1f);
}


void MARIO_BlackCube(float xpos, float ypos, float zpos, GLfloat srot) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); 
    glRotatef(srot, xrot, yrot, zrot);
    glBegin(GL_QUADS);

    // 앞면
    glColor3f(0.0f, 0.0f, 0.0f);
    Front();
    // 뒷면
    glColor3f(0.0f, 0.0f, 0.0f);
    Back();
    // 윗면
    glColor3f(0.0f, 0.0f, 0.0f);
    Top();
    // 아랫면
    glColor3f(0.0f, 0.0f, 0.0f);
    Bottom();
    // 우측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Right();
    // 좌측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Left();
    glEnd();
    glPopMatrix();
}

void MARIO_WhiteCube(float xpos, float ypos, float zpos, GLfloat srot) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glRotatef(srot, xrot, yrot, zrot);
    glBegin(GL_QUADS);

    // 앞면
    glColor3f(0.0f, 0.0f, 0.0f);
    Front();

    // 뒷면  보이는 면
    glColor3f(1.0f, 1.0f, 1.0f);
    Back();

    // 윗면
    glColor3f(0.0f, 0.0f, 0.0f);
    Top();

    // 아랫면
    glColor3f(0.0f, 0.0f, 0.0f);
    Bottom();

    // 우측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Right();

    // 좌측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Left();

    glEnd();
    glPopMatrix();
}

void MARIO_RedCube(float xpos, float ypos, float zpos, GLfloat srot) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glRotatef(srot, xrot, yrot, zrot);
    glBegin(GL_QUADS);

    // 앞면
    glColor3f(0.0f, 0.0f, 0.0f);
    Front();

    // 뒷면
    glColor3f(1.0f, 0.0f, 0.0f);
    Back();

    // 윗면
    glColor3f(0.0f, 0.0f, 0.0f);
    Top();

    // 아랫면
    glColor3f(0.0f, 0.0f, 0.0f);
    Bottom();

    // 우측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Right();

    // 좌측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Left();

    glEnd();
    glPopMatrix();
}

void MARIO_OrangeCube(float xpos, float ypos, float zpos, GLfloat srot) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glRotatef(srot, xrot, yrot, zrot);
    glBegin(GL_QUADS);

    // 앞면
    glColor3f(0.0f, 0.0f, 0.0f);
    Front();

    // 뒷면
    glColor3f(1.0f, 0.6f, 0.0f);
    Back();

    // 윗면
    glColor3f(0.0f, 0.0f, 0.0f);
    Top();

    // 아랫면
    glColor3f(0.0f, 0.0f, 0.0f);
    Bottom();

    // 우측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Right();

    // 좌측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Left();

    glEnd();
    glPopMatrix();
}

void MARIO_BrownCube(float xpos, float ypos, float zpos, GLfloat srot) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glRotatef(srot, xrot, yrot, zrot);
    glBegin(GL_QUADS);

    // 앞면
    glColor3f(0.0f, 0.0f, 0.0f);
    Front();

    // 뒷면
    glColor3f(0.5f, 0.2f, 0.04f);
    Back();

    // 윗면
    glColor3f(0.0f, 0.0f, 0.0f);
    Top();

    // 아랫면
    glColor3f(0.0f, 0.0f, 0.0f);
    Bottom();

    // 우측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Right();

    // 좌측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Left();

    glEnd();
    glPopMatrix();
}

void MARIO_SkinCube(float xpos, float ypos, float zpos, GLfloat srot) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glRotatef(srot, xrot, yrot, zrot);
    glBegin(GL_QUADS);

    // 앞면
    glColor3f(0.0f, 0.0f, 0.0f);
    Front();

    // 뒷면
    glColor3f(1.0f, 0.89f, 0.75f);
    Back();

    // 윗면
    glColor3f(0.0f, 0.0f, 0.0f);
    Top();

    // 아랫면
    glColor3f(0.0f, 0.0f, 0.0f);
    Bottom();

    // 우측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Right();

    // 좌측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Left();

    glEnd();
    glPopMatrix();
}

void MARIO_BlueCube(float xpos, float ypos, float zpos, GLfloat srot) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glRotatef(srot, xrot, yrot, zrot);
    glBegin(GL_QUADS);

    // 앞면
    glColor3f(0.0f, 0.0f, 0.0f);
    Front();

    // 뒷면
    glColor3f(0.24f, 0.31f, 0.71f);
    Back();

    // 윗면
    glColor3f(0.0f, 0.0f, 0.0f);
    Top();

    // 아랫면
    glColor3f(0.0f, 0.0f, 0.0f);
    Bottom();

    // 우측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Right();

    // 좌측면
    glColor3f(0.0f, 0.0f, 0.0f);
    Left();

    glEnd();
    glPopMatrix();
}

void Text() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -0.1f, -0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f, -0.1f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1f, 0.1f, 0.1f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, 0.1f, -0.1f);
}

void END_Block(float xPos, float yPos, float zPos)
{
    glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glBegin(GL_QUADS);
    Text();
    glEnd();
    glPopMatrix();
}

void END_Ground(float xPos, float yPos, float zPos)
{
    glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, tex[1]); 
    glBegin(GL_QUADS);
    Text();
    glEnd();
    glPopMatrix();
}

void END_Box(float xpos, float ypos, float zpos) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, tex[2]);
    glBegin(GL_QUADS);
    Text();
    glEnd();
    glPopMatrix();
}

void END_Logo(float xpos, float ypos, float zpos) {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos); // 큐브의 위치
    glScalef(1, 10, 16);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, tex[3]);
    glBegin(GL_QUADS);
    Text();
    glEnd();
    glPopMatrix();
}


bool setting() {
    memset(texRec, 0, sizeof(void*) * 4);

    if ((texRec[0] = LoadBMP("block.bmp")) && 
        (texRec[1] = LoadBMP("ground.bmp")) &&
        (texRec[2] = LoadBMP("box.bmp")) &&
        (texRec[3] = LoadBMP("super_mario_logo.bmp"))) {
        glGenTextures(3, &tex[0]); 
        for (int i = 0; i < 4; i++) { 
            glBindTexture(GL_TEXTURE_2D, tex[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
            glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0,
                GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data); 
        }
    }
    else return FALSE;

    for (int i = 0; i < 4; i++) { 
        if (texRec[i]) {
            if (texRec[i]->data) free(texRec[i]->data);
            free(texRec[i]);
        }
        else return FALSE;
    }

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

AUX_RGBImageRec* LoadBMP(const char* szFilename) {
    FILE* pFile = NULL;
    if (!szFilename) {
        return NULL;
    }
    pFile = fopen(szFilename, "rb");
    if (pFile) {
        fclose(pFile);
        return auxDIBImageLoad(szFilename);     //파일로   부터 메모리로
    }
    return NULL;
}