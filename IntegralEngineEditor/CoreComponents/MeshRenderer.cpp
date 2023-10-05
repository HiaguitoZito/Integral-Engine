#include "./../IntegralEngineCore.cpp"

class MeshRenderer : public MonoBehaviour {
	unsigned int program;
	unsigned int VBO, VAO, EBO;
	int PositionLocation;
	Shader* shader = nullptr;
	Mesh* mesh = nullptr;
	float vertices[12] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	}; 

	void Start() {
		if(mesh == nullptr) mesh = new Mesh(vertices, sizeof(vertices), indices, sizeof(indices));

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh->vSize, mesh->vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->uSize, mesh->indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		std::cout << "VertexArray Bound!" << std::endl;
		std::cout << "VAO: " << VAO << std::endl;
		std::cout << "vs: " << mesh->vSize / sizeof(float) << std::endl;
		std::cout << "is: " << mesh->uSize / sizeof(unsigned int) << std::endl;
	}
	void Update() {
		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, mesh->uSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUniform3f(PositionLocation, gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z);
	}
public:
	~MeshRenderer(){
		std::cout << "MeshRenderer Deleted!" << std::endl;
		delete mesh;
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(program);
	}
	void SetMesh(float* vertices, int vSize, GLuint* indices, int uSize){
		delete mesh;
		mesh = new Mesh(vertices, vSize, indices, uSize);
		Start();
	}
	void SetShaders(Shader* shader){
		// glDeleteProgram(program);
		program = glCreateProgram(); std::cout << "Program Created!" << std::endl;
		shader->AttachShader(program); std::cout << "Shader Attached!" << std::endl;
		this->shader = shader; std::cout << "this->shader = shader;" << std::endl;
		glLinkProgram(program); std::cout << "Shader Linked!" << std::endl;

		PositionLocation = glGetUniformLocation(program, "position");

		int success;
		char infoLog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}else{
			std::cout << "Program Linked!" << std::endl;
			std::cout << "Program: " << program << std::endl;
		}
	}
};