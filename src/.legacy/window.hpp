#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLEW_STATIC

namespace cap{

namespace graphics{

class window{

    private:
             
            typedef GLFWwindow* window_t;   


    public:
	    window()
		    :m_name("Default Window"), m_len(1000), m_hieght(750){
		    
                        if (!glfwInit())
                            exit(1);

		        m_window = glfwCreateWindow(m_len, m_hieght, m_name, NULL, NULL);
                        
			if(!m_window)
			    glfwTerminate();
			   

			glfwMakeContextCurrent(m_window);

			//glewExperimental=true;
			//GLenum err=glewInit();
                        //if(err!=GLEW_OK)
                         //std::cout<<"glewInit failed, aborting."<<std::endl;
  
			glewInit();// != GLEW_OK)
                            //std::cout << "Error" << '\n';
		    }


	    window(const char* name)
                    :m_name(name), m_len(1000), m_hieght(750){

                        if (!glfwInit())
                            exit(1);

                        m_window = glfwCreateWindow(m_len, m_hieght, m_name, NULL, NULL);

                        if(!m_window)
                            glfwTerminate();


                        glfwMakeContextCurrent(m_window);
			
		//	glewInit(); //!= GLEW_OK)
			    //std::cout << "Error" << '\n';
                    }


	    ~window(){glfwTerminate();}


    private:
	    window_t m_window;
	    int m_len;
	    int m_hieght;
	    const char* m_name;

    public:
            


	    void Render(){

		if (!glfwInit())
                            exit(1);

		if(!m_window)
                            glfwTerminate();

	    
	        glfwMakeContextCurrent(m_window);

                glewInit();

                /* Loop until the user closes the window */
                while (!glfwWindowShouldClose(m_window)){
                    	
		    /* Render here */
                    glClear(GL_COLOR_BUFFER_BIT);

		    glBegin(GL_TRIANGLES);
                    glVertex2f(-0.5f, -0.5f);
                    glVertex2f(0.0f, 0.5f);
                    glVertex2f(0.5f,-0.5f);
                    glEnd();

                    /* Swap front and back buffers */
                    glfwSwapBuffers(m_window);

                     /* Poll for and process events */
                     glfwPollEvents();
                    }	    
	     }

};


}//end namespace graphics

}//end namespace cap
