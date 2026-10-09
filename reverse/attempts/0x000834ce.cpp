// ?rva000834CE@Rva000834CE@@QAEXXZ
// partial score=0.995 date=2026-10-09
// ?rva000834CE@Rva000834CE@@QAEXXZ
// partial score=0.98 date=2026-10-07
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>
//
// ?rva000834CE@Rva000834CE@@QAEXXZ @ 0x000834CE (121B), Ghidra boundary.
// Target bytes establish a one-shot guarded call to 0x0008304A followed by a
// loop over the pointer range at +0x70/+0x74. Each slot binds an index buffer
// from +0x88, a vertex buffer from +0x70, and draws with the vertex count at
// +0x7C and index count at +0x94. The three DX8Wrapper callees are matched
// rows. Owner identity and the +0xA0 flag's broader purpose remain unknown;
// field roles are inferred from target accesses and callee ABIs.

class IndexBufferClass;
class VertexBufferClass;

class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *buffer, unsigned short slot);
	static void Set_Vertex_Buffer(const VertexBufferClass *buffer, unsigned stream);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count,
		unsigned min_vertex_index, unsigned vertex_count);
};

class Rva0008304A
{
public:
	void rva0008304A();
};

class Rva000834CE
{
	char m_pad00[0x70];
	_STL::vector<VertexBufferClass *> m_vertexBuffers;
	_STL::vector<unsigned> m_vertexCounts;
	_STL::vector<IndexBufferClass *> m_indexBuffers;
	_STL::vector<int> m_indexCounts;
	bool m_needsRefresh;

public:
	void rva000834CE();
};

void Rva000834CE::rva000834CE()
{
	if (m_needsRefresh) {
		((Rva0008304A *)this)->rva0008304A();
		m_needsRefresh = false;
	}

	for (unsigned int i = 0; i < m_vertexBuffers.size(); ++i) {
		DX8Wrapper::Set_Index_Buffer(m_indexBuffers[i], 0);
		DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffers[i], 0);
		DX8Wrapper::Draw_Triangles(0, m_indexCounts[i] / 3, 0, m_vertexCounts[i]);
	}
}
