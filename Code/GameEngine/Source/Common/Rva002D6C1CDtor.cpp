// cl: /MD /EHsc
// ??1Rva002D6C1C@@UAE@XZ retail 0x002D6C1C 93B
// Own vptr C0331C; under EH state 0 the singly linked list at +0xC (next at
// +4 of each node) is drained, each node deleted through its slot-0 deleting
// dtor with flag 0 and the global ??3@YAXPAX@Z (a global-scope delete); then
// the rowed base dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74.
// Names address-derived.

class Rva002D6C1CNode
{
public:
	virtual ~Rva002D6C1CNode();

	Rva002D6C1CNode *m_next; // +0x04
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva002D6C1C : public GameEngineDeletingBase
{
public:
	virtual ~Rva002D6C1C();

private:
	Rva002D6C1CNode *m_head; // +0x0C
};

Rva002D6C1C::~Rva002D6C1C()
{
	while (m_head)
	{
		Rva002D6C1CNode *next = m_head->m_next;
		::delete m_head;
		m_head = next;
	}
}
