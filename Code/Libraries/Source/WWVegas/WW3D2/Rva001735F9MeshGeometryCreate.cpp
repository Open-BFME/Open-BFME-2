// cl: /O1 /G7 /arch:SSE /EHsc /MD
//
// ?rva001735F9@Rva001735F9@@QAEXPAVMeshModelClass@@@Z, retail 0x001735F9
// (145 bytes, thiscall, RET4).  Rebuilds the per-mesh object held at
// MeshModelClass +0xBC: deletes the old one (pinned non-virtual dtor
// 0x0018C57C, then operator delete), allocates 0x28 bytes and runs the rowed
// constructor 0x0018C54E, then initialises it from the mesh (0x0018C84E);
// when that returns false the new object is deleted and the slot cleared.
// Nothing is returned (the failure arm leaves operator delete's EAX).
//
// Target evidence: the bytes; the receiver is the context published at
// 0x00DF6F94 and the call site is MeshModelClass::Register_For_Rendering
// (0x001732B1), whose rowed sibling DeleteModelGapFiller (0x001732E2)
// deletes the same +0xBC slot with the same inline delete.  The WorldBuilder
// twin 0x00A218D0 (callgraph score 1.0) has the same sequence and calls the
// initialiser by its symbol FXShaderGeometry::Init.  The constructor, the
// destructor and the receiver keep their ledger's address-derived names;
// one object is reached through those three spellings.
class Rva001732C6
{
public:
	~Rva001732C6();
};

class Rva0018C54E
{
public:
	Rva0018C54E();
	char m_pad[0x28];
};

class MeshModelClass
{
public:
	char m_pad[0xBC];
	Rva001732C6 *m_geometry;	// +0xBC
};

class FXShaderGeometry
{
public:
	bool Init(MeshModelClass *mesh);
};

class Rva001735F9
{
public:
	void rva001735F9(MeshModelClass *mesh);
};

void Rva001735F9::rva001735F9(MeshModelClass *mesh)
{
	if (mesh->m_geometry != 0)
		delete mesh->m_geometry;
	mesh->m_geometry = 0;
	mesh->m_geometry = (Rva001732C6 *)new Rva0018C54E;
	if (!((FXShaderGeometry *)mesh->m_geometry)->Init(mesh)) {
		if (mesh->m_geometry != 0)
			delete mesh->m_geometry;
		mesh->m_geometry = 0;
	}
}
