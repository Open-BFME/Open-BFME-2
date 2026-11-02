// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?rva000834CE@Rva000834CE@@QAEXXZ, retail 0x000834ce, 121 bytes. Banked partial (score 0.995) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <vector>
//
// Target bytes establish a one-shot guarded call to 0x0008304A followed by a
// loop over the pointer range at +0x70/+0x74. Each slot binds an index buffer
// from +0x88, a vertex buffer from +0x70, and draws with the vertex count at
// +0x7C and index count at +0x94. The three DX8Wrapper callees are matched
// rows. Owner identity and the +0xA0 flag's broader purpose remain unknown;
// field roles are inferred from target accesses and callee ABIs.

class IndexBufferClass;
class VertexBufferClass;

#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

// The native refresh target is now rowed in W3DWater.cpp at 0x0008304A.
class RenderableStandingWaterArea
{
public:
	void AllocateAndFillBuffers();
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
		((RenderableStandingWaterArea *)this)->AllocateAndFillBuffers();
		m_needsRefresh = false;
	}

	for (unsigned int i = 0; i < m_vertexBuffers.size(); ++i) {
		DX8Wrapper::Set_Index_Buffer(m_indexBuffers[i], 0);
		DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffers[i], 0);
		DX8Wrapper::Draw_Triangles(0, m_indexCounts[i] / 3, 0, m_vertexCounts[i]);
	}
}
