#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Texture.h"


HDC hDc = NULL;
HGLRC hRc = NULL;
HWND hWnd = NULL;

float angle = 0.0;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;

float deltaAngleI = 0.05f;
float deltaMoveI = 2.5f;

bool onGround = true;
float gravity = 0.2f;
float gravityDefault = 0.2f;
float gravityI = 0.02f;


float yyy = 2.0f;

int windowWidth = 800;
int windowHeight = 600;



Texture* texture = NULL;
Texture* textureWall = NULL;
Texture* textureRoof = NULL;
Texture* textureLamp = NULL;

Texture* textureDoor = NULL;

//Texture* fontTexture = NULL;
//
//GLuint fontBase;
//
//const int fontSize = 13;
//const int fontSpace = 7;

LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);


//void font()
//{
//    
// 
//    fontTexture = new Texture("C:/Users/user/Desktop/font.tga", "fontTexture");
//    fontBase = glGenLists(256);
//    glBindTexture(GL_TEXTURE_2D, fontTexture->texID);
// 
// 
//
//    for (int i = 0; i < 256; i++)
//    {
//        float cx = (float)(i % 16) / 16.0f;
//        float cy = (float)(i / 16) / 16.0f;
//
//        glNewList(fontBase + i, GL_COMPILE);
//
//        glBegin(GL_QUADS);
//        glTexCoord2f(cx,          1 - cy - 0.0625f); glVertex2f(0, fontSize);
//        glTexCoord2f(cx + 0.0625f, 1 - cy - 0.0625f); glVertex2f(fontSize, fontSize);
//        glTexCoord2f(cx + 0.0625f, 1 - cy);          glVertex2f(fontSize, 0);
//        glTexCoord2f(cx,          1 - cy);          glVertex2f(0, 0);
//        glEnd();
//
//        glTranslated(fontSpace, 0, 0);
//
//        glEndList();
//
//    }
//
//  
//
//
//}
//GLvoid setPers(GLsizei width, GLsizei height)
//{
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0f, width / height, 0.1f, 100.0f);
//    glMatrixMode(GL_MODELVIEW);
//
//}
//GLvoid setOrtho(GLsizei width, GLsizei height)
//{
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, width, width, 0, 0.1f, 100.0f);
//
//
//}

//void drawText(const char* in_text)
//{
//    char text[256];
//    va_list ap;
//
//    va_start(ap, in_text);
//        vsprintf_s(text, in_text, ap);
//
//    va_end(ap);
//
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//    glBindTexture(GL_TEXTURE_2D, fontTexture->texID);
//    glMatrixMode(GL_MODELVIEW);
//
//    glPushMatrix();
//    glLoadIdentity();
//
//    glTranslated(15, 15, 0);
//    glListBase(fontBase - 32);
//    glCallLists((GLsizei)strlen(text), GL_BYTE, text);
//
//
//    glMatrixMode(GL_MODELVIEW);
//    glPopMatrix();
//
//}

GLvoid initGL()
{
 

    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

    glEnable(GL_DEPTH_TEST);


    texture = new Texture("C:/Users/user/Desktop/tiletga.tga", "Surface Texture");
    textureWall = new Texture("C:/Users/user/Desktop/wall_rock.tga", "textureWall");
    //textureWall = new Texture("C:/Users/user/Desktop/wall.tga", "textureWall");
    textureRoof = new Texture("C:/Users/user/Desktop/roof.tga", "textureRoof");
    textureLamp = new Texture("C:/Users/user/Desktop/lamp.tga", "textureLamp");
   
    textureDoor = new Texture("C:/Users/user/Desktop/door.tga", "textureDoor");
    


    glClearColor(0.0, 0.0, 0.0, 1.0);
    if (windowHeight == 0)
        windowHeight = 1;
    float ratio = windowWidth * 1.0 / windowHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, windowWidth, windowHeight);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

  
}



void initLighting()
{

    // Enable lighting
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    // Set lighting intensity and color
    float ambientLight0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);

    // определяет цвет света источника
    float diffuseLight0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);

    // определяет отраженный свет
    float specularLight0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);

    float position0[4] = { 0.0f, 9.98f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position0);

    /*float dir[3] = { -1, 1, -1 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);*/

    ////////////////////////////////////////////////
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);// set cutoff angle
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1); // set focusing strength

  /*  GLfloat shinnes[] = { 1 };

    GLfloat matdiffu[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matspec[] = { 1.0f, 1.f, 1.f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matdiffu);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinnes);*/

}

void onResize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove)
{
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;

}

