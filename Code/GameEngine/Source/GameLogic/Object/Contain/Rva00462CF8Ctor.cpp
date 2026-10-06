// cl: /DNDEBUG /MD
//
// ??0Rva00462CF8@@QAE@XZ, retail 0x00462CF8, 16 bytes.
// Gap between 0x00462CE1 (SlaughterHordeContain slot 82) and 0x00462D62.
// Default ctor over the rowed Rva0024C7B3Member zeroing helper at 0x24C7B3
// (member at +0x00, 0x1C bytes) plus int at +0x1C cleared via and-idiom.
// Evidence: rowed callee plus and-zero plus no-caller gap. Honest address
// name: owning class identity unproven.

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

private:
	char m_bytes[0x1C];
};

class Rva00462CF8
{
public:
	Rva00462CF8();

private:
	Rva0024C7B3Member m_00;
	int m_1C;
};

Rva00462CF8::Rva00462CF8()
{
	m_1C = 0;
}
