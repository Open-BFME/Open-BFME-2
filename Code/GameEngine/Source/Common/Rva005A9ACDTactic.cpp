// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "SiegeGates" skirmish-AI tactic (vtable 0x00871E28; ctor 0x005A9C1E in
// Rva004ECECDTacticCtors.cpp, dtor 0x005A9ACD and ??_G in
// Rva005DC87BDerived.cpp, slot 9 in Rva004ECECDTacticCreate.cpp). Base chain,
// all address-derived: Rva005DC87B (ctor 0x005DC85F, +0x58 object id) over
// Rva005DC73C (ctor 0x005DC722) over the AITactic.cpp object Rva004ECECD.
//
//   0x005A9AD8  slot 1: the owner's TheSkirmishAIManager record answers
//               0x002C6ACB, the base test passes, the request carries no
//               +0x04, and the 0x005DC8A2 search finds nothing
//   0x005A9CA3  slot 3: set bit 5 of the unit's +0x30C flags
//   0x005A9BF2  slot 5: xfer, version 1, then the base's
//   0x005A9B61  slot 6: with a team, attack (0x005A9B20); otherwise stop
//   0x005A9B82  slot 7: while running: no team stops; before the gate is
//               reached (+0x5C) move to the +0x20 record's point once
//               0x005DC93B allows it, or attack when 0x005DCAF4 or
//               0x004ED169 says so; afterwards stop (1, 0) on 0x004ED169
//   0x005A9B20  attack the base's target (0x005DCAE5) when 0x005DC9C8 has one
#include "ascii_string.h"

class Object;
class Team;
class Snapshot;
class Xfer
{
public:
	class Version;
	virtual ~Xfer();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void v9();
	virtual Xfer &operator==(Version &value);
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

struct Rva005A9ACDRecord
{
	char m_pad00[0x0C];
	char m_point0C[0x0C];	// +0x0C
};

struct Rva002A8AB1Record
{
	void *rva002C6ACB();
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

struct Rva005A9ACDRequest
{
	char m_pad00[4];
	void *m_04;		// +0x04
};

struct Rva005A9ACDUnit
{
	char m_pad000[0x30C];
	unsigned int m_30C;	// +0x30C
};

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual bool appliesTo(void *request);
	virtual void v2();
	virtual bool v3(Rva005A9ACDUnit *unit, void *unused);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual Rva004ECECD *create();
	Team *rva004ECECD(int index);
	unsigned char rva004ED169();
	void rva004ED1A1(int a, Object *target);
	void rva004ED342(void *point);
	void rva004ED748(int a, int b);
};

class Rva005DC73C : public Rva004ECECD
{
public:
	virtual ~Rva005DC73C();
	unsigned char rva005DC763(void *request);
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x20 - 0x11];
	Rva005A9ACDRecord *m_record;	// +0x20
	void *m_owner;			// +0x24
	char m_pad28[0x58 - 0x28];
};

class Rva005DC87B : public Rva005DC73C
{
public:
	virtual ~Rva005DC87B();
	virtual void xfer(Xfer *xfer);
	bool rva005DC8A2();
	bool rva005DC93B();
	bool rva005DC9C8();
	Object *rva005DCAE5();
	bool rva005DCAF4();
	int m_58;
};

class Rva005A9ACD : public Rva005DC87B
{
public:
	virtual ~Rva005A9ACD();
	virtual bool appliesTo(void *request);
	virtual bool v3(Rva005A9ACDUnit *unit, void *unused);
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void v7();
	bool rva005A9B20();
private:
	bool m_reached;		// +0x5C
};

bool Rva005A9ACD::appliesTo(void *request)
{
	if (g_00DFEEF8->rva002A8AB1(m_owner)->rva002C6ACB()
		&& rva005DC763(request)
		&& !((Rva005A9ACDRequest *)request)->m_04)
		return !rva005DC8A2();
	return false;
}

bool Rva005A9ACD::rva005A9B20()
{
	if (rva005DC9C8()) {
		rva004ED1A1(0, rva005DCAE5());
		return true;
	}
	return false;
}

void Rva005A9ACD::v6()
{
	if (rva004ECECD(0))
		rva005A9B20();
	else
		rva004ED748(0, 0);
}

void Rva005A9ACD::v7()
{
	if (!m_running)
		return;
	if (!rva004ECECD(0)) {
		rva004ED748(0, 0);
		return;
	}
	if (!m_reached) {
		if (rva005DC93B()) {
			rva004ED342(m_record->m_point0C);
			m_reached = true;
		} else if (rva005DCAF4() || rva004ED169()) {
			rva005A9B20();
		}
	} else if (rva004ED169()) {
		rva004ED748(1, 0);
	}
}

bool Rva005A9ACD::v3(Rva005A9ACDUnit *unit, void *)
{
	unit->m_30C |= 0x20;
	return true;
}

void Rva005A9ACD::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	Rva005DC87B::xfer(xfer);
}
