#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"
#include <iostream>
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_vArrayID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_vArrayID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_vArrayID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
