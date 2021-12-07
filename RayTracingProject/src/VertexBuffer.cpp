#include "VertexBuffer.h"

#include "Renderer.h"


VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &m_vBufferID));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_vBufferID));
}

void VertexBuffer::AddData(const void* data, uint32_t size)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vBufferID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vBufferID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
