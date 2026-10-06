// cl: /DNDEBUG /MD
//
// ?rva00318E8C@Rva00318E8C@@QAEXPAURva00318E8COut@@@Z, retail 0x00318E8C, 18 bytes.
// Copies float at +0x20 and dword at +0x24 to an 8-byte out struct.
// Callers are FUN_0071A372 at 0x0031A51E 0x0031A542 passing a stack out with
// this in edi plus FUN_009666C5. Identity beyond the two members is unproven
// so the name stays honest address-derived.

struct Rva00318E8COut
{
	float f;
	int i;
};

class Rva00318E8C
{
public:
	void rva00318E8C(Rva00318E8COut *out);
private:
	char m_pad[0x20];
	float m_20;
	int m_24;
};

void Rva00318E8C::rva00318E8C(Rva00318E8COut *out)
{
	out->f = m_20;
	out->i = m_24;
}
