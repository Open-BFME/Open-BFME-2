// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: lazy flag inits at 0x1EB6FE (36B) and 0x1EB68A (27B).
// Both bump +0xC and set +0xC3 on first use, then run 0x1EB456.
// 0x1EB6FE is gated on +0xC2 and passes (1,1); 0x1EB68A always runs and
// passes (0,1). Address-derived names.

class Rva001EB456
{
public:
	void rva001EB456(int a, int b);
};
class Rva001EB6FE
{
public:
	void rva001EB6FE();
	void rva001EB68A();
private:
	char m_pad[0xC];
	int m_0C;
	char m_pad10[0xB2];
	char m_C2;
	char m_C3;
};

// ?rva001EB6FE@Rva001EB6FE@@QAEXXZ
void Rva001EB6FE::rva001EB6FE()
{
	if (m_C2) {
		if (!m_C3) {
			++m_0C;
			m_C3 = 1;
		}
		((Rva001EB456 *)this)->rva001EB456(1, 1);
	}
}

// ?rva001EB68A@Rva001EB6FE@@QAEXXZ
void Rva001EB6FE::rva001EB68A()
{
	if (!m_C3) {
		++m_0C;
		m_C3 = 1;
	}
	((Rva001EB456 *)this)->rva001EB456(0, 1);
}
