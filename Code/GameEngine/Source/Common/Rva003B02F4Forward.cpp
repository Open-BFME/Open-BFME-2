// cl: /O1 /MD /G7
// ?rva003B02F4@Rva003B02F4@@QAEXXZ @0x003B02F4 26B: forwards the three members
// to the pinned 0x003B02A1 static, then backs the +4 member down by 0xc.
// Evidence: byte member at +0xc widens through al (mov al/push eax, not a
// dword push), ret with all pushes cleaned inline (thiscall, no args).
void rva003B02A1(int a1, int a2, char a3);

class Rva003B02F4
{
public:
	void rva003B02F4(void);

private:
	int m_00;
	int m_04;
	char m_pad08[4];
	char m_0c;
};

void Rva003B02F4::rva003B02F4(void)
{
	rva003B02A1(m_00, m_04, m_0c);
	m_04 -= 0xc;
}
