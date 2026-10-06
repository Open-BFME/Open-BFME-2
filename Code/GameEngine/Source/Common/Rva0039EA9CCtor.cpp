// cl: /DNDEBUG /MD
// ??0Rva0039EA9C@@QAE@XZ @0x0039EA9C 27B, call sites 0x0059A388 0x0059A689
// 0x005A9FDF. Six-dword record: zeros, 1 at +0x08, -1 at +0x14.
// Structural inference: retail stores the -1 last (or dword [+0x14], -1
// after the zero and 1 stores) even though plain int initialisers schedule
// it first; a +0x14 member sub-object with its own inline -1 constructor
// gives exactly that order.
struct Rva0039EA9CHandle
{
	int m_value;
	Rva0039EA9CHandle() : m_value(-1) {}
};

class Rva0039EA9C
{
public:
	Rva0039EA9C();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	Rva0039EA9CHandle m_14;
};
Rva0039EA9C::Rva0039EA9C() : m_00(0), m_04(0), m_08(1), m_0c(0), m_10(0)
{
}
