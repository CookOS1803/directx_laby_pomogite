#pragma once
#include "NormWin.h"
#include <vector>
#include <memory>
#include <string_view>
#include "SimpleVertex.h"
#include "DXDeleter.h"
#include <DirectXHelpers.h>

class Mesh
{
public:

	constexpr Mesh(class Graphics* gfx) : m_vertices(), m_indices(), p_gfx(gfx) {}
	Mesh(const Mesh& other);
	~Mesh();

	constexpr const std::vector<SimpleVertex>& Vertices() const noexcept { return m_vertices; }
	constexpr const std::vector<WORD>& Indices() const noexcept { return m_indices; }
	constexpr ID3D11Buffer* VertexBuffer() const noexcept { return p_vertexBuffer.get(); }
	constexpr ID3D11Buffer* IndexBuffer() const noexcept { return p_indexBuffer.get(); }

	void SetVertices(const std::vector<SimpleVertex>& vertices);
	void RecreateVertexBuffer();
	void SetIndices(const std::vector<WORD>& indices);
	void RecreateIndexBuffer();
	void Rebuild();
	void Clear();
	void MakeSphere(int slices, int stacks);
	int AddVertex(SimpleVertex d);
	void AddTriangle(WORD i0, WORD i1, WORD i2);
	void AddQuad(WORD i0, WORD i1, WORD i2, WORD i3);

	Mesh& operator=(const Mesh& other);

	void LoadFromFile(std::wstring_view fileName);

private:

	Graphics* p_gfx;

	std::vector<SimpleVertex> m_vertices;
	std::vector<WORD> m_indices;

	std::unique_ptr<ID3D11Buffer, DXDeleter<ID3D11Buffer>> p_vertexBuffer = nullptr;
	std::unique_ptr<ID3D11Buffer, DXDeleter<ID3D11Buffer>> p_indexBuffer = nullptr;
};

