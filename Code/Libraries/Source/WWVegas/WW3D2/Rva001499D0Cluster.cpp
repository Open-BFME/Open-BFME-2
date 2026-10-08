// cl: /DNDEBUG /MD /EHsc
//
// MeshClass::Get_Deformed_Vertices(Vector3*, Vector3*) at 0x001499D0 (50 bytes).
// Zero Hour mesh.cpp body: the skin assert is compiled out under /DNDEBUG, then
// both destination arrays and the container's HTree go to
// MeshModelClass::get_deformed_vertices (retail 0x0016BF40, unpinned).
//
// Reduced TU-local views on the MakeUnique pattern: the retail RenderObjClass
// Container lives at +0x7C and its Get_HTree is vtable slot 0xE8 (the
// bfmerendobj shim places them at +0x84 / 0xE4, so it is not reused here).
// MeshClass::Model is at +0xC4, proven by the rowed Get_Model 0x001499B0.

class Vector3;
class HTreeClass;
class MeshModelClass
{
public:
	void get_deformed_vertices(Vector3 *dst_vert, Vector3 *dst_norm, const HTreeClass *htree);
	void get_deformed_vertices(Vector3 *dst_vert, const HTreeClass *htree);
};

class Rva001499D0RenderObj
{
public:
	virtual void vf00();
	virtual void vf04();
	virtual void vf08();
	virtual void vf0c();
	virtual void vf10();
	virtual void vf14();
	virtual void vf18();
	virtual void vf1c();
	virtual void vf20();
	virtual void vf24();
	virtual void vf28();
	virtual void vf2c();
	virtual void vf30();
	virtual void vf34();
	virtual void vf38();
	virtual void vf3c();
	virtual void vf40();
	virtual void vf44();
	virtual void vf48();
	virtual void vf4c();
	virtual void vf50();
	virtual void vf54();
	virtual void vf58();
	virtual void vf5c();
	virtual void vf60();
	virtual void vf64();
	virtual void vf68();
	virtual void vf6c();
	virtual void vf70();
	virtual void vf74();
	virtual void vf78();
	virtual void vf7c();
	virtual void vf80();
	virtual void vf84();
	virtual void vf88();
	virtual void vf8c();
	virtual void vf90();
	virtual void vf94();
	virtual void vf98();
	virtual void vf9c();
	virtual void vfa0();
	virtual void vfa4();
	virtual void vfa8();
	virtual void vfac();
	virtual void vfb0();
	virtual void vfb4();
	virtual void vfb8();
	virtual void vfbc();
	virtual void vfc0();
	virtual void vfc4();
	virtual void vfc8();
	virtual void vfcc();
	virtual void vfd0();
	virtual void vfd4();
	virtual void vfd8();
	virtual void vfdc();
	virtual void vfe0();
	virtual void vfe4();
	virtual const HTreeClass *Get_HTree() const;
};

class MeshClass
{
public:
	void Get_Deformed_Vertices(Vector3 *dst_vert, Vector3 *dst_norm);
	void Get_Deformed_Vertices(Vector3 *dst_vert);
	void rva00149bb0();

private:
	char m_base[0x7C];
	Rva001499D0RenderObj *m_container; // +0x7C
	char m_pad[0xC4 - 0x80];
	MeshModelClass *Model;             // +0xC4
};

void MeshClass::Get_Deformed_Vertices(Vector3 *dst_vert, Vector3 *dst_norm)
{
	Model->get_deformed_vertices(dst_vert, dst_norm,
		(m_container != 0) ? m_container->Get_HTree() : 0);
}

// MeshClass::Get_Deformed_Vertices(Vector3*) at 0x00149A10 (64 bytes), right
// after the two-array overload as in Zero Hour mesh.cpp, with the same
// container guard; the compiler duplicates the short call tail into both arms.
// The single-array MeshModelClass::get_deformed_vertices (0x0016B680) is
// pinned from this body.
void MeshClass::Get_Deformed_Vertices(Vector3 *dst_vert)
{
	Model->get_deformed_vertices(dst_vert,
		(m_container != 0) ? m_container->Get_HTree() : 0);
}

// ---------------------------------------------------------------------------
// MeshClass::rva00149bb0 at 0x00149BB0 (57 bytes). Address-derived; identity
// not recovered. It reads the pointer at Model+0x94 and copies a pair of
// globals when either of that object's +0xB8/+0x108 flags is set. The globals
// are named address-derived externs (the DIR32 relocations are masked by the
// byte gate; the names keep the literal addresses out of the source).
extern int g_rva009f36b0;
extern int g_rva009f36ac;
extern int G00DEDA78;
extern int g_rva009eda24;

class Rva00149BB0Inner
{
public:
	char m_padB8[0xB8];
	int m_flagB8;   // +0xB8
	char m_padBC[0x108 - 0xBC];
	int m_flag108;  // +0x108
};

class Rva00149BB0Model
{
public:
	char m_pad94[0x94];
	Rva00149BB0Inner *m_inner; // +0x94
};

void MeshClass::rva00149bb0()
{
	Rva00149BB0Model *model = (Rva00149BB0Model *)Model;
	if (model == 0)
		return;
	Rva00149BB0Inner *inner = model->m_inner;
	if (inner->m_flagB8 != 0 || inner->m_flag108 != 0)
	{
		G00DEDA78 = g_rva009f36b0;
		g_rva009eda24 = g_rva009f36ac;
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_rva009eda24@@3HA=?FogColor@DX8Wrapper@@1KA")
