// cl: /DNDEBUG /MD
//
// Helper-then-tail wrappers: each saves this, runs a no-argument member
// helper, restores this, and tail-jumps to another no-argument member.
// The first three restore this itself (mov ecx,esi); the rest load a
// member pointer (mov ecx,[esi+off]). Single-inheritance qualified base
// calls for same-object tails (VslotSmallBodiesAJ idiom); unrowed
// targets are pinned from each body's own REL32, rowed ones reuse their
// ledger names.
// 0x0010BA61: helper 0x00109D64, tail rowed-pin 0x00108895.
// 0x004E54B8: helper 0x004E5372, tail 0x004E52DC.
// 0x005962E7: helper rowed 0x0025C010, tail 0x00596269.
// 0x005D1516: helper rowed trivial 0x000B3FD0, tail 0x005D13C2 (+8).
// 0x005E1906: helper rowed 0x00248D08, tail 0x005E18D0 (+0xC).
// 0x005E1917: helper rowed 0x00420B2A, tail 0x005E18DC (+0xC).
// 0x005E1BC4: helper rowed trivial 0x000B3FD0, tail 0x005E1B9A (+0xC).
// 0x005E25DE: helper rowed trivial 0x000B3FD0, tail 0x005E254C (+0xC).
// 0x005E590F: helper rowed trivial 0x000B3FD0, tail 0x005E589E (+8).
// 0x005E6BA3: helper rowed trivial 0x000B3FD0, tail 0x005E6A9D (+0x20).
// 0x005E6BB4: helper rowed trivial 0x000B3FD0, tail 0x005E6AD8 (+0x20).

class Rva0010BA2COwner
{
public:
	void rva00108895();
};

class Rva0010BA61 : public Rva0010BA2COwner
{
public:
	void rva0010BA61();
private:
	void helper00109D64();
};
// Rva0010BA61::rva0010BA61 is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva0010BA61.cpp (0x0010BA61).

class Rva004E52DC
{
public:
	void rva004E52DC();
};

class Rva004E54B8 : public Rva004E52DC
{
public:
	void rva004E54B8();
private:
	void helper004E5372();
};
void Rva004E54B8::rva004E54B8()
{
	helper004E5372();
	Rva004E52DC::rva004E52DC();
}

class Rva0025C010
{
public:
	void rva0025C010();
};

class Rva005961D6
{
public:
	void rva00596269();
};

class Rva005962E7 : public Rva005961D6
{
public:
	void rva005962E7();
};

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_EXTERN_DTOR
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"

class Rva005D13C2
{
public:
	void rva005D13C2();
};

class Rva005D1516
{
public:
	void rva005D1516();
private:
	char m_pad00[8];
	Rva005D13C2 *m_08;
};
void Rva005D1516::rva005D1516()
{
	((Coord3D *)this)->~Coord3D();
	m_08->rva005D13C2();
}

class Overridable
{
public:
	void markAsOverride();
};

class Rva005E18D0Forwarder
{
public:
	void tail005E18D0();
};

class Rva005E1906 : public Rva005E18D0Forwarder
{
public:
	void rva005E1906();
private:
	char m_pad00[0x0C];
	Rva005E18D0Forwarder *m_0C;
};
void Rva005E1906::rva005E1906()
{
	((Overridable *)this)->markAsOverride();
	m_0C->tail005E18D0();
}

class Rva00420B2AZeroSetter
{
public:
	void disable();
};

class Rva005E18DCForwarder
{
public:
	void tail005E18DC();
};

class Rva005E1917 : public Rva005E18DCForwarder
{
public:
	void rva005E1917();
private:
	char m_pad00[0x0C];
	Rva005E18DCForwarder *m_0C;
};
void Rva005E1917::rva005E1917()
{
	((Rva00420B2AZeroSetter *)this)->disable();
	m_0C->tail005E18DC();
}

namespace StrategicInGameUI {
class RegionDetailsArmiesPage
{
public:
	class Impl
	{
	public:
		void Update();
	};
};
}

