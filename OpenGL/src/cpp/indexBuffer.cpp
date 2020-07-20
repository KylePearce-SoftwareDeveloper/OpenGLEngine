#include "../hpp/indexBuffer.h"
#include "../hpp/renderer.h"

indexBuffer::indexBuffer(const unsigned int* data, unsigned int count)
    : m_count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererId));//created buffer (section of memory on GPU)
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));//about to work on buffer
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));//fill buffer with data
}

indexBuffer::~indexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererId));
}

void indexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void indexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
