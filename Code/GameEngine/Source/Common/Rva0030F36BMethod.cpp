// cl: /MD
// ?rva0030F36B@Rva0030F388@@QAEXXZ @ 0x0030F36B 29B: guarded listener-list broadcast setting flag at +0x1c
// Evidence: rowed forEach 0x0030F34D in Rva0030F2E0ListenerWalks.cpp; pushed code 0x005CC208 slot-2 forwarder as listener notify; list at +4 and flag at +0x1c shared with 0x0030F388; unblocks 0x00086BC5.
class Rva0030F34DListener
{
public:
	virtual void dummy0(void *);
	virtual void dummy1(void *);
	virtual void notify(void *);
};

class Rva0030F34DList
{
public:
	void forEach(void (Rva0030F34DListener::*notify)(void *), void *arg);
private:
	Rva0030F34DListener **m_begin;
	Rva0030F34DListener **m_end;
	Rva0030F34DListener **m_capacity;
	unsigned int m_index;
};

class Rva0030F388
{
public:
	void rva0030F36B();
private:
	char m_00[4];
	Rva0030F34DList m_list;
	char m_pad14[8];
	bool m_flag;
};

void Rva0030F388::rva0030F36B()
{
	if (m_flag)
		return;
	m_list.forEach(&Rva0030F34DListener::notify, this);
	m_flag = true;
}
