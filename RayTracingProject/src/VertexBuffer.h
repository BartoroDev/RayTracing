#pragma once

#include <stdint.h>

class VertexBuffer
{
private:
	uint32_t m_vBufferID;
public:
	VertexBuffer(const void* data, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};