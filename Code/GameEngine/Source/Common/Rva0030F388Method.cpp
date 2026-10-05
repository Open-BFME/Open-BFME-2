// cl: /O1 /MD
// ?rva0030F388@Rva0030F388@@QAEXXZ @ 0x0030F388 29B: guarded listener-list broadcast with flag at +0x1c
// Evidence: rowed forEach 0x0030F34D in Rva0030F2E0ListenerWalks.cpp; pushed code 0x001FF3A9 slot-0 forwarder as listener notify; list at +4 and flag at +0x1c shared with caller 0x0030F3BF (vtable slot 1 of Rva0030F42E class); unblocks 0x0030F3BF.
class Rva0030F34DListener
{
public:
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
	void rva0030F388();
private:
	char m_00[4];
	Rva0030F34DList m_list;
	char m_pad14[8];
	bool m_flag;
};

void Rva0030F388::rva0030F388()
{
	if (!m_flag)
		return;
	m_list.forEach(&Rva0030F34DListener::notify, this);
	m_flag = false;
}
