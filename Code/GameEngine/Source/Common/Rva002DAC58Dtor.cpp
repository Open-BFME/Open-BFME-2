// cl: /MD /EHsc
// ??1Rva002DAC58@@UAE@XZ @0x002DAC58 128B: dtor with two node lists plus GameEngineDeletingBase.
// Evidence: vptr 0x00C03D64 store, lists at +0xC/+0x10 with virtual slot0 get(0) plus global delete row 0x2FD60, base dtor row 0x1B4E74, deleting dtor caller 0x002DACD8 28B, neighbour Rva002DB311Dtor /O1 /MD /EHsc.

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

struct Rva002DAC58Node
{
	virtual void *get(int v);
	char m_pad04[0xC];
	Rva002DAC58Node *m_next;
};

class Rva002DAC58 : public GameEngineDeletingBase
{
public:
	virtual ~Rva002DAC58();
private:
	Rva002DAC58Node *m_list0C;
	Rva002DAC58Node *m_list10;
};

Rva002DAC58::~Rva002DAC58()
{
	while (m_list0C)
	{
		Rva002DAC58Node *next = m_list0C->m_next;
		void *p = m_list0C ? m_list0C->get(0) : 0;
		::operator delete(p);
		m_list0C = next;
	}
	while (m_list10)
	{
		Rva002DAC58Node *next = m_list10->m_next;
		void *p = m_list10 ? m_list10->get(0) : 0;
		::operator delete(p);
		m_list10 = next;
	}
}
