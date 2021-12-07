#pragma once

#include <stdint.h>

class IndexBuffer
{
private:
	uint32_t m_iBufferID;
	uint32_t m_Count;

public:
	//template<typename T>
	IndexBuffer();
	~IndexBuffer();

	void BindData(const uint32_t* data, uint32_t count);
	void Bind() const;
	void Unbind() const;

	inline uint32_t GetCount() const { return m_Count; }
};