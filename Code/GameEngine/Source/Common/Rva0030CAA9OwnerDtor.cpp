// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0030CAA9Owner@@UAE@XZ, retail 0x0030CDCA..0x0030CE66 (156 bytes,
// EH): the base-object destructor of the owner whose broadcast slots
// Rva0030CAA9Notifiers.cpp rows (pinned at the opaque scalar deleting
// destructor as ??1Rva0030CDCA). It installs its tables (0x00C089A8 at +0,
// 0x00C08974 at +0x30, 0x00C08958 on the shared virtual base behind its
// vtordisp), tells every listener through slot 0 (the generic vcall thunk),
// and then its members and bases die: the +0x9C AsciiString, the listener
// storage (GameFree), the secondary base (rowed Rva002E3E51 destructor) and
// the primary base (destructor body 0x00538133, pinned under this view).
// Layout: primary base with its vbptr at +0x18, secondary base at +0x30
// (vbptr +0x34), the listener list as a third base at +0x68 (retail's
// null-checked unwind conversion; its funclet reaches the shared
// free-first-pointer body 0x0007FAB3), the virtual base at +0xA8.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

class VBase00C6EE28
{
public:
	virtual void s0();
};

class Rva00538133Root
{
public:
	virtual void s1();
private:
	unsigned char m_pad04[0x18 - 4];
};

class Rva0053805DBase : public Rva00538133Root, public virtual VBase00C6EE28
{
public:
	virtual ~Rva0053805DBase();
	virtual void s0();
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Rva002E3E51 : public virtual VBase00C6EE28
{
public:
	virtual ~Rva002E3E51();
	virtual void s0();
private:
	void *m_08;
	unsigned char m_pad0C[0x38 - 0x0C];
};

class Rva0030CAA9Owner;

class Rva0030CAA9Listener
{
public:
	virtual void notify00(Rva0030CAA9Owner *owner);
};

class Rva0030CA8BList
{
public:
	~Rva0030CA8BList() { if (m_begin) Rva00030830GameFree(m_begin); }
	void forEach(void (Rva0030CAA9Listener::*notify)(Rva0030CAA9Owner *), Rva0030CAA9Owner *owner);
private:
	Rva0030CAA9Listener **m_begin;
	Rva0030CAA9Listener **m_end;
	Rva0030CAA9Listener **m_capacity;
	unsigned int m_index;
};

class Rva0030CAA9Owner : public Rva0053805DBase, public Rva002E3E51, public Rva0030CA8BList
{
public:
	virtual ~Rva0030CAA9Owner();
	virtual void s0();
private:
	unsigned char m_pad78[0x9C - 0x78];
	AsciiString m_name9C;			// +0x9C
	int m_A0;
};

Rva0030CAA9Owner::~Rva0030CAA9Owner()
{
	forEach(&Rva0030CAA9Listener::notify00, this);
}
