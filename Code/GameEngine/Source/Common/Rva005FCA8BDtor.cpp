// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005FCA8B@@QAE@XZ retail 0x005FCA8B 89B
// Non-virtual dtor: under EH state 2 the owner at +0 broadcasts itself to the
// listener list at its +8 through the rowed forEach 0x005FCA6D with a vcall
// member-function pointer to listener slot +0x0C (folded thunk 0x005CB265);
// then member dtors -- vector wrappers +0x1C +0x10 (rowed 0x005242D7
// 0x0052413E) and AsciiString +0xC (releaseBuffer 0x00036410). The list view
// is the one in Rva005FCA00ListenerWalks.cpp. Names address-derived.
#include "ascii_string.h"

class Rva005FCA6DListener
{
public:
	virtual void notify(void *);
	virtual void slot1(void *);
	virtual void slot2(void *);
	virtual void slot3(void *);
};

class Rva005FCA6DList
{
public:
	void forEach(void (Rva005FCA6DListener::*notify)(void *), void *arg);

private:
	Rva005FCA6DListener **m_begin;
	Rva005FCA6DListener **m_end;
	Rva005FCA6DListener **m_capacity;
	unsigned int m_index;
};

struct Rva005FCA8BOwner
{
	char m_pad[8];
	Rva005FCA6DList m_list; // +0x08
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva005FCA8B
{
public:
	~Rva005FCA8B();
private:
	Rva005FCA8BOwner *m_owner; // +0x00
	char m_pad04[8];
	AsciiString m_0C;
	Rva0052413E m_10;
	Rva005242D7 m_1C;
};

Rva005FCA8B::~Rva005FCA8B()
{
	m_owner->m_list.forEach(&Rva005FCA6DListener::slot3, m_owner);
}
