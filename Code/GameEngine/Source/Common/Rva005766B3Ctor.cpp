// cl: /MD
// ??0Rva005766B3@@QAE@HHH@Z @0x005766B3 32B: ctor stores 3 args at +4/+8/+0xC plus vtable 0x0086E7D0 at +0. Evidence: retail mov stores plus vtable imm plus ret 12 plus caller at 0x00576778; prev Disp0DwordImmSetters next Rva0057702EClear.
class Rva005766B3
{
public:
	virtual ~Rva005766B3();
	Rva005766B3(int a, int b, int c);
private:
	int m_4;
	int m_8;
	int m_c;
};
Rva005766B3::Rva005766B3(int a, int b, int c)
	: m_4(a), m_8(b), m_c(c)
{
}
