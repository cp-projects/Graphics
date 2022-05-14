#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

struct shaderProgramSource{

    std::string VertexSource;
    std::string FragmentSource;
};

//remember to parse shaders
static shaderProgramSource ParseShader(const std::string& path){

   std::ifstream stream(path);

   enum class ShaderType{
       NONE = -1, VERTEX = 0, FRAGMENT = 1,
   };

   std::string line;
   std::stringstream stst[2];
   ShaderType type = ShaderType::NONE;
   while(getline(stream, line)){

	   if(line.find("#shader") != std::string::npos){
	       if(line.find("vertex") != std::string::npos)
		       type = ShaderType::VERTEX;
	       else if(line.find("fragment") != std::string::npos)
		       type = ShaderType::FRAGMENT;
	             }

	   else
		   stst[(int)type] << line << '\n'; 
          }

   return {stst[0].str(), stst[1].str()};
 
}


//make sure source exists
static int CompileShader(unsigned int type, const std::string& source){

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	char message[length];
	glGetShaderInfoLog(id, length, &length, message);
	std::cout << "Failed to Compile " << 
		(type == GL_VERTEX_SHADER ? "vertex":"fragment") << " Shader\n";
	std::cout << message << std::endl;

	glDeleteShader(id);
	return 0;
    }

    return id;

}


static unsigned int CreateShaders(const std::string& vertexShader, const std::string fragmentShader){

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //deletes .o files
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
 
}

int main(){
           
	
	GLFWwindow* window;


        if (!glfwInit())
            exit(1);

        window = glfwCreateWindow(1000,750, "Defaul Window", NULL, NULL);

        if(!window)
            glfwTerminate();


        glfwMakeContextCurrent(window);

        
	glewInit();

	std::cout << glGetString(GL_VERSION) << std::endl;

        float positions[6] = {
	
	    -0.5f, -0.5f,
             0.0f, 0.5f,
	     0.5f, -0.5f
	};


	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);
		
        shaderProgramSource source = ParseShader("res/shaders/basic.shader");
	//std::cout << source.VertexSource << std::endl;
	//std::cout << source.FragmentSource << std::endl;


	unsigned int shader = CreateShaders(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)){

              /* Render here */
              glClear(GL_COLOR_BUFFER_BIT);
	      
              glDrawArrays(GL_TRIANGLES, 0,3);

              /* Swap front and back buffers */
              glfwSwapBuffers(window);

               /* Poll for and process events */
              glfwPollEvents();
                    
             }

	//glDeleteProgram(shader);
	glfwTerminate();
}
