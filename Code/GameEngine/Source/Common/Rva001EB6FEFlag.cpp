// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: lazy flag init at 0x1EB6FE (36B). When +0xC2 is set
// and +0xC3 is clear, bumps +0xC and sets +0xC3, then runs 0x1EB456(1,1).
// Address-derived names.

class Rva001EB456
{
public:
	void rva001EB456(int a, int b);
};
class Rva001EB6FE
{
public:
	void rva001EB6FE();
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
