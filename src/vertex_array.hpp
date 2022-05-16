#pragma once

#include "vertex_buffer.hpp"

class VertexArray{

private:


public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout);




};
