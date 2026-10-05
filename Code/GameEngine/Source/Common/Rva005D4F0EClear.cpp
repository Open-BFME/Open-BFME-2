// cl: /O1 /MD
// ?rva005D4F0E@Rva005D4F0E@@QAEXXZ @0x005D4F0E 25B
// Triple clear: this+0 via rowed 0x0057C2CC then this+0xC via rowed 0x005D4E8B then tail jmp to rowed clear 0x002BED91 at this+8.
// Evidence: callees all rowed; callers at 0x005D5012 and jmp at 0x005D4F7F; unblocks 0x005D4F7D.
class Rva0057C2CC
{
public:
	void rva0057C2CC();
	char m_pad[8];
};
class Rva002BED91
{
public:
	void clear();
	void *m_ptr;
};
class Rva005D4E8B
{
public:
	void rva005D4E8B();
	void *m_ptr;
};
class Rva005D4F0E
{
public:
	void rva005D4F0E();
private:
	Rva0057C2CC m_00;
	Rva002BED91 m_08;
	Rva005D4E8B m_0C;
};
void Rva005D4F0E::rva005D4F0E()
{
	m_00.rva0057C2CC();
	m_0C.rva005D4E8B();
	m_08.clear();
}