void computeDir(float deltaAngle)
{

    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

GLvoid Timer(GLvoid)
{

    if (deltaMove)
        computePos(deltaMove);
    if (deltaAngle)
        computeDir(deltaAngle);

    if (!onGround)
    {
        yyy += gravity;
        gravity -= gravityI;
    }

    if (yyy < 2.0f) {
        yyy = 2.0f;
        gravity = gravityDefault;
        onGround = true;
    }

    if (z < -18.0f) {
        z = -18.0f;
    }
    if (z > 18.0f) {
        z = 18.0f;
    }
    if (x < -18.0f) {
        x = -18.0f;
    }
    if (x > 18.0f) {
        x = 18.0f;
    }



}

void displayFPS()
{
    static long lastTime = GetTickCount();
    static long loops = 0;
    static GLfloat fps = 0.0f;

    long newTime = GetTickCount();

    if (newTime - lastTime > 100)
    {
        float newFPS = (float) loops / (float) (newTime - lastTime) * 1000.0f;
        fps = (fps + newFPS) / 2.0f;


        wchar_t title[100];

        swprintf(title, 100, L"OpenGL FPS: %.2f", fps);

        SetWindowText(hWnd, title);

        lastTime = newTime;

        loops = 0;
    }

    loops++;
}

void drawLevel() //DRAW------------------------------------------------------------------------DRAW
{

    glEnable(GL_TEXTURE_2D);


    // DOOR-----------------------------------------DOOR
    glBindTexture(GL_TEXTURE_2D, textureDoor->texID);
    glColor3f(1.0f, 1.0f, 1.0f);

  
    glPushMatrix();
   
   

    glRotatef(-20, 0, 1, 0);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0);glVertex3f(-1.0f, 0.0f, -19.99f);
    glTexCoord2f(0.0, 1.0);glVertex3f(-1.0f, 3.0f, -19.99f);

    glTexCoord2f(1.0, 1.0);glVertex3f(1.0f, 3.0f, -19.99f);
    glTexCoord2f(1.0, 0.0);glVertex3f(1.0f, 0.0f, -19.99f);

    glEnd();
    glPopMatrix();



    // GROUND-----------------------------------------GROUND
    glBindTexture(GL_TEXTURE_2D, texture->texID);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);glVertex3f(20.0f, 0.0f, 20.0f);
        glTexCoord2f(0.0, 20.0);glVertex3f(-20.0f, 0.0f, 20.0f);
        glTexCoord2f(20.0, 20.0);glVertex3f(-20.0f, 0.0f, -20.0f);
        glTexCoord2f(20.0, 0.0);glVertex3f(20.0f, 0.0f, -20.0f);

    glEnd();

    // WALL-----------------------------------------WALL
    glBindTexture(GL_TEXTURE_2D, textureWall->texID);


    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    //UP
    glTexCoord2f(0.0, 0.0);glVertex3f(-20.0f, 0.0f, -20.0f);
    glTexCoord2f(0.0, 10.0);glVertex3f(-20.0f, 10.0f, -20.0f);
    glTexCoord2f(20.0, 10.0);glVertex3f(20.0f, 10.0f, -20.0f);
    glTexCoord2f(20.0, 0.0);glVertex3f(20.0f, 0.0f, -20.0f);

    //DOWN
    glTexCoord2f(0.0, 0.0);glVertex3f(20.0f, 0.0f, 20.0f);
    glTexCoord2f(0.0, 10.0); glVertex3f(20.0f, 10.0f, 20.0f);
    glTexCoord2f(20.0, 10.0);glVertex3f(-20.0f, 10.0f, 20.0f);
    glTexCoord2f(20.0, 0.0);glVertex3f(-20.0f, 0.0f, 20.0f);

    //LEFT
    glTexCoord2f(0.0, 0.0);glVertex3f(-20.0f, 0.0f, 20.0f);
    glTexCoord2f(0.0, 10.0);glVertex3f(-20.0f, 10.0f, 20.0f);
    glTexCoord2f(20.0, 10.0);glVertex3f(-20.0f, 10.0f, -20.0f);
    glTexCoord2f(20.0, 0.0);glVertex3f(-20.0f, 0.0f, -20.0f);

    //RIGHT
    glTexCoord2f(0.0, 0.0);glVertex3f(20.0f, 0.0f, 20.0f);
    glTexCoord2f(0.0, 10.0);glVertex3f(20.0f, 10.0f, 20.0f);
    glTexCoord2f(20.0, 10.0);glVertex3f(20.0f, 10.0f, -20.0f);
    glTexCoord2f(20.0, 0.0);glVertex3f(20.0f, 0.0f, -20.0f);

    glEnd();


    // ROOF-----------------------------------------ROOF

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glBindTexture(GL_TEXTURE_2D, textureRoof->texID);


    glColor3f(1.0f, 1.0f, 1.0f);


    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(20.0f, 10.0f, 20.0f);
        glTexCoord2f(0.0, 20.0);glVertex3f(-20.0f, 10.0f, 20.0f);
        glTexCoord2f(20.0, 20.0);glVertex3f(-20.0f, 10.0f, -20.0f);
        glTexCoord2f(20.0, 0.0);glVertex3f(20.0f, 10.0f, -20.0f);
    glEnd();

    // LAMP-----------------------------------------LAMP

    glBindTexture(GL_TEXTURE_2D, textureLamp->texID);
    glColor3f(1.0f, 1.0f, 1.0f);


    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);glVertex3f(-3.0f, 9.99f, 1.0f);
        glTexCoord2f(0.0, 1.0);glVertex3f(-3.0f, 9.99f, -1.0f);
        glTexCoord2f(1.0, 1.0);glVertex3f(3.0f, 9.99f, -1.0f);
        glTexCoord2f(1.0, 0.0);glVertex3f(3.0f, 9.99f, 1.0f);
    glEnd();
  

    glDisable(GL_TEXTURE_2D);

}

