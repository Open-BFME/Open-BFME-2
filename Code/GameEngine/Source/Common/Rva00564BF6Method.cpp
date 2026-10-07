// cl: /O1 /arch:SSE /G7 /Ob0
// ?rva00564BF6@Rva00564BF6@@QAEXPAURva00564BF6Out@@@Z @0x00564BF6 18B. Copies float at +0x10 and dword at +0x14 to out param. Callers at 0x00564F91 0x0056503D in 0x00564EC0. Honest address name: caller class unproven.
// TU-local honest-address views; offsets prove operations not type names.
struct Rva00564BF6Out
{
	float m_00;
	int m_04;
};

class Rva00564BF6
{
public:
	void rva00564BF6(Rva00564BF6Out *out);
private:
	char m_pad[0x10];
	float m_10;
	int m_14;
};

void Rva00564BF6::rva00564BF6(Rva00564BF6Out *out)
{
	out->m_00 = m_10;
	out->m_04 = m_14;
}
