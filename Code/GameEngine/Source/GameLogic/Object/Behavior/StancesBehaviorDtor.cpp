// cl: /DNDEBUG /MD /EHs
// ??1StancesBehavior@@UAE@XZ retail 0x0045F001 103B
// Own vptrs C424DC (+0), BEFF90 (+0xC) and C424D0 (+0x10); under EH state 1
// the listener list at +0x20 broadcasts this object through the rowed forEach
// 0x0045EF37 with a member-function pointer to the slot-0 forwarder 0x001FF3A9;
// the list's inline dtor frees its block through the rowed CRT free, then the
// rowed first-base dtor ??1UpdateModule@@UAE@XZ 0x0024A797 runs. The two
// secondary bases are interface views without destructors (no restores).
// Same recipe as Rva005C9B76Dtor.cpp; TU-local view of the class.

extern "C" void __cdecl free(void *);

class Rva0045EF37Listener
{
public:
	virtual void notify(void *);
};

class Rva0045EF37List
{
public:
	void forEach(void (Rva0045EF37Listener::*notify)(void *), void *arg);
	~Rva0045EF37List() throw()
	{
		if (m_begin)
			free(m_begin);
	}
	Rva0045EF37Listener **m_begin;
	Rva0045EF37Listener **m_end;
	Rva0045EF37Listener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
private:
	char m_pad04[8];
};

class StancesBehaviorInterfaceA
{
public:
	virtual void stancesInterfaceA() = 0;
};

class StancesBehaviorInterfaceB
{
public:
	virtual void stancesInterfaceB() = 0;
};

class StancesBehavior : public UpdateModule, public StancesBehaviorInterfaceA, public StancesBehaviorInterfaceB
{
public:
	virtual ~StancesBehavior();
	virtual void stancesInterfaceA();
	virtual void stancesInterfaceB();
private:
	char m_pad14[0x20 - 0x14];
	Rva0045EF37List m_listeners; // +0x20
	int m_30;
};

StancesBehavior::~StancesBehavior()
{
	m_listeners.forEach((void (Rva0045EF37Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
}
