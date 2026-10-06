// cl: /MD
// ?rva004E8220@Rva004E8220@@QAEXH@Z @ 0x004E8220 (20B):
// Leaf thiscall setter. If the dword at +0x27C is 1 set it to 2; single
// unused int arg (ret 4). Evidence: reads ecx before writing it; caller at
// 0x004E8499; callees none.
class Rva004E8220
{
public:
	void rva004E8220(int);
private:
	unsigned char m_pad[0x27C];
	int m_val27C;
};

void Rva004E8220::rva004E8220(int)
{
	if (m_val27C == 1)
		m_val27C = 2;
}
