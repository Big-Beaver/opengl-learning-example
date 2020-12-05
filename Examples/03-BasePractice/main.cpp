#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// ������ɫ��С���� ��ӦOpenGL�汾 3.3
const char *vertexShaderSuorce =
"#version 330 core\n"					// ��Ӧʹ�ú��İ汾
"layout (location = 0) in vec3 aPos;\n" // �������붥������
"void main()\n"
"{\n"
" vec4 v4Pos = vec4(aPos.xy, 0.0, 1.0);\n"
" gl_Position = v4Pos;\n" // ���ñ��� gl_Position
"}";

// ƬԪ��ɫ��С���� ��Ӧ�汾3.3 ����ģʽ
const char *fragementShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n" // ������� �����������ɫ
"void main()\n"
"{"
"	FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}";

const char *fragementShaderSource2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{"
" 	//FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
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
	float vertices1[] = {
		// ��һ��������
		0.5f,
		0.75f,
		0.0f,
		0.25f,
		0.25f,
		0.0f,
		0.75f,
		0.25f,
		0.0f,
	};

	float vertices2[] = {
		// �ڶ���������
		-0.5f,
		-0.25f,
		0.0f,
		-0.75f,
		-0.75f,
		0.0f,
		-0.25f,
		-0.75f,
		0.0f,
	};

	// ����VBO����
	unsigned int VBO1, VBO2;
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &VBO2);

	// ���������������
	unsigned int VAO1, VAO2;
	glGenVertexArrays(1, &VAO1);
	glGenVertexArrays(1, &VAO2);
	// ��VAO
	glBindVertexArray(VAO1);
	// �󶨻��嵽Ŀ�껺��
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// ���ö�������
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO2);
	// �󶨻��嵽Ŀ�껺��
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	// �������ݵ�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// ���ö�������
	glEnableVertexAttribArray(0);

	// ������ɫ��
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int fragementShader2;

	// ������ɫ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragementShader2 = glCreateShader(GL_FRAGMENT_SHADER);

	// ���Ӷ�����ɫ��Դ�뵽��ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSuorce, NULL);
	glCompileShader(vertexShader);

	// ����ƬԪ��ɫ��Դ�뵽��ɫ������
	glShaderSource(fragmentShader, 1, &fragementShaderSource, NULL);
	// ������ɫ����
	glCompileShader(fragmentShader);

	glShaderSource(fragementShader2, 1, &fragementShaderSource2, NULL);
	glCompileShader(fragementShader2);

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

	glGetShaderiv(fragementShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragementShader2, 512, NULL, infoLog);
		std::cout << "ƬԪ��ɫ��2 ����ʧ�ܣ�" << infoLog << std::endl;
	}

	// 2 ��ɫ���������
	unsigned int shaderProgram, shaderProgram2;
	shaderProgram = glCreateProgram();
	shaderProgram2 = glCreateProgram();

	// ���������ɫ�����ӵ����������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragementShader2);

	// ������ɫ��
	glLinkProgram(shaderProgram);
	glLinkProgram(shaderProgram2);

	glUseProgram(shaderProgram);

	// ��ѯ���Ե�λ��
	int aPos = glGetAttribLocation(shaderProgram, "aPos");
	std::cout << "aPos �� location �ǣ�" << aPos << std::endl;

	// ��������Ƿ�ʧ��
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "��ɫ�������������ʧ�ܣ�" << infoLog << std::endl;
	}

	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout << "��ɫ���������2 ����ʧ�ܣ�" << infoLog << std::endl;
	}

	// 3 ʹ����ɫ������
	// glUseProgram(shaderProgram);

	// 4 ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragementShader2);

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

	// ��ȡ����֧�ֵĶ������Ե�����
	int numAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);

	std::cout << "����֧�ֵĶ������Ե���������ǣ� " << numAttributes << std::endl;

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{

		// ����Ƿ���Ҫ�˳�����
		processInput(window);

		// ��Ⱦָ��

		// ���������ɫ -- ״̬����
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//��ʼ�����Ļ����ʹ���������ɫ -- ״̬ʹ��
		glClear(GL_COLOR_BUFFER_BIT);

		// ��������
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, (sizeof(vertices1) / sizeof(vertices1[0])) / 3);

		//glUseProgram(shaderProgram2);
		//glBindVertexArray(VAO2);
		//glDrawArrays(GL_TRIANGLES, 0, (sizeof(vertices2) / sizeof(vertices2[0])) / 3);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &VBO2);
	glDeleteVertexArrays(1, &VAO1);
	glDeleteVertexArrays(1, &VAO2);

	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram2);

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