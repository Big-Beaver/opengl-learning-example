#version 330 core
out vec4 FragColor;

// ���ղ��ʽṹ
struct Material {
	sampler2D  diffuse; // ������
	sampler2D specular; // �������
	float shininess;// �߹�ǿ��
};

// ��Ӱ��ǿ�Ƚṹ
struct Light {
	vec3  position; // �۹�λ��
	vec3  direction;// �۹�ķ���
	float cutOff; // �й��
	float outerCutOff; // ���й��

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	// ���˥������
	float constant; // ������ 1.0
	float linear; // һ����
	float quadratic;// ������
};

uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 viewPos; // ���λ��

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Material material;
uniform Light light;


void main() {

	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// ִ�й��ռ���
	float distance = length(light.position - FragPos); // �����Դ�ľ���
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// ������
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// ������
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// ����߹�
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // �߹���ɫֵ

	ambient *= attenuation;
	diffuse *= intensity;
	specular *= intensity;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0f);
}