// cl: /O1 /MD /EHsc /DNDEBUG
//
// ?rva00091D0D@Rva00091D0D@@QAEXXZ @0x00091D0D 37B: empty-base op, optional
// worker call, guarded tail dispatch. Invokes the pinned 1B ret stub
// 0x000B3FD0 on this (shared empty-base operation; implicit empty-base
// calls are elided by the compiler, so it is spelled explicitly), calls
// the pinned no-arg method 0x0010082F on +0x14 when non-null (this dies
// right after the load, so esi is popped before the call), then
// tail-jumps to the 16-byte dispatch at 0x0009A338 (rowed as the free
// Rva007B7600) as a member call on the shadow manager when it is set:
// retail loads ecx from g_shadowManager for the test and keeps it for the
// jump, which only a thiscall spelling reproduces. Honest address-derived
// names; boundary verified (push esi at 0x91D0D, jmp-or-ret at end).

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

class Gen0003AC38
{
public:
	void rva0009A338();
};
extern Gen0003AC38 *g_shadowManager;

// ?rva00091D0D@Rva00091D0D@@QAEXXZ
void Rva00091D0D::rva00091D0D()
{
	((Rva000B3FD0 *)this)->rva000B3FD0();
	if (m_14)
		m_14->rva0010082F();
	if (g_shadowManager)
		g_shadowManager->rva0009A338();
}

