// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small table-reached bodies from .text gaps no ledger row covers (seat-3
// batch J; see GapBodiesS3A.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a
// view of only the members it touches.

// 0x000B3FD0 is the one-byte empty body the toolchain folds many empties into.
#include "../../Include/Common/Rva000B3FD0.h"

// --- 0x005CFAD3 (19B): from a +0x08 interface, latch +0x0C (of the
// interface) when the second argument equals the +0x04 owner's +0x14 word.
struct Rva005CFAD3Owner
{
	char m_pad[0x14];
	int m_14;												// +0x14
};

class Rva005CFAD3Base0
{
public:
	virtual void b0();
	Rva005CFAD3Owner *m_owner;								// +0x04
};

class Rva005CFAD3Iface
{
public:
	virtual void rva005CFAD3(int a, int value, int c);
	int m_08;
	int m_0C;
	bool m_latched;											// +0x0C of the interface
};

class Rva005CFAD3 : public Rva005CFAD3Base0, public Rva005CFAD3Iface
{
public:
	virtual void rva005CFAD3(int a, int value, int c);
};

void Rva005CFAD3::rva005CFAD3(int, int value, int)
{
	if (value == m_owner->m_14)
		m_latched = true;
}

// --- 0x005E5575 (19B): run the +0x08 part's rowed 0x005E509F, then the
// (folded, empty) base hook.
class Rva005E508F
{
public:
	void rva005E509F();										// 0x005E509F
};

class Rva005E5575
{
public:
	virtual void rva005E5575();
private:
	int m_04;
	Rva005E508F m_part;										// +0x08
};

void Rva005E5575::rva005E5575()
{
	m_part.rva005E509F();
	((Rva000B3FD0 *)this)->rva000B3FD0();
}

// --- 0x003028F1 (22B): refresh the next record (stride 0x14, cursor +0x10)
// of the +0x0C array through the rowed 0x00302823.
class DataChunkInput;
struct DataChunkInfo;

class Rva00454200Element
{
public:
	bool refresh(DataChunkInput &file, DataChunkInfo *info);	// 0x00302823
	char m_pad[0x14];
};

class Rva003028F1
{
public:
	virtual bool rva003028F1(DataChunkInput &file, DataChunkInfo *info);
private:
	int m_04;
	int m_08;
	Rva00454200Element *m_records;							// +0x0C
	int m_cursor;											// +0x10
};

bool Rva003028F1::rva003028F1(DataChunkInput &file, DataChunkInfo *info)
{
	return m_records[m_cursor++].refresh(file, info);
}

// --- 0x005D0089 (11B): slot 1 of the +0x04 object's +0x1C member.
class Rva005D0089Target
{
public:
	virtual void s0();
	virtual void s1();
};

struct Rva005D0089Holder
{
	char m_pad[0x1C];
	Rva005D0089Target *m_target;							// +0x1C
};

class Rva005D0089
{
public:
	virtual void rva005D0089();
private:
	Rva005D0089Holder *m_holder;							// +0x04
};

void Rva005D0089::rva005D0089()
{
	m_holder->m_target->s1();
}

// --- 0x005DB204 (29B): 1 unless the +0xBC object's slot 10 reports set.
class Rva005DB204Target
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9();
	virtual bool s10();
};

class Rva005DB204
{
public:
	virtual bool rva005DB204();
private:
	char m_pad04[0xBC - 4];
	Rva005DB204Target *m_target;							// +0xBC
};

bool Rva005DB204::rva005DB204()
{
	if (m_target)
		return m_target->s10() == false;
	return true;
}

// --- 0x005D1362 (27B): the base snapshot's (folded, empty) DoXfer, then the
// rowed 0x005ED861 with the transfer.
class Xfer;

class FXParticleSystem
{
public:
	class EmissionVelocityInfo
	{
	public:
		virtual void DoXfer(Xfer &xfer);					// 0x0047A69C
	};
};

#include "../../Include/GameClient/Rva005ED976.h"

class Rva005D1362 : public FXParticleSystem::EmissionVelocityInfo
{
public:
	virtual void DoXfer(Xfer &xfer);
};

void Rva005D1362::DoXfer(Xfer &xfer)
{
	FXParticleSystem::EmissionVelocityInfo::DoXfer(xfer);
	((Rva005ED976 *)this)->selectPlayer((int)&xfer);
}
