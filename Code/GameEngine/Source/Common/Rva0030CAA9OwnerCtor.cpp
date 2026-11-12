// cl: /O1 /arch:SSE /G7 /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii
//
// ??0Rva0030CAA9Owner@@QAE@H@Z, retail 0x0030CC3B (314 bytes, EH, RET 8: one
// int and the hidden most-derived flag): the constructor of the wave area
// whose destructor 0x0030CDCA (Rva0030CAA9OwnerDtor.cpp) and broadcast slots
// (Rva0030CAA9Notifiers.cpp) are rowed; its one caller is 0x0030CF43. Target
// evidence: it installs the destructor's tables (0x00C089A8 at +0,
// 0x00C08974 at +0x30, 0x00C08958 on the shared interface 0x00C6EE28 at
// +0xA8 behind a vtordisp) over the rowed bases Rva0053805DBase 0x005380A8
// (+0), Rva00330C50 0x00330C50 (+0x30) and the listener list 0x00330757
// (+0x68), the layout of the standing water area constructor 0x00308E63
// (Rva0030902ECtor.cpp); the int sizes the secondary base's container
// (rowed 0x00330AA6). Defaults: 28.0 at +0x78, 18/50/100 at +0x7C..+0x84,
// 5.0, 2000.0, 1000.0, 3000.0 and 40.0 at +0x88..+0x98, the texture
// "wave256.tga" (+0x9C) and a cleared +0xA0. The StandingWaveAreas chunk
// writer 0x0030CAF8 saves the same fields. Field meanings are not
// established; names are address-derived.
#include "ascii_string.h"

#include "../../../Libraries/Include/Lib/Region2D.h"
struct Rva0030B72CPoint {
 Rva0030B72CPoint() {}
 __forceinline Rva0030B72CPoint(const Rva0030B72CPoint &p):x(p.x),y(p.y) {}
 float x,y;
};

// Native seven-slot polygon interface, as in Rva00330C50Ctor.cpp.
#include "../../Include/Common/Rva00330C50Interface.h"

// The base as Rva0053805DBaseCtor.cpp lays it out.
#include "../../Include/Common/Rva0007DF07.h"

#include "../../Include/Common/Rva00330757Member.h"

class Rva0053805DBase : public Rva0007DF07, public Rva00330757Member,
	public virtual Rva00330C50Interface
{
public:
	Rva0053805DBase();
	virtual ~Rva0053805DBase();
	virtual bool slot1() const;
	virtual void rva0053805D();
	virtual void rva0053806C();
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	Rva00330C50();
	void rva00330AA6(int);
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
	unsigned char m_pad08[0x38 - 8];
};

class Rva0030CAA9Owner : public Rva0053805DBase, public Rva00330C50, public Rva00330757Member
{
public:
	Rva0030CAA9Owner(int count);
	virtual ~Rva0030CAA9Owner();
private:
	float m_78;				// +0x78
	int m_7C;
	int m_80;
	int m_84;
	float m_88;				// +0x88
	float m_8C;
	float m_90;
	float m_94;
	float m_98;
	AsciiString m_9C;			// +0x9C
	int m_A0;				// +0xA0
};

Rva0030CAA9Owner::Rva0030CAA9Owner(int count)
	: m_78(28.0f), m_7C(18), m_80(50), m_84(100), m_88(5.0f), m_8C(2000.0f),
	  m_90(1000.0f), m_94(3000.0f), m_98(40.0f), m_9C("wave256.tga"), m_A0(0)
{
	rva00330AA6(count);
}
