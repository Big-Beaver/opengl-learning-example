#include <GL/glad.h>
#include <GL/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// ������ɫ��С���� ��ӦOpenGL�汾 3.3
const char *vertexShaderSuorce =
"#version 330 core\n"					// ��Ӧʹ�ú��İ汾
"layout (location = 0) in vec3 aPos;\n" // �������붥������
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // ���ñ��� gl_Position
"}";

// ƬԪ��ɫ��С���� ��Ӧ�汾3.3 ����ģʽ
const char *fragementShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n" // ������� �����������ɫ
"void main()\n"
"{"
"	FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}";

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
		std::cout << "��ʼ��glfw����ʧ��!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "��ʼ��GLADʧ��!" << std::endl;
		return -1;
	}

	// �����ӿ�
	glViewport(0, 0, 800, 600);

	// ע�ⴰ�ڼ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��������
	float vertices[] = {
		0.5f, 0.5f, 0.0f,	// ���Ͻ�
		0.5f, -0.5f, 0.0f,	// ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f	// ���Ͻ�
	};

	// ��������
	unsigned int indeces[] = {
		0, 1, 3, // ��һ��������
		1, 2, 3	 // �ڶ���������
	};

	// �����������
	unsigned int EBO;
	glGenBuffers(1, &EBO);

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
	// �������ݵ�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// ������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	// ������ɫ��
	unsigned int vertexShader;
	unsigned int fragmentShader;

	// ������ɫ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���Ӷ�����ɫ��Դ�뵽��ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSuorce, NULL);
	// ����ƬԪ��ɫ��Դ�뵽��ɫ������
	glShaderSource(fragmentShader, 1, &fragementShaderSource, NULL);

	// ������ɫ����
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// ����Ƿ�ɹ�
	int success;	   // ����Ƿ�ɹ�
	char infoLog[512]; // �洢������Ϣ
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	// �������ʧ�ܴ�ӡ������Ϣ
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "������ɫ������ʧ�ܣ�" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ƬԪ��ɫ������ʧ�ܣ�" << infoLog << std::endl;
	}

	// 2 ��ɫ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// ���������ɫ�����ӵ����������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// ������ɫ��
	glLinkProgram(shaderProgram);

	// ��������Ƿ�ʧ��
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "��ɫ�������������ʧ�ܣ�" << infoLog << std::endl;
	}

	// 3 ʹ����ɫ������
	glUseProgram(shaderProgram);

	// 4 ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteProgram(fragmentShader);

	// 5 ������������
	// ����1 location
	// ����2 �������ԵĴ�С
	// ����3 ��������
	// ����4 �Ƿ����ݱ�׼��
	// ����5 ����
	// ����6 ��ʼλ�õ�ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// ���ö�������
	glEnableVertexAttribArray(0);

	// ��buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ʹ���ֿ�����ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
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
	// else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	// {
	// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// }
	// else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	// {
	// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// }
}