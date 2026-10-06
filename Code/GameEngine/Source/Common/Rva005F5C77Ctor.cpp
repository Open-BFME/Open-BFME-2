// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD
// ??0Rva005F5C77@@QAE@PAXPAURva005F5C77In@@@Z @0x005F5C77 174B
// Button constructor sibling of 0x005F5F2B (same 174B shape, same callees,
// differing only in vtables and image global): three-base object (Base0 at +0
// with int at +4, image holder at +8 built by pinned 0x005E1680 from a "button"
// AsciiString temporary, listener at +0x1C), int/List* at +0x20/+0x24 from the
// input struct, image looked up through the Rva005E16DA global at 0x00E06900
// via rowed 0x005E16B9 and unlocked via rowed 0x005E1158, listener registered
// through rowed append 0x005A0B4C. Evidence: vtable 0x00C795B4 shared with the
// rowed dtor 0x005F5BF2; holder extent +8..+0x1B matches 0x005E1680 (vtable
// 0x00C779B4, arg words at +0xC/+0x10); the double [esi+0x1C] store is the
// inlined listener ctor plus this class's third vtable (three-base pattern per
// Rva005E4AE2Ctor.cpp); states 0/1/3/4 and __EH_prolog from the init-list
// temporary under /EHsc.
#include "ascii_string.h"

class Image;

class Rva005E0E1D
{
public:
	void rva005E0E1D(const Image *image);
};

class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
	virtual ~Rva005E1158();
private:
	int m_04;
	Rva005E0E1D *m_ptr08;
};

class Rva005E16B9
{
	char m_pad[8];
	AsciiString m_8;
public:
	const Image *rva005E16B9();
};

// The listener base's vptr is 0x00C79544, the listener vtable Rva005E4AE2Ctor.cpp
// names Rva005E4AE2Listener; Rva002BA8F1Listener's own vtable is 0x00C77F44
// (Rva0057605DCtor.cpp, vtbl_00C77F44), so the list's pointer type is only
// declared here and the base is cast to it, as Rva005E4AE2Ctor.cpp does.
struct Rva002BA8F1Listener;
struct Rva005E4AE2Listener
{
	Rva005E4AE2Listener() {}
	virtual ~Rva005E4AE2Listener();
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

struct Rva005F5C77Base0
{
	Rva005F5C77Base0() : m_04(0) {}
	virtual ~Rva005F5C77Base0() {}
	int m_04;
};

class Rva005F5C77Holder : public Rva005E1158
{
public:
	Rva005F5C77Holder(void *a1, const AsciiString &a2, void *a3);
	virtual ~Rva005F5C77Holder();
private:
	void *m_0C;
	int m_10;
};

struct Rva005F5C77In
{
	void *m_00;
	int m_04;
	Rva005A0B4CList *m_08;
};

struct Rva005E16DA;

extern Rva005E16DA g_rva00E06900;

class Rva005F5C77 : public Rva005F5C77Base0, public Rva005F5C77Holder, public Rva005E4AE2Listener
{
public:
	Rva005F5C77(void *a1, Rva005F5C77In *a2);
	virtual ~Rva005F5C77();
private:
	int m_20;
	Rva005A0B4CList *m_24;
};

Rva005F5C77::Rva005F5C77(void *a1, Rva005F5C77In *a2)
	: Rva005F5C77Base0()
	, Rva005F5C77Holder(a1, AsciiString("button"), a2->m_00)
	, Rva005E4AE2Listener()
{
	m_20 = a2->m_04;
	m_24 = a2->m_08;
	const Image *img = ((Rva005E16B9 *)&g_rva00E06900)->rva005E16B9();
	((Rva005E1158 *)this)->rva005E1158(img);
	m_24->append((Rva002BA8F1Listener *)static_cast<Rva005E4AE2Listener *>(this));
}
