#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

int main(int argc, char** argv)
{
    //cap::graphics::window my_window;

    if(argc == 2){
        std::cout << argv[1] << std::endl;
        cap::graphics::window my_window = cap::graphics::window(argv[1]);
        my_window.Render();
      }

    else{
          cap::graphics::window my_window = cap::graphics::window();
          my_window.Render();
         }

    return 0;

 }
