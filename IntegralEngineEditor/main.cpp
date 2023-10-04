#include "./CoreComponents/MeshRenderer.cpp"
std::string ProjectPath = "";

float vertices[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

int main(int argc, char *argv[]) {
	if(argc > 1) ProjectPath = argv[1];
	std::cout << ProjectPath << std::endl;

	if (!glfwInit()) {
		std::cout << "Error Initializing!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "I dont know what the heck im doin", NULL, NULL);

	if (window == NULL) {
		std::cout << "An error occured while creating the window!" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	Shader* s = new Shader("C:/Users/Hiago Fernando/Desktop/Coisas Importantes/IntegralEngine/IntegralEngineEditor/VertexShader.vert", "C:/Users/Hiago Fernando/Desktop/Coisas Importantes/IntegralEngine/IntegralEngineEditor/FragShader.frag");

	GameObject* obj = new GameObject();
	MeshRenderer* m = obj->AddComponent<MeshRenderer>();
	m->SetShaders(s);

	std::cout << "Starting Update!" << std::endl;
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for(MonoBehaviour* c : obj->components){
			c->callUpdate();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}