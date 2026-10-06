// cl: /DNDEBUG /MD
// ?rva00255CA8@Rva00255CA8@@QAEXXZ @0x00255CA8 41B.
// Chain from 0x00254D38: if +4 is 0 return else free list at [inner+4] via
// rowed Rva00254D38::rva00254D38 then reset inner +8 to self plus +4 to 0
// plus +0xC to self and +4 to 0. Callers at 0x0025643E plus 0x00256E6C.
// __thiscall method. Neighbour flags /O1.
struct Rva00254D38Node;
class Rva00254D38
{
public:
	void rva00254D38(Rva00254D38Node *head);
};
struct Rva00255CA8Inner
{
	void *m_00;
	Rva00254D38Node *m_04;
	void *m_08;
	void *m_0C;
};
class Rva00255CA8
{
public:
	void rva00255CA8();
private:
	Rva00255CA8Inner *m_00;
	int m_04;
};
void Rva00255CA8::rva00255CA8()
{
	if (m_04 == 0)
		return;
	((Rva00254D38 *)this)->rva00254D38(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0C = m_00;
	m_04 = 0;
}
