#include "../hpp/vertexArray.h"
#include "../hpp/vertexBufferLayout.h"
#include "../hpp/renderer.h"

vertexArray::vertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

vertexArray::~vertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void vertexArray::addBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout)
{
	Bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset));
		offset += element.count * vertexBufferElement::getSizeOfType(element.type);
	}
}

void vertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void vertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
