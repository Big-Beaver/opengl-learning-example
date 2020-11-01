#include <GL/glad.h>
#include <GL/glfw3.h>
#include <iostream>

#include <Shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

float factor = 0.2f;

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

	Shader ourShader("vs.glsl", "fs.glsl");

	// ��������
	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f  // top left 
	};	// ����

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// ����λ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// ������ɫ
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);



	// 5 ������������
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ��ȡ�������������
	unsigned int texture1, texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// ���������ƺ͹��˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// ���ز���������
	int width, height, nChannels;

	// ͼ��Y�ᷭת
	stbi_set_flip_vertically_on_load(true);
	//unsigned char *data = stbi_load("C:/Users/ithan/Desktop/container.jpg", &width, &height, &nChannels, 0);
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "��ȡ����ͼƬʧ��!" << endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// ���������ƺ͹��˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//unsigned char *data = stbi_load("C:/Users/ithan/Desktop/container.jpg", &width, &height, &nChannels, 0);
	data = stbi_load("awesomeface.png", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "��ȡ����ͼƬʧ��!" << endl;
	}
	stbi_image_free(data);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture1"), 0);
	ourShader.setInt("ourTexture2", 1);


	// ƽ��
	//trans = glm::translate(trans, glm::vec3(-0.5f, 0.0f, 0.0f));

	// ����
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));

	// ��ת
	// ��ȡuniform������ַ
	unsigned int transformLocation = glGetUniformLocation(ourShader.ID, "transform");
	
	// ���ݵ���ɫ��
	
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

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ��������
		ourShader.use();
		ourShader.setFloat("factor", factor);
		glm::mat4 trans = glm::mat4(1.0f);

		// ƽ��
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.0f, 0.0f));

		// ��ת
		trans = glm::rotate(trans, (float)glm::cos(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

		// ����
		trans = glm::scale(trans, glm::vec3(glm::sin(glfwGetTime()), glm::sin(glfwGetTime()), 0.5f));

		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &trans[0][0]);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		trans = glm::mat4(1.0f);

		// ƽ��
		trans = glm::translate(trans, glm::vec3(0.5f, 0.0f, 0.0f));

		// ����
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		factor += 0.001f;
		cout << factor << endl;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		factor -= 0.001f;
		cout << factor << endl;
	}
}