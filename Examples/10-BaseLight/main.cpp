#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <common/shader.h>
#include <common/camera.h>

#define STB_IMAGE_IMPLEMENTATION
#include <common/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


const unsigned int  SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;


float deltaTime = 0.0f; // ��ǰ֡����һ֮֡���ʱ���
float lastTime = 0.0f; // ��һ֡��ʱ��

float lastX = 400; // �����һ֡��λ��
float lastY = 300;


bool firstMouse = true;


// �����������
Camera camera(glm::vec3(0.0f, 0.0f, 1.0f));


glm::vec3 lightPos(0.5f, 0.5f, -1.5f);

int main()
{

	// ��ʼ��GLFW
	glfwInit();

	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����GLFW���ڶ���
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);

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
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// ע�ⴰ�ڼ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		

	// �����������ɫ��
	Shader ourShader("vs.glsl", "fs.glsl");
		
	// ���ƹ�Դ����ɫ��
	Shader lampShader("lightCube_vs.glsl", "lightCube_fs.glsl");

	// ��������
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};	// ����


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// ����λ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// 5 ������������
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	// ��ԴVAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);


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
	unsigned char *data = stbi_load("../../assert/texture/container.jpg", &width, &height, &nChannels, 0);
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
	data = stbi_load("../../assert/texture/awesomeface.png", &width, &height, &nChannels, 0);
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

	/*ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture1"), 0);
	ourShader.setInt("ourTexture2", 1);*/

	glEnable(GL_DEPTH_TEST);
	

	// ���û���ģʽ
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// ����Ƿ���Ҫ�˳�����
		processInput(window);


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//��ʼ�����Ļ����ʹ���������ɫ -- ״̬ʹ��
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ��������
		ourShader.use();

		// �������屾����ɫ
		ourShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		ourShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		// ���ݹ�Դλ��
		ourShader.setVec3("lightPos", lightPos);
		ourShader.setVec3("viewPos", camera.Position);
		

		// ͶӰ����
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.01f, 100.0f);
		ourShader.setMat4("projection", projection);

		// ��ͼ����
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);
		
		// ģ�;���
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f,-0.5f, -0.8f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// ���ƹ�Դ������
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.05f));
		lampShader.setMat4("model", model);


		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// ������ɫ������
		glfwSwapBuffers(window);

		// ����Ƿ��������¼�
		glfwPollEvents();
	}

	// ɾ�������Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// ɾ��/�ͷ���Դ
	glfwTerminate();
	return 0;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// ���ڴ�С�任����
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// �������
void processInput(GLFWwindow *window)

{
	float cameraSpeed = deltaTime * 2.5f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

}