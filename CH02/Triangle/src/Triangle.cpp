//
//	Triangle.cpp
//	OpenGL Tutorial Sample Code
//
//	Created by Ge Jian Feng on 2014-10-25
//	Copyright (c) 2014 Ge Jian Feng. All rights reserved.
//

#include <GLTools.h>
#include <GLShaderManager.h>

#ifdef OS_APPLE
#include <GLUT/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch					triangleBatch;
GLShaderManager			shaderManager;

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
						  0.5f, 0.0f, 0.0f,
						  0.0f, 0.5f, 0.0f };

	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	triangleBatch.Draw();
	glutSwapBuffers();
}

void ChangeSize(int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Triangle");

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();
	glutMainLoop();

	return 0;
}