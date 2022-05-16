#include <iostream>
#include "renderer.hpp"

void clear_errors(){
   while(glGetError() != GL_NO_ERROR);

}

bool check_errors(){
    bool error_free = true;
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] ("
                << error << ')' << std::endl;
        error_free = false;
      }

    return error_free;
}
