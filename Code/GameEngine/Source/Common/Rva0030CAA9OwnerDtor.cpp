// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0030CAA9Owner@@UAE@XZ, retail 0x0030CDCA..0x0030CE66 (156 bytes,
// EH): the base-object destructor of the owner whose broadcast slots
// Rva0030CAA9Notifiers.cpp rows (pinned at the opaque scalar deleting
// destructor as ??1Rva0030CDCA). It installs its tables (0x00C089A8 at +0,
// 0x00C08974 at +0x30, 0x00C08958 on the shared virtual base behind its
// vtordisp), tells every listener through slot 0 (the generic vcall thunk),
// and then its members and bases die: the +0x9C AsciiString, the listener
// storage (GameFree), the secondary base (rowed Rva00330C50 destructor) and
// the primary base (destructor body 0x00538133, pinned under this view).
// Layout: primary base with its vbptr at +0x18, secondary base at +0x30
// (vbptr +0x34), the listener list as a third base at +0x68 (retail's
// null-checked unwind conversion; its funclet reaches the shared
// free-first-pointer body 0x0007FAB3), the virtual base at +0xA8.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../Include/Common/Rva0030B72CPoint.h"

// Native seven-slot polygon interface, as in Rva00330C50Ctor.cpp.
class Rva00330C50Interface {
public:
	~Rva00330C50Interface() {}
	virtual int slot0() const = 0;
	virtual Rva0030B72CPoint slot1(int index) const = 0;
	virtual int slot2() const = 0;
	virtual Region2D slot3() = 0;
	virtual float slot4() const = 0;
	virtual float slot5() const = 0;
	virtual Rva0030B72CPoint slot6() const = 0;
};

class Rva00538133Root
{
public:
	virtual ~Rva00538133Root();
private:
	unsigned char m_pad04[0x18 - 4];
};

class Rva0053805DBase : public Rva00538133Root, public virtual Rva00330C50Interface
{
public:
	virtual ~Rva0053805DBase();
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	virtual ~Rva00330C50();
	virtual int slot0() const;
	virtual Rva0030B72CPoint slot1(int index) const;
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
	virtual void primary1() = 0;
	virtual void primary2() = 0;
	virtual void primary3() = 0;
	virtual void primary4() = 0;
	virtual void primary5() = 0;
	virtual void primary6(int) = 0;
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

class Rva0030CAA9Owner : public Rva0053805DBase, public Rva00330C50, public Rva0030CA8BList
{
public:
	virtual ~Rva0030CAA9Owner();
private:
	unsigned char m_pad78[0x9C - 0x78];
	AsciiString m_name9C;			// +0x9C
	int m_A0;
};

Rva0030CAA9Owner::~Rva0030CAA9Owner()
{
	forEach(&Rva0030CAA9Listener::notify00, this);
}
