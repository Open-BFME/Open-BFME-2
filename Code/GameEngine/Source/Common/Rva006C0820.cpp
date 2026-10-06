// cl: /MD
// ?rva006C0820@Rva006C0820@@QAEXXZ @ 0x006C0820 8B.
// Tail jmp to just-landed 0x006C0DA0: loads member pointer at +0x10 then jumps.
// Evidence: chain from 0x006C0DA0 landing; callers at 0x00073BE8 0x0007444C
// 0x0023F682 0x00246D8C; neighbours 0x006C07D0 and 0x006C0990.
class Rva006C0DA0
{
public:
	void rva006C0DA0();
};
class Rva006C0820
{
public:
	void rva006C0820();
private:
	char m_pad[0x10];
	Rva006C0DA0 *m_ptr;
};
void Rva006C0820::rva006C0820()
{
	m_ptr->rva006C0DA0();
}
