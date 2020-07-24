#pragma once

#include <GL/glew.h>

#include "../hpp/vertexArray.h"
#include "../hpp/indexBuffer.h"
#include "../hpp/shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class renderer
{
public:
    void clear() const;
    void draw(const vertexArray& va, const indexBuffer& ib, const shader& shader) const;
};