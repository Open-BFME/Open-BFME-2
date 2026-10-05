// ?rva00091D0D@Rva00091D0D@@QAEXXZ
// partial score=0.95 date=2026-10-06
// cl: /O1 /MD /EHsc /DNDEBUG
//
// ?rva00091D0D@Rva00091D0D@@QAEXXZ @0x00091D0D 37B: empty-base op, optional
// worker call, guarded tail dispatch. Invokes the pinned 1B ret stub
// 0x000B3FD0 on this (shared empty-base operation; implicit empty-base
// calls are elided by the compiler, so it is spelled explicitly), calls
// the pinned no-arg method 0x0010082F on +0x14 when non-null (this dies
// right after the load, so esi is popped before the call), then
// tail-jumps to the rowed thunk Rva007B7600 (0x0009A338) when the
// shadow-manager global is set. Honest address-derived names; boundary
// verified (push esi at 0x91D0D, jmp-or-ret at end).

class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class Rva0010082F
{
public:
	void rva0010082F();
};

class Rva00091D0D
{
public:
	void rva00091D0D();

private:
	char m_pad00[0x14];
	Rva0010082F *m_14;
};

extern void *W3DGCData00DE5DFC;
void Rva007B7600();

// ?rva00091D0D@Rva00091D0D@@QAEXXZ
void Rva00091D0D::rva00091D0D()
{
	((Rva000B3FD0 *)this)->rva000B3FD0();
	if (m_14)
		m_14->rva0010082F();
	void *shadow = W3DGCData00DE5DFC;
	if (shadow)
		Rva007B7600();
}

#pragma comment(linker, "/alternatename:?W3DGCData00DE5DFC@@3PAXA=?g_shadowManager@@3PAVGen0003AC38@@A")
