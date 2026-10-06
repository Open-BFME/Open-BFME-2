// cl: /DNDEBUG /MD /EHsc
// ?rva004FA992@Rva004FA992@@QAEXP8Rva004FA953Listener@@AEXPAXH@Z0H@Z @0x004FA992 31B unlock: forward 3 args to member list at +4 then tail to global g_00E044F0; unblocks 0x004FAEAA 0x004FAA81; callee forEach 0x004FA953

class Rva004FA953Listener
{
public:
	virtual void notify(void *, int);
};

class Rva004FA953List
{
public:
	void forEach(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value);
};

extern Rva004FA953List g_00E044F0;

class Rva004FA992
{
public:
	void rva004FA992(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value);

private:
	char m_pad0[4];
	Rva004FA953List m_list;
};

void Rva004FA992::rva004FA992(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value)
{
	m_list.forEach(notify, arg, value);
	g_00E044F0.forEach(notify, arg, value);
}
