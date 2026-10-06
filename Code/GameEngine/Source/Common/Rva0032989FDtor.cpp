// cl: /O1 /MD /EHsc
// ??1Rva0032989F@@UAE@XZ retail 0x0032989F 103B
// Own vptr C0D8FC; under EH state 0 each of the m_count (+0x68) pointers in
// the array at +0x18 is deleted through its slot-0 deleting dtor with flag 0
// and the global ??3@YAXPAX@Z (a global-scope delete); then the base's inline
// dtor restores BC9574 and hands its id (+8) back to its owner (+4) through
// the rowed ?handle@Q1Forwardee0000871A@@QAEXH@Z 0x00306D7B.
// Names address-derived.

class Q1Forwardee0000871A
{
public:
	void handle(int id);
};

class Rva0032989FBase
{
public:
	virtual ~Rva0032989FBase()
	{
		m_owner->handle(m_id);
	}

protected:
	Q1Forwardee0000871A *m_owner; // +0x04
	int m_id; // +0x08
};

class Rva0032989FItem
{
public:
	virtual ~Rva0032989FItem();
};

class Rva0032989F : public Rva0032989FBase
{
public:
	virtual ~Rva0032989F();

private:
	unsigned char m_pad0C[0x18 - 0x0C];
	Rva0032989FItem *m_items[20]; // +0x18
	int m_count; // +0x68
};

Rva0032989F::~Rva0032989F()
{
	for (int i = 0; i < m_count; ++i)
		::delete m_items[i];
}
