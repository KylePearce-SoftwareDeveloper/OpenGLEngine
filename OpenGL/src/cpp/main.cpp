#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../hpp/renderer.h"
#include "../hpp/vertexBuffer.h"
#include "../hpp/vertexBufferLayout.h"
#include "../hpp/indexBuffer.h"
#include "../hpp/vertexArray.h"
#include "../hpp/shader.h"
#include "../hpp/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            100.0f, 100.0f, 0.0f, 0.0f,//0 (only 1 "attribute" in this vertex, position)
             200.0f, 100.0f, 1.0f, 0.0f,//1 (only 1 "attribute" in this vertex, position)
             200.0f, 200.0f, 1.0f, 1.0f,//2 (only 1 "attribute" in this vertex, position)
            100.0f,  200.0f, 0.0f, 1.0f//3 (only 1 "attribute" in this vertex, position)
        };

        unsigned int indices[] = { //order in which to draw the above indexed vertices
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vertexArray va;
        vertexBuffer vb(positions, 4 * 4 * sizeof(float));
        vertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        va.addBuffer(vb, layout);
        

        indexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

        glm::mat4 mvp = proj * view * model;
        
        shader shader("res/shaders/basic.shader");
        shader.bind();
        shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.setUniformMat4f("u_MVP", mvp);

        Texture texture("res/textures/GOAT.png");
        texture.Bind();
        shader.setUniform1i("u_Texture", 0);

        va.Unbind();
        shader.unbind();
        vb.unbind();
        ib.unbind();

        renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.clear();

            shader.bind();
            shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0);

            renderer.draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.5f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}