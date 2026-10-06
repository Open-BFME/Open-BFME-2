// cl: /DNDEBUG /MD /EHsc
// ?rva004FA978@Rva004FA978@@QAEXP8Rva004FA935Listener@@AEXPAX@Z0@Z @0x004FA978 26B leaf: forward same args to member list at +4 then tail to global g_00E044F0; callers 0x004FB1C6; callee forEach 0x004FA935

class Rva004FA935Listener
{
public:
	virtual void notify(void *);
};

class Rva004FA935List
{
public:
	void forEach(void (Rva004FA935Listener::*notify)(void *), void *arg);
};

extern Rva004FA935List g_00E044F0;

class Rva004FA978
{
public:
	void rva004FA978(void (Rva004FA935Listener::*notify)(void *), void *arg);

private:
	char m_pad0[4];
	Rva004FA935List m_list;
};

void Rva004FA978::rva004FA978(void (Rva004FA935Listener::*notify)(void *), void *arg)
{
	m_list.forEach(notify, arg);
	g_00E044F0.forEach(notify, arg);
}
