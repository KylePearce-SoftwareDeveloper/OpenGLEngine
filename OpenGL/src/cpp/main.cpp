#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
        -0.5f, -0.5f,//first vertex (only 1 "attribute" in this vertex, position)
         0.0f,  0.5f,//seccond vertex (only 1 "attribute" in this vertex, position)
         0.5f, -0.5f //third vertex (only 1 "attribute" in this vertex, position)
    };

    unsigned int buffer;//will later be the ID of the buffer
    glGenBuffers(1, &buffer);//created buffer (section of memory on GPU)
    glBindBuffer(GL_ARRAY_BUFFER, buffer);//about to work on buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);//fill buffer with data
    glEnableVertexAttribArray(0);//enable the following atrribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//define the layout of the data now in the buffer


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);//draws using currently bound buffer (glBindBuffer) and the data that is inside it

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}