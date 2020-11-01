#include <GL/glad.h>
#include <GL/glfw3.h>
#include "Shader.h"

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{

	// ��ʼ��GLFW
	glfwInit();

	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����GLFW���ڶ���
	GLFWwindow *window = glfwCreateWindow(800, 600, "demo01", NULL, NULL);

	if (window == NULL)
	{
		cout << "��ʼ��glfw����ʧ��!" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "��ʼ��GLADʧ��!" << endl;
		return -1;
	}

	// �����ӿ�
	glViewport(0, 0, 800, 600);

	// ע�ⴰ�ڼ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��������
	float vertices[] = {
		// ����λ��xyz		��ɫ rgba
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // ����
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	// ����
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f };	// ����

													// ����VBO����
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// ���������������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ��VAO
	glBindVertexArray(VAO);
	// �󶨻��嵽Ŀ�껺��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����λ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// ������ɫ
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader ourShader("vs.glsl", "fs.glsl");

	// 5 ������������
	// ����1 location
	// ����2 �������ԵĴ�С
	// ����3 ��������
	// ����4 �Ƿ����ݱ�׼��
	// ����5 ����
	// ����6 ��ʼλ�õ�ƫ����
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// // ���ö�������
	// glEnableVertexAttribArray(0);

	// ��buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ʹ���ֿ�����ģʽ
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{

		// ����Ƿ���Ҫ�˳�����
		processInput(window);

		// ��Ⱦָ��

		// ���������ɫ -- ״̬����
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

		//��ʼ�����Ļ����ʹ���������ɫ -- ״̬ʹ��
		glClear(GL_COLOR_BUFFER_BIT);

		// ��������
		// glUseProgram(shaderProgram);
		ourShader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// ����1 ͼԪ����
		// ����2 �����������ʼ����
		// ����3 ���ƵĶ������
		// glDrawArrays(GL_LINE_LOOP, 0, 3);

		// ������ɫ������
		glfwSwapBuffers(window);

		// ����Ƿ��������¼�
		glfwPollEvents();
	}

	// ɾ�������Դ
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	// ɾ��/�ͷ���Դ
	glfwTerminate();
	return 0;
}

// ���ڴ�С�任����
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// �������
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}