// cl: /DNDEBUG /MD /GX-
//
// ?read_Rva00188AF0@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x00188AF0 (190 bytes: ret C2 08 00 at 0x188BAB).
// BFME2-new 0x3F-case reader (chunk 0x3F undefined in w3d_file.h; dispatch in
// MeshModelReadMaterialPass.cpp). Shape is the read_vertex_material_ids
// template verbatim (same 190B: single-or-array uint32, 2-arg single install
// plus 3-arg indexed install, frameless /O2 /G7, bool returns). Retail-
// measured differences from the 0x1888F0 body (raw diff is 14 bytes: 4
// displacement upgrades plus REL32 knock-ons from the 0x40-shifted call
// sites):
// - Matdesc check arrays at +0xB8/+0x108 (vs +0xA8/+0xE8).
// - Context entry list at +0xF8 (vs VertexMaterials +0xC8); the Peek lookup
//   inlines as the array read (no out-of-line body, no pin).
// - Indexed arm loops PolyCount at this+0x24 (vs VertexCount +0x28).
// - Callees are the +0xB8-family single/indexed installers (new opaque pins
//   0x15A800/0x15D300; byte-twins of Set_Single_Material/Set_Material with
//   only displacement bytes changed: 53/55 and 88/89 identical).
// True identities of the 0x3F chunk and the +0xB8 family are open; names are
// opaque Rva pins and offsets are measured, never invented.
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess
// precedent). Frameless, no EH temps (no BfmeHandleCX here).

class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_Length();
	unsigned long Read(void *buffer, unsigned long bytes);
};

class MeshMatDescClass
{
public:
	void Set_Single_Rva0015A800(void *entry, int pass);
	void Set_Rva0015D300(int index, void *entry, int pass);
	bool Has_Rva00188AF0_Data(int pass) { return SingleEntries[pass] != 0 || ArrayEntries[pass] != 0; }

private:
	char m_pad0[0xB8];
	void *SingleEntries[4];
	char m_pad1[0x108 - 0xC8];
	void *ArrayEntries[4];
};

typedef char MeshMatDescSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

class MeshLoadContextClass
{
	virtual ~MeshLoadContextClass();
	char m_pad0[0x88 - 4];
public:
	unsigned long PrelitChunkID;
	int CurPass;
	int CurTexStage;
private:
	char m_pad1[0xF8 - 0x94];
public:
	void **Rva00188AF0Entries;
private:
	char m_pad2[0x124 - 0xFC];
public:
	MeshMatDescClass AlternateMatDesc;
public:
	void *Peek_Rva00188AF0Entry(unsigned long index) { return Rva00188AF0Entries[index]; }
};

class MeshModelClass
{
	virtual ~MeshModelClass();
	char m_pad0[0x24 - 4];
public:
	int PolyCount;
	int VertexCount;
private:
	char m_pad1[0x8C - 0x2C];
public:
	MeshMatDescClass *DefMatDesc;
	int Get_Polygon_Count() const { return PolyCount; }
protected:
	bool read_Rva00188AF0(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

// ?read_Rva00188AF0@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_Rva00188AF0(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	unsigned long entry;
	MeshMatDescClass *matdesc = DefMatDesc;

	if (matdesc->Has_Rva00188AF0_Data(context->CurPass)) {
		matdesc = &(context->AlternateMatDesc);
	}

	if (cload.Cur_Chunk_Length() == 1 * sizeof(unsigned long)) {
		cload.Read(&entry, sizeof(entry));
		matdesc->Set_Single_Rva0015A800(context->Peek_Rva00188AF0Entry(entry), context->CurPass);
	} else {
		for (int i = 0; i < Get_Polygon_Count(); i++) {
			cload.Read(&entry, sizeof(unsigned long));
			matdesc->Set_Rva0015D300(i, context->Peek_Rva00188AF0Entry(entry), context->CurPass);
		}
	}

	return true;
}
