#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <common/shader.h>
#include <common/camera.h>

#define STB_IMAGE_IMPLEMENTATION
#include <common/stb_image.h>
#include <common/gui.h>

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
	const char* glsl_version = "#version 330";
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

	// ����imgui������
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImVec4 light_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// ����Ƿ���Ҫ�˳�����
		processInput(window);


		// ���������ɫ -- ״̬����
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//��ʼ�����Ļ����ʹ���������ɫ -- ״̬ʹ��
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ��������
		ourShader.use();

		// ���ù���
		glm::vec3 lightColor = glm::vec3(light_color.x, light_color.y, light_color.z);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
		ourShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
		ourShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f); // �����յ�����һЩ�Դ��䳡��
		ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		// ���ò���
		ourShader.setVec3("material.ambient", 0.19225, 0.19225, 0.19225);
		ourShader.setVec3("material.diffuse", 0.50754, 0.50754, 0.50754);
		ourShader.setVec3("material.specular", 0.508273, 0.508273, 0.508273);
		ourShader.setFloat("material.shininess", 0.4 * 128);

		// λ��
		ourShader.setVec3("viewPos", camera.Position);
		ourShader.setVec3("light.position", lightPos);

		lightPos.x = (float)sin(glfwGetTime());

		ImGui::Begin("view value");
		ImGui::SliderFloat("lightPos.x", &lightPos.x, -1.0f, 1.0f);
		ImGui::SliderFloat("lightColor.x", &lightColor.x, -1.0f, 1.0f);
		ImGui::SliderFloat("lightColor.y", &lightColor.y, -1.0f, 1.0f);
		ImGui::SliderFloat("lightColor.z", &lightColor.z, -1.0f, 1.0f);

		ImGui::ColorEdit3("lightColor", (float*)&light_color);
		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		// ͶӰ����
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.01f, 100.0f);
		ourShader.setMat4("projection", projection);

		// ��ͼ����
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		// ģ�;���
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -0.8f));
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

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


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