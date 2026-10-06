// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Peek_Vertex_Material@MaterialInfoClass@@QBEPAVVertexMaterialClass@@H@Z
// retail 0x000636C9, 22 bytes, size-optimised (/O1).
//
// The bounds-checked inline Peek from the MaterialInfoClass replica in
// MaterialRemapperClassCtor.cpp (vertex-material count at +0x18, array base
// at +0x0C), emitted out of line the way a size-optimised unit leaves it.
// Retail callers: 0x0006374E, 0x000CE2A5, 0x0014BE36. The replica mangles
// identically to the real member.

#define NULL 0

class VertexMaterialClass;

class MaterialInfoClass
{
public:
	VertexMaterialClass *Peek_Vertex_Material(int index) const
	{
		if (index < m_vmatCount) {
			return m_vmatBase[index];
		}
		return NULL;
	}

private:
	void *m_vptr;
	int NumRefs;
	int m_pad08;
	VertexMaterialClass **m_vmatBase;
	int m_pad10;
	int m_pad14;
	int m_vmatCount;
};

extern VertexMaterialClass *(MaterialInfoClass::*const g_bfmePeekVertexMaterialAnchor)(int) const;
VertexMaterialClass *(MaterialInfoClass::*const g_bfmePeekVertexMaterialAnchor)(int) const = &MaterialInfoClass::Peek_Vertex_Material;