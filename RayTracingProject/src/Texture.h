#pragma once

#include "Renderer.h"

class Texture
{
private:
	uint32_t m_TextureID;
	std::string m_FilePath;
	uint8_t* m_LocalBuffer;
	int32_t m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	inline int32_t GetWidth() const { return m_Width; }
	inline int32_t GetHeight() const { return m_Height; }
};