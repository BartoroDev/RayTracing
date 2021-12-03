#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
	:m_Count(count)
{
	GLCall(glGenBuffers(1, &m_iBufferID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBufferID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_iBufferID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBufferID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