GLvoid Draw(GLvoid) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

   

    gluLookAt(x, yyy, z,
        x + lx, yyy, z + lz,
        0.0f, 1.0f, 0.0f);


    drawLevel();

    Timer();

    

    SwapBuffers(hDc);

   
    
}



int killWindow(HINSTANCE hInstance)
{

    if (hRc)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hRc);

        hRc = NULL;

    }
    UnregisterClass(L"OpenGLTest", hInstance);
    return TRUE;
}
HINSTANCE m_hInstance;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{

    m_hInstance = hInstance;

    GLuint PixelFormat;
    WNDCLASS wndClass;

    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndClass.lpfnWndProc = (WNDPROC)WindowProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = NULL;
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = L"OpenGLTest";

    if (!RegisterClass(&wndClass))
    {
        DWORD dwError = GetLastError();
        if (dwError != ERROR_CLASS_ALREADY_EXISTS)
            return HRESULT_FROM_WIN32(dwError);
    }


    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
        L"OpenGLTest",    // name of the window class
        L"OpenGL",   // title of the window
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,    // window style
        0,    // x-position of the window
        0,    // y-position of the window
        windowWidth,    // width of the window
        windowHeight,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        m_hInstance,    // application handle
        NULL);    // used with multiple windows, NULL

    if (hWnd == NULL)
    {
        DWORD dwError = GetLastError();
        return HRESULT_FROM_WIN32(dwError);
    }

    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        16,
        0,0,0,0,0,0,
        0,
        0,
        0,
        0,0,0,0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };

    hDc = GetDC(hWnd);
    PixelFormat = ChoosePixelFormat(
        hDc,
        &pfd);

    SetPixelFormat(hDc, PixelFormat, &pfd);

    hRc = wglCreateContext(hDc);
    wglMakeCurrent(hDc, hRc);

    ShowWindow(hWnd, SW_SHOW);

    SetForegroundWindow(hWnd);
    SetFocus(hWnd);

    //-------



    initGL();
    initLighting();

   


    bool bGotMsg;
    MSG  msg;
    msg.message = WM_NULL;
    PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

    while (WM_QUIT != msg.message)
    {

        bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);

        if (bGotMsg)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Draw();
        }
    }


    killWindow(m_hInstance);

    return (int)(msg.wParam);

}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

        case WM_CLOSE:
        {
            HMENU hMenu;
            hMenu = GetMenu(hWnd);
            if (hMenu != NULL)
            {
                DestroyMenu(hMenu);
            }
            DestroyWindow(hWnd);
            UnregisterClass(L"OpenGLTest", m_hInstance);

            return 0;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
  

        case WM_SIZE:
        {
      
            onResize(LOWORD(lParam), HIWORD(lParam));

            break;
        }

        case WM_KEYDOWN:
        {
            if (wParam == 65)
            {
                deltaAngle = -deltaAngleI;
            }
            if (wParam == 68)
            {
                deltaAngle = deltaAngleI;
            }
            if (wParam == 87)
            {

                deltaMove = deltaMoveI;
            }
            if (wParam == 83)
            {
                deltaMove = -deltaMoveI;
            }

            if (wParam == 32)
            {
                onGround = false;
            }

            break;
        }

    

        case WM_KEYUP:
        {

            if (wParam == 65 || wParam == 68)
            {
                deltaAngle = 0.0f;
            }
            if (wParam == 83 || wParam == 87)
            {
                deltaMove = 0;
            }

            break;
        }
       
  

   
    }


    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
