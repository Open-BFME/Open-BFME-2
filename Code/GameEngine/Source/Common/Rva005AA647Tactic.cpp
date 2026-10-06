// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "SimpleAttack" skirmish-AI tactic (vtable 0x00871F80; its destructor
// 0x005AA647 and ??_G are rowed in Rva005DC73CDerived.cpp). One of the
// prototypes the Rva00506909 generator seeds its +0x04 pool with
// (0x00505E5D news 0x58 bytes and runs the ctor below), and slot 9 clones
// it. Base chain, all address-derived: Rva005DC73C (ctor 0x005DC722, dtor
// 0x005DC73C) over the AITactic.cpp object Rva004ECECD.
//
//   0x005AA6B4  ctor: base ctor with the tactic name
//   0x005AA652  slot 1: the base's applicability test as bool
//   0x005AA663  slot 6: 0x004ED342 with the +0x20 record's +0x0C point
//   0x005AA670  slot 7: while running (+0x10), stop (0x004ED748(1, 0)) when
//               0x004ED169 says so or the +0x20 record is flagged at +0x18
//   0x005AA703  slot 9: a fresh SimpleAttack tactic
#include "ascii_string.h"

struct Rva005AA647Record
{
	char m_pad00[0x0C];
	char m_point0C[0x0C];	// +0x0C
	bool m_18;		// +0x18
};

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual bool appliesTo(void *request);
	virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual Rva004ECECD *create();
	unsigned char rva004ED169();
	void rva004ED342(void *point);
	void rva004ED748(int a, int b);
};

class Rva005DC73C : public Rva004ECECD
{
public:
	Rva005DC73C(const AsciiString &name);
	virtual ~Rva005DC73C();
	unsigned char rva005DC763(void *request);
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x20 - 0x11];
	Rva005AA647Record *m_record;	// +0x20
	char m_pad24[0x58 - 0x24];
};

class Rva005AA647 : public Rva005DC73C
{
public:
	Rva005AA647();
	virtual ~Rva005AA647();
	virtual bool appliesTo(void *request);
	virtual void v6();
	virtual void v7();
	virtual Rva004ECECD *create();
};

Rva005AA647::Rva005AA647()
	: Rva005DC73C(AsciiString("SimpleAttack"))
{
}

bool Rva005AA647::appliesTo(void *request)
{
	return rva005DC763(request) ? true : false;
}

void Rva005AA647::v6()
{
	rva004ED342(m_record->m_point0C);
}

void Rva005AA647::v7()
{
	if (m_running && (rva004ED169() || m_record->m_18))
		rva004ED748(1, 0);
}

Rva004ECECD *Rva005AA647::create()
{
	return new Rva005AA647;
}
