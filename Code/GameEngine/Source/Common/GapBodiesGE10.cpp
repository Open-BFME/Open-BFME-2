// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (tenth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

class Player;
class Matrix3D;

// --- 0x004A2BF0 (64B): the object answers the rowed 0x002943B2 for the
// +0x08 player, or its +0x250 interface answers virtual slot 4 and slot 73.
class Rva004A2BF0Interface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual bool s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
	virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
	virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
	virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
	virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
	virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
	virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
	virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
	virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56();
	virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60();
	virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68();
	virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72();
	virtual int s73();
};

#include "../GameLogic/Object/object.h"

class Rva004A2BF0
{
public:
	bool allow(Object *obj);
private:
	char m_pad[8];
	const Player *m_player;									// +0x08
};

// --- 0x005DB033 (18B): the rowed 0x0039B28F with 0, then the rowed
// 0x005DB004.
#include "../../Include/Common/Rva005DB004.h"

#include "../../Include/GameLogic/Module/Rva003BD306Target.h"

void Rva005DB004::rva005DB033()
{
	((Rva003BD306Target *)this)->rva0039B28F(0);
	rva005DB004();
}

// --- 0x005E95B9 (48B): when TheLivingWorldLogic passes the rowed check, its
// 0x002B256E object takes the +0x08 object's +0x08 matrix (rowed 0x003F8361).
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

#include "../../Include/Common/Rva002B254F.h"

#include "../../Include/Common/Rva003F81FDProxy.h"

#include "../../Include/Common/Rva002B256E.h"

struct Rva005E95B9Data
{
	char m_pad[8];
	const Matrix3D *m_08;
};

class Rva005E95B9
{
public:
	void updateWaterTransform();
private:
	char m_pad[8];
	Rva005E95B9Data *m_08;
};

void Rva005E95B9::updateWaterTransform()
{
	if (TheLivingWorldLogic && (unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
		((Rva003F81FDProxy *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E())->rva003F8361(m_08->m_08);
}

// --- 0x0026FCA3 / 0x0026FCB6 / 0x0026FCC3 / 0x0026FCD6: mask test of
// +0x118, mask set of +0x120, mask test of +0x120, mask clear of +0x114.
class Rva0026FCA3
{
public:
	int rva0026FCA3(unsigned int mask) const;
	void rva0026FCB6(unsigned int mask);
	int rva0026FCC3(unsigned int mask) const;
	void rva0026FCD6(unsigned int mask);
private:
	char m_pad[0x114];
	unsigned int m_114;
	unsigned int m_118;
	unsigned int m_11C;
	unsigned int m_120;
};

int Rva0026FCA3::rva0026FCA3(unsigned int mask) const
{
	return (m_118 & mask) != 0;
}

void Rva0026FCA3::rva0026FCB6(unsigned int mask)
{
	m_120 |= mask;
}

int Rva0026FCA3::rva0026FCC3(unsigned int mask) const
{
	return (m_120 & mask) != 0;
}

void Rva0026FCA3::rva0026FCD6(unsigned int mask)
{
	m_114 &= ~mask;
}
