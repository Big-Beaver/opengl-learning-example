#version 330 core
out vec4 FragColor;

// ���Դ
struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// ���ղ��ʽṹ
struct Material {
	sampler2D  diffuse; // ������
	sampler2D specular; // �������
	float shininess;// �߹�ǿ��
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos; // ���λ��
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform PointLight pointLight;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
	vec3 outputColor;

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	outputColor += CalcPointLight(pointLight, norm, FragPos, viewDir);
    FragColor = vec4(outputColor, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	float distance = length(light.position - fragPos); // �����Դ�ľ���
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// ������
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));

	// ������
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));

	// ����߹�
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),32.0f);
	vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords)); // �߹���ɫֵ

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}