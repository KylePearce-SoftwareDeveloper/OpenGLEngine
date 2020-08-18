#pragma once

#include <GL/glew.h>

#include "../hpp/VertexArray.h"
#include "../hpp/IndexBuffer.h"
#include "../hpp/Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& Shader) const;
};