class Rva005E1BC4
{
public:
	void rva005E1BC4();
private:
	char m_pad00[0x0C];
	StrategicInGameUI::RegionDetailsArmiesPage::Impl *m_0C;
};
void Rva005E1BC4::rva005E1BC4()
{
	((Coord3D *)this)->~Coord3D();
	m_0C->Update();
}

class Rva005E254C
{
public:
	void rva005E254C();
};

class Rva005E25DE
{
public:
	void rva005E25DE();
private:
	char m_pad00[0x0C];
	Rva005E254C *m_0C;
};
void Rva005E25DE::rva005E25DE()
{
	((Coord3D *)this)->~Coord3D();
	m_0C->rva005E254C();
}

class Rva005E589EForwarder
{
public:
	void tail005E589E();
};

class Rva005E590F
{
public:
	void rva005E590F();
private:
	char m_pad00[8];
	Rva005E589EForwarder *m_08;
};
void Rva005E590F::rva005E590F()
{
	((Coord3D *)this)->~Coord3D();
	m_08->tail005E589E();
}

class Rva005E6A9DRun
{
public:
	void run();
};

class Rva005E6BA3
{
public:
	void rva005E6BA3();
private:
	char m_pad00[0x20];
	Rva005E6A9DRun *m_20;
};
void Rva005E6BA3::rva005E6BA3()
{
	((Coord3D *)this)->~Coord3D();
	m_20->run();
}

class Rva005E6AD8
{
public:
	void rva005E6AD8();
};

class Rva005E6BB4
{
public:
	void rva005E6BB4();
private:
	char m_pad00[0x20];
	Rva005E6AD8 *m_20;
};
void Rva005E6BB4::rva005E6BB4()
{
	((Coord3D *)this)->~Coord3D();
	m_20->rva005E6AD8();
}

// Native 0x005E6B8F..0x005E6BA3, 20B. The +0x14 member runs the
// complete 81B no-argument helper; the tail uses this-0x0C and the
// existing 0x005F327A owner through its 0x005F604C retail jump thunk.
// Neither the wrapper's original class nor its method name is known.
class Rva005E6B3E
{
public:
	void updateTooltip();
};

// Retail 0x005E6B8F calls 0x005F604C, the rowed 5-byte forward to
// Rva005F327ARun::run (TailJumpWrappers5B.cpp); the call names that row.
class Rva005F604C
{
public:
	void run();
};

class Rva005E6B8F
{
public:
	virtual void rva005E6B8F();
private:
	char m_pad04[0x14 - 4];
	Rva005E6B3E *m_14;
};

void Rva005E6B8F::rva005E6B8F()
{
	m_14->updateTooltip();
	((Rva005F604C *)((char *)this - 0x0C))->run();
}

// Native 0x005E5920..0x005E5942, 34B.  A qualified call to the rowed
// RAMFile::write 0x00574473; on -1 it restores this and tail-jumps to the
// rowed helper 0x005E5884 with the two arguments forwarded (thiscall ret 8).
// The tail-jump form needs the owner region's /O1 /arch:SSE /G7: under /O2 the
// same source re-pushes the args and calls.  The equal-arm m_8 test and the
// barrier after the call are codegen carriers that only shape the schedule;
// the evaluated semantics are the plain write/compare/forward.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class RAMFile
{
public:
	virtual int write(const void *a, int b);
};

class Rva005E5884
{
public:
	int rva005E5884(void *a1, int a2);
};

class Rva005E5920 : public RAMFile
{
public:
	int rva005E5920(void *buffer, int size);
private:
	char m_pad04[4];
	Rva005E5884 *m_8;
};

int Rva005E5920::rva005E5920(void *buffer, int size)
{
	int writeResult = RAMFile::write(buffer, size);
	_ReadWriteBarrier();
	if ((writeResult == -1) && (m_8 != 0 || m_8 == 0))
		return (size ? m_8 : m_8)->rva005E5884(buffer, size);
	return writeResult;
}
