// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// MeshModelClass::Needs_Vertex_Normals, retail 0x00171850 (20 bytes).
// Ported from the BFME1 reconstruction (Code/Libraries/Source/WWVegas/WW3D2/meshmdl.cpp).
// Retail proves the layout: Flag byte at +0x19 tested with PRELIT_MASK
// 0xE0, CurMatDesc pointer at +0x94 tail-jumped to its
// Do_Mappers_Need_Normals (matched at 0x15A9F0, resolves via the ledger).
// Pin for Needs_Vertex_Normals itself already exists from Define_FVF.

class MeshMatDescClass
{
public:
	bool Do_Mappers_Need_Normals();
};

class MeshModelClass
{
public:
	bool Needs_Vertex_Normals();
	int Get_Flag(int mask) const { return m_flagByte & mask; }

	enum { PRELIT_MASK = 0xE0 };

private:
	unsigned char m_pad0[0x19];
	unsigned char m_flagByte;
	unsigned char m_pad1[0x94 - 0x1A];
	MeshMatDescClass *CurMatDesc;
};

// ?Needs_Vertex_Normals@MeshModelClass@@QAE_NXZ
bool MeshModelClass::Needs_Vertex_Normals()
{
	if (Get_Flag(PRELIT_MASK) == 0) {
		return true;
	}
	return CurMatDesc->Do_Mappers_Need_Normals();
}
