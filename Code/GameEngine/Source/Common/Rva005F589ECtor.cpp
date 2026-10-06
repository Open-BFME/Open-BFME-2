// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD
// ??0Rva005F589E@@QAE@HPAX@Z, retail 0x005F589E (174B).
// Button ctor same 174B shape as sibling 0x005F5C77: three-base object (Base0 at +0
// with int at +4, image holder at +8 built by pinned 0x005E1680 from a "button"
// AsciiString temporary, listener at +0x1C), int/List* at +0x20/+0x24 from the
// input struct, image looked up through the Rva005E16DA global at 0x00E068EC
// via rowed 0x005E16B9 and unlocked via rowed 0x005E1158, listener registered
// through rowed append 0x005A0B4C. Evidence: EH_prolog cookie 0xBA5425; vtables
// 0x00C79570/0x00C79550/0x00C79544; caller at 0x005E5D27; prev 0x005F5882 next 0x005F594C.
// Reuses Rva005F5C77Base0/Rva005F5C77Holder names to call the existing pin at 0x005E1680.
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

struct Rva005F589EIn
{
	void *m_00;
	int m_04;
	Rva005A0B4CList *m_08;
};

struct Rva005E16DA;

extern Rva005E16DA g_00E068EC;

class Rva005F589E : public Rva005F5C77Base0, public Rva005F5C77Holder, public Rva005E4AE2Listener
{
public:
	Rva005F589E(int a1, void *a2);
	virtual ~Rva005F589E();
private:
	int m_20;
	Rva005A0B4CList *m_24;
};

Rva005F589E::Rva005F589E(int a1, void *a2raw)
	: Rva005F5C77Base0()
	, Rva005F5C77Holder((void *)a1, AsciiString("button"), ((Rva005F589EIn *)a2raw)->m_00)
	, Rva005E4AE2Listener()
{
	Rva005F589EIn *a2 = (Rva005F589EIn *)a2raw;
	m_20 = a2->m_04;
	m_24 = a2->m_08;
	const Image *img = ((Rva005E16B9 *)&g_00E068EC)->rva005E16B9();
	((Rva005E1158 *)this)->rva005E1158(img);
	m_24->append((Rva002BA8F1Listener *)static_cast<Rva005E4AE2Listener *>(this));
}
