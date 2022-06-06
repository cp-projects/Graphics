#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "renderer.hpp"


class Shader{
	
	
    private:
	    std::string m_filePath;
	    unsigned int m_RendererID;
	    struct shaderProgramSource;



    public:
	    Shader(const std::string& filepath);
	    ~Shader();

	    void Bind() const;
	    void Unbind() const;

	    void setUniform4f(const std::string& name, float v0, float v1, float f2, float  f3);


    private:
	    static unsigned int CreateShaders(const std::string& vertexShader, const std::string fragmentShader);
	    static shaderProgramSource ParseShader(const std::string& path);
	    static int CompileShader(unsigned int type, const std::string& source);
	    unsigned int GetUniformLocation(const std::string& name);

};
