// cl: /MD
//
// ?rva005FFB81@Rva005FFB81@@QAEXXZ @ 0x005FFB81 (8B).
// Forward to inner reset via pointer at +4 with tail jmp.
// Evidence: callee row 0x005FFB32; caller 0x006003AD 8B jmp;
// prev Rva005FFB32Method.cpp flags.
class Rva005FFB32
{
public:
	void rva005FFB32();
};

class Rva005FFB81
{
public:
	void rva005FFB81();
private:
	char m_pad[4];
	Rva005FFB32 *m_inner;
};

void Rva005FFB81::rva005FFB81()
{
	m_inner->rva005FFB32();
}
