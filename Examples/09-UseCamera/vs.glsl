#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;// ģ�;��� ���� ������ת������������ϵ
uniform mat4 view; // ��ͼ���� ���� ����������ת�����۲�ռ�
uniform mat4 projection; // ͶӰ���� ���� ����������ͶӰ���ü�����

out vec2 TexCoord;

void main()
{
    gl_Position = projection * view *  model * vec4(aPos, 1.0) ;
    TexCoord = aTexCoord;
}