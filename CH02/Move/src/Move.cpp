//
//	Move.cpp
//	OpenGL Tutorial Sample Code
//
//	Created by Ge Jian Feng on 2014-10-25
//	Copyright (c) 2014 Ge Jian Feng. All rights reserved.
//

#include <GLTools.h>
#include <GLShaderManager.h>

#ifdef OS_MAC
#include <GLUT/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch             squareBatch;
GLShaderManager     shaderManager;

GLfloat             blockSize = 0.1f;
GLfloat             vVerts[] = { -blockSize, -blockSize, 0.0f,
                                  blockSize, -blockSize, 0.0f,
                                  blockSize,  blockSize, 0.0f,
                                 -blockSize,  blockSize, 0.0f };

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

void SpecialKey(int key, int x, int y)
{
    GLfloat stepSize = 0.025f;
    
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[7];
    
    if (key == GLUT_KEY_UP) {
        blockY = blockY + stepSize;
    }
    
    if (key == GLUT_KEY_DOWN) {
        blockY = blockY - stepSize;
    }
    
    if (key == GLUT_KEY_LEFT) {
        blockX = blockX - stepSize;
    }
    
    if (key == GLUT_KEY_RIGHT) {
        blockX = blockX + stepSize;
    }
    
    if (blockX < -1.0f) {
        blockX = -1.0f;
    }
    
    if (blockX > 1.0f - blockSize * 2) {
        blockX = 1.0f - blockSize * 2;
    }
    
    if (blockY > 1.0f) {
        blockY = 1.0f;
    }
    
    if (blockY <= -1.0f + blockSize * 2) {
        blockY = -1.0f + blockSize * 2;
    }
    
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;
    
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;
    
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;
    
    squareBatch.CopyVertexData3f(vVerts);
    
    glutPostRedisplay();
}

void ChangeSize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    squareBatch.Draw();
    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Move");
    
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKey);
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));
        return 0;
    }
    
    SetupRC();
    glutMainLoop();
    
    return 0;
}