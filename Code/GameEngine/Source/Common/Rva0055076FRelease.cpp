// cl: /MD
// ?rva0055076F@Rva0055076F@@QAEXXZ @0x0055076F 13B.
// Null-and-delete of owned pointer at +0 via rowed scalar delete 0x0002FD60.
// Evidence: callee rowed 0x0002FD60; 7 call sites incl thunk at 0x005753DD and 0x00575FE8.
class Rva0055076F
{
public:
	__declspec(noinline) void rva0055076F();
private:
	void *m_00;
};

void Rva0055076F::rva0055076F()
{
	void *p = m_00;
	m_00 = 0;
	::operator delete(p);
}

// Native5753DD..5753E2 JMP55076F; unchanged thiscall receiver and RET0.
// Original wrapper name and enclosing type remain unknown.
struct Rva005753DDReleaseForward { void release(); };
void Rva005753DDReleaseForward::release() {
    reinterpret_cast<Rva0055076F *>(this)->rva0055076F();
}
