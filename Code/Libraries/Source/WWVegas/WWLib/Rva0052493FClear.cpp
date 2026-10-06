// cl: /MD
// ?rva0052493F@Rva0052493F@@QAEXXZ @0x0052493F 52B
// Evidence: chain via rowed 0x00523F22 0x00523F57 0x00523F8C 0x00523FEC 0x00524021 0x00524056; six Rva00524021 subobject clears at +4 +10 +1C +34 +40 +4C with tail-jmp on last; callers 0x0043DEC1 0x0051E4F0 0x0057EFAF etc.
class Rva00524021
{
public:
	void rva00523F22();
	void rva00523F57();
	void rva00523F8C();
	void rva00523FEC();
	void rva00524021();
	void rva00524056();
private:
	char m_data[8];
};

class Rva0052493F
{
public:
	void rva0052493F();
private:
	char m_pad0[4];
	Rva00524021 m_04;
	char m_pad0C[4];
	Rva00524021 m_10;
	char m_pad18[4];
	Rva00524021 m_1C;
	char m_pad24[16];
	Rva00524021 m_34;
	char m_pad3C[4];
	Rva00524021 m_40;
	char m_pad48[4];
	Rva00524021 m_4C;
};

void Rva0052493F::rva0052493F()
{
	m_04.rva00523F22();
	m_10.rva00523F57();
	m_1C.rva00523F8C();
	m_34.rva00523FEC();
	m_40.rva00524021();
	m_4C.rva00524056();
}
