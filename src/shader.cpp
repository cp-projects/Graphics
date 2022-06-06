#include "shader.hpp"

Shader::Shader(const std::string& filepath)
	:m_filePath(filepath), m_RendererID(0){
	
	    //CompileShader();
	
	}
	

Shader::~Shader(){}



struct Shader::shaderProgramSource{

    std::string VertexSource;
    std::string FragmentSource;
};

//remember to parse shaders
Shader::shaderProgramSource Shader::ParseShader(const std::string& path){

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



unsigned int Shader::CreateShaders(const std::string& vertexShader, const std::string fragmentShader){

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


//make sure source exists
int Shader::CompileShader(unsigned int type, const std::string& source){

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

void Shader::Bind() const{}

void Shader::Unbind() const{}


void Shader::setUniform4f(const std::string& name, float v0, float v1, float f2, float  f3){}
	    
unsigned int Shader::GetUniformLocation(const std::string& name){

return 0;}
