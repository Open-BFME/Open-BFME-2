// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0030C1FCOwner@@UAE@XZ, retail 0x0030C40A..0x0030C4A6 (156 bytes,
// EH): the base-object destructor of the owner whose broadcast slots
// Rva0030C1FCNotifiers.cpp rows; sibling of Rva0030CAA9OwnerDtor.cpp. It
// installs its tables (0x00C088FC at +0, 0x00C088E0 on the shared virtual
// base behind its vtordisp), tells every listener through slot 0 (the
// generic vcall thunk), and then its parts die: the +0x68 buffer
// (GameFree), the four AsciiStrings at +0x40 (eh vector destructor
// iterator), the listener list -- a second base at +0x30, as retail's
// null-checked unwind conversion shows -- and the primary base (destructor
// body 0x00538133, pinned under the same virtual-dtor view). The unwind
// funclets reach the list and buffer destructors through the shared
// free-first-pointer body 0x0007FAB3. The virtual base sits at +0x90.
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

class Rva0030C1FCOwner;

class Rva0030C1FCListener
{
public:
	virtual void notify00(Rva0030C1FCOwner *owner);
};

class Rva0030C185List
{
public:
	~Rva0030C185List() { if (m_begin) Rva00030830GameFree(m_begin); }
	void forEach(void (Rva0030C1FCListener::*notify)(Rva0030C1FCOwner *), Rva0030C1FCOwner *owner);
private:
	Rva0030C1FCListener **m_begin;
	Rva0030C1FCListener **m_end;
	Rva0030C1FCListener **m_capacity;
	unsigned int m_index;
};

struct Rva0030C40ABuffer
{
	~Rva0030C40ABuffer() { if (m_data) Rva00030830GameFree(m_data); }
	void *m_data;
};

class Rva0030C1FCOwner : public Rva0053805DBase, public Rva0030C185List
{
public:
	virtual ~Rva0030C1FCOwner();
	virtual void s0();
private:
	AsciiString m_records[4];		// +0x40
	unsigned char m_pad50[0x68 - 0x50];
	Rva0030C40ABuffer m_buffer68;		// +0x68
	unsigned char m_pad6C[0x8C - 0x6C];
};

Rva0030C1FCOwner::~Rva0030C1FCOwner()
{
	forEach(&Rva0030C1FCListener::notify00, this);
}
