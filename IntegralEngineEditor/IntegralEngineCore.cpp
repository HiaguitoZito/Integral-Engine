#include <iostream>
#include <string>
#include <list>
#include <functional>
#include <fstream>
#include "IntegralEngineDST.cpp"
#include "./include/glad/glad.h"
#include "./include/GLFW/glfw3.h"

class Shader {
	unsigned int VertexBuffer;
	unsigned int FragmentBuffer;
public:
	Shader(std::string VertexShaderPath, std::string FragmentShaderPath){
		std::ifstream shader(VertexShaderPath);
		std::string data;
		if(shader.is_open()){
			while(shader){
				std::string line;
				std::getline(shader, line);
				data += line + '\n';
			}
		}
		shader.close();

		const char* VertexSource = data.c_str();

		VertexBuffer = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexBuffer, 1, &VertexSource, NULL);
		glCompileShader(VertexBuffer);
		int  success;
		char infoLog[512];
		glGetShaderiv(VertexBuffer, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(VertexBuffer, 512, NULL, infoLog);
			std::cout << "ERROR::COMPILE::SHADER\n" << infoLog << std::endl;
		}

		// Fragment Shader Compiler.
		std::ifstream shader2(FragmentShaderPath);
		std::string data2;
		if(shader2.is_open()){
			while(shader2){
				std::string line;
				std::getline(shader2, line);
				data2 += line + '\n';
			}
		}
		shader2.close();
		const char* FragSource = data2.c_str();

		FragmentBuffer = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentBuffer, 1, &FragSource, NULL);
		glCompileShader(FragmentBuffer);
		int  success2;
		char infoLog2[512];
		glGetShaderiv(VertexBuffer, GL_COMPILE_STATUS, &success2);
		if(!success2){
			glGetShaderInfoLog(VertexBuffer, 512, NULL, infoLog2);
			std::cout << "ERROR::COMPILE::SHADER\n" << infoLog2 << std::endl;
		}
	}
	int AttachShader(unsigned int program){
		glAttachShader(program, VertexBuffer);
		glAttachShader(program, FragmentBuffer);
	}
	~Shader(){
		glDeleteShader(VertexBuffer);
		glDeleteShader(FragmentBuffer);
	}
};

class Mesh {
public:
	float* vertices;
	size_t vSize;
	GLuint* indices;
	size_t uSize;

	Mesh(float* vertices, size_t vSize, GLuint* indices, size_t uSize){
		this->vertices = vertices;
		this->vSize    = vSize;
		this->indices  = indices;
		this->uSize    = uSize;
	}

	~Mesh(){
		delete vertices;
	}
};

class Component {
public:
	std::string type;
};

class Transform {
public:
	Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(0.0f, 0.0f, 0.0f);
	Quaternion rotation = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

	Transform() {}

	Transform(Vector3 position, Vector3 scale, Quaternion rotation) {
		
	}
};

class Object {
public:
	Transform* transform;
};

class MonoBehaviour : public Component {
private:
	virtual void Start() {};
	virtual void Update() {};
public:
	Object* gameObject;
	MonoBehaviour() {
		type = typeid(this).name();
	}
	void callUpdate();
	void callStart();
};

class GameObject : public Object {
	
public:
	std::list<MonoBehaviour*> components;
	int index;
	GameObject() {
		components = std::list<MonoBehaviour*>();
		transform = new Transform();
	}
	GameObject(Vector3 position, Vector3 scale, Quaternion rotation) {
		components = std::list<MonoBehaviour*>();
		transform = new Transform(position, scale, rotation);
	}

	~GameObject() {
		std::cout << "Deleted Components: " << components.size() << std::endl;
		while (!components.empty()) {
			MonoBehaviour* c = components.front();
			components.pop_front();
			delete (MonoBehaviour*)c;
		}
	}

	template <typename T>
	T* GetComponent() {
		for (MonoBehaviour* m : components) {
			if (m->type.compare(typeid(T*).name())) return (T*)m;
		}
		return nullptr;
	}

	template <typename T>
	T* AddComponent()
	{
		MonoBehaviour* temp = new T();
		temp->gameObject = this;
		components.push_back(temp);
		temp->callStart();
		return (T*)temp;
	}
	template <typename T>
	void AddComponent(T* component)
	{
		MonoBehaviour* m = ((MonoBehaviour*)component);
		m->gameObject = this;
		components.push_back(m);
		m->callStart();
	}
};
void MonoBehaviour::callUpdate() {
	Update();
}
void MonoBehaviour::callStart() {
	Start();
}