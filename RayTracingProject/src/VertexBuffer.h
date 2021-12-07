#pragma once

#include <stdint.h>

class VertexBuffer
{
private:
	uint32_t m_vBufferID;
public:
	
	VertexBuffer();
	~VertexBuffer();

	void AddData(const void* data, uint32_t size);
	void Bind() const;
	void Unbind() const;
};