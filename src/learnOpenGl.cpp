#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>


#include"renderer.hpp"
#include"vertex_buffer.hpp"
#include"index_buffer.hpp"


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

	glfwSwapInterval(1);
        
	glewInit();
	std::cout << glGetString(GL_VERSION) << std::endl;

  {//Defining Scope So Destructors Don't Run After Terminate

        float positions[] = {
	
	     -0.5f, -0.5f,
             0.5f, -0.5f,
	     0.5f, 0.5f,
	     -0.5f, 0.5f

	};

	unsigned int indicies[] = {
	    0, 1, 2,
	    2, 3, 0
	};


	//bind array
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	VertexBuffer vb(positions, 4*2*sizeof(float));

	glEnableVertexAttribArray(0);
	//connects vertex array to vertex buffer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

	IndexBuffer ib(indicies, 6);	


        shaderProgramSource source = ParseShader("res/shaders/basic.shader");
	unsigned int shader = CreateShaders(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_Color");
        assert(location != -1);
	glUniform4f(location, 0.2f,0.2f,0.8f,1.0f);

	float r = 0.0f;
	float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)){

              /* Render here */
              glClear(GL_COLOR_BUFFER_BIT);

              glUniform4f(location, r,0.2f,0.8f,1.0f);	      
	      clear_errors();
              glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
              assert(check_errors());

	      if(r > 1.0f)
		      increment = -0.05f;
	      else if(r < 0.0f)
		      increment = 0.05f;

	      r+=increment;


              /* Swap front and back buffers */
              glfwSwapBuffers(window);

               /* Poll for and process events */
              glfwPollEvents();
                    
             }

  }//END SCOPE

	//glDeleteProgram(shader);
	glfwTerminate();
}
