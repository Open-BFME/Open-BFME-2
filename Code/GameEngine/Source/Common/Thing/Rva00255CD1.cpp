// cl: /DNDEBUG /MD
// ?rva00255CD1@Rva00255CD1@@QAEXXZ @0x00255CD1 41B.
// Twin of 0x00255CA8 but via rowed Rva00254D0B::rva00254D0B: if +4 is 0
// return else free list at [inner+4] then reset inner +8 to self plus +4
// to 0 plus +0xC to self and +4 to 0. Caller at 0x00256476.
// __thiscall method. Neighbour flags /O1.
struct Rva00254D0BNode;
class Rva00254D0B
{
public:
	void rva00254D0B(Rva00254D0BNode *head);
};
struct Rva00255CD1Inner
{
	void *m_00;
	Rva00254D0BNode *m_04;
	void *m_08;
	void *m_0C;
};
class Rva00255CD1
{
public:
	void rva00255CD1();
private:
	Rva00255CD1Inner *m_00;
	int m_04;
};
void Rva00255CD1::rva00255CD1()
{
	if (m_04 == 0)
		return;
	((Rva00254D0B *)this)->rva00254D0B(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0C = m_00;
	m_04 = 0;
}
