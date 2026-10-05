// ?rva00151EE2@Rva00151EE2@@QAE_NPAPAXH@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// Dump-lane range 5: holder-gated texture applier.
//
// ?rva00151EE2@Rva00151EE2@@QAE_NPAPAXH@Z, retail 0x00151EE2 (198 bytes).
// Framed thiscall returning bool: zeroes the out slot, gates on the +8
// holder pointer and getter revalidation plus +0x20, applies DX8 states,
// then drives the getter-result vtable (stdcall slots 0xE8/0x12C/0xD0/0xFC),
// walks [+0x28, +0x2C) peeking textures, forwards to the rowed 0x1514B2
// chain, and bumps the rowed 0x129670 counter. Early exits return false.

struct IDirect3DBaseTexture8;

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class Rva0015148D
{
public:
	void *rva0015148D();
	void *m_ptr;
	char m_pad04[0x14];
};

class Rva001514B2
{
public:
	void *rva001514B2(int a, int b);
};

class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes();
};

void __cdecl Rva00129670Inc();

class Rva00151EE2Vt
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void __stdcall v52(int a, void *b) = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual void v56() = 0;
	virtual void v57() = 0;
	virtual int __stdcall v58(int x) = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual int __stdcall v63(int a, int b) = 0;
	virtual void v64() = 0;
	virtual void v65() = 0;
	virtual void v66() = 0;
	virtual void v67() = 0;
	virtual void v68() = 0;
	virtual void v69() = 0;
	virtual void v70() = 0;
	virtual void v71() = 0;
	virtual void v72() = 0;
	virtual void v73() = 0;
	virtual void v74() = 0;
	virtual void __stdcall v75(int x) = 0;
};

class Rva00151EE2
{
public:
	bool rva00151EE2(void **out, int b);
private:
	char m_pad[8];
	Rva0015148D m_holder;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
};

// ?rva00151EE2@Rva00151EE2@@QAE_NPAPAXH@Z
bool Rva00151EE2::rva00151EE2(void **out, int b)
{
	*out = 0;
	if (m_holder.m_ptr == 0) {
		return false;
	}
	if (m_holder.rva0015148D() == 0) {
		return false;
	}
	if (m_20 == 0) {
		return false;
	}
	DX8Wrapper::Apply_Render_State_Changes();
	Rva00151EE2Vt *q = (Rva00151EE2Vt *)m_holder.rva0015148D();
	if (q->v58(m_20) < 0) {
		return false;
	}
	int v24 = m_24;
	if (v24 != 0) {
		q->v75(v24);
	}
	int idx = m_28;
	while (idx != m_2C) {
		TextureBaseClass *tb = (TextureBaseClass *)(idx + 4);
		IDirect3DBaseTexture8 *t = tb->Peek_D3D_Base_Texture();
		q->v52(*(int *)idx, t);
		idx += 8;
	}
	((Rva001514B2 *)&m_holder)->rva001514B2(b, m_20);
	if (q->v63(b, 6) >= 0) {
		Rva00129670Inc();
		return true;
	}
	return false;
}
