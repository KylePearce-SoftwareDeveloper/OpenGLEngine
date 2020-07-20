#pragma once

class indexBuffer
{
private:
	unsigned int m_RendererId;
	unsigned int m_count;
public:
	indexBuffer(const unsigned int* data, unsigned int count);
	~indexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() { return m_count; }
};
