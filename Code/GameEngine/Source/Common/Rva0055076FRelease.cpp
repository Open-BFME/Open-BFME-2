// cl: /MD
// ?rva0055076F@Rva0055076F@@QAEXXZ @0x0055076F 13B.
// Null-and-delete of owned pointer at +0 via rowed scalar delete 0x0002FD60.
// Evidence: callee rowed 0x0002FD60; 7 call sites incl thunk at 0x005753DD and 0x00575FE8.
class Rva0055076F
{
public:
	void rva0055076F();
private:
	void *m_00;
};

void Rva0055076F::rva0055076F()
{
	void *p = m_00;
	m_00 = 0;
	::operator delete(p);
}
