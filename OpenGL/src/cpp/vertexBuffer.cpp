#include "../hpp/vertexBuffer.h"
#include "../hpp/renderer.h"

vertexBuffer::vertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererId));//created buffer (section of memory on GPU)
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));//about to work on buffer
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));//fill buffer with data
}

vertexBuffer::~vertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererId));
}

void vertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void vertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
