// cl: /MD
// ?rva00448E3B@Rva00448E3B@@QAEXXZ retail 0x00448E3B 41B
// Clear resetting header self-links and count: if m_04==0 return; free walk
// root m_00->m_04 via rowed 0x00448D96 with same this; m_00->m_08=m_00;
// m_00->m_04=0; m_00->m_0c=m_00; m_04=0. Evidence: cmp je push call mov mov
// and mov and sequence; unblocks 0x00448FA6; chain from free walk.
class Rva00448089
{
public:
	~Rva00448089();
};
struct Rva00448D96Node
{
	int m_00;
	int m_04;
	Rva00448D96Node *m_08;
	Rva00448D96Node *m_0c;
	Rva00448089 m_10;
};
class Rva00448D96
{
public:
	void rva00448D96(Rva00448D96Node *node);
};
struct Rva00448E3BHeader
{
	int m_00;
	Rva00448D96Node *m_04;
	Rva00448E3BHeader *m_08;
	Rva00448E3BHeader *m_0c;
};
class Rva00448E3B : public Rva00448D96
{
public:
	void rva00448E3B();
private:
	Rva00448E3BHeader *m_00;
	int m_04;
};
void Rva00448E3B::rva00448E3B()
{
	if (m_04 == 0)
		return;
	rva00448D96(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0c = m_00;
	m_04 = 0;
}
