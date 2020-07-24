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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
            -0.5f, -0.5f,//0 (only 1 "attribute" in this vertex, position)
             0.5f, -0.5f,//1 (only 1 "attribute" in this vertex, position)
             0.5f,  0.5f, //2 (only 1 "attribute" in this vertex, position)
            -0.5f,  0.5f//3 (only 1 "attribute" in this vertex, position)
        };

        unsigned int indices[] = { //order in which to draw the above indexed vertices
            0, 1, 2,
            2, 3, 0
        };

        vertexArray va;
        vertexBuffer vb(positions, 4 * 2 * sizeof(float));
        vertexBufferLayout layout;
        layout.push<float>(2);
        va.addBuffer(vb, layout);
        

        indexBuffer ib(indices, 6);

        shader shader("res/shaders/basic.shader");
        shader.bind();
        shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

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