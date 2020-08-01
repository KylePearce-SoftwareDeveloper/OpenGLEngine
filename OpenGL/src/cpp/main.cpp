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

#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw_gl3.h"

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
            -50.0f, -50.0f, 0.0f, 0.0f,//0 (only 1 "attribute" in this vertex, position)
             50.0f, -50.0f, 1.0f, 0.0f,//1 (only 1 "attribute" in this vertex, position)
             50.0f,  50.0f, 1.0f, 1.0f,//2 (only 1 "attribute" in this vertex, position)
            -50.0f,  50.0f, 0.0f, 1.0f//3 (only 1 "attribute" in this vertex, position)
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
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        
        shader shader("res/shaders/basic.shader");
        shader.bind();

        Texture texture("res/textures/GOAT.png");
        texture.Bind();
        shader.setUniform1i("u_Texture", 0);

        va.Unbind();
        shader.unbind();
        vb.unbind();
        ib.unbind();

        renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.clear();

            ImGui_ImplGlfwGL3_NewFrame();

            

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.bind();
                shader.setUniformMat4f("u_MVP", mvp);
                renderer.draw(va, ib, shader);
            }
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.bind();
                shader.setUniformMat4f("u_MVP", mvp);
                renderer.draw(va, ib, shader);
            }

            if (r > 1.0f)
                increment = -0.5f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            {
                ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f 
                ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}