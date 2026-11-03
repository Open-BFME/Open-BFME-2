// Target facts (game.dat, RVAs unless marked VA): factory 0x00064D6E allocates 0x18 bytes and calls ctor 0x000CF10B, which calls W3DPropDraw 0x000CEEC0 at +0; that ctor calls DrawModule 0x000B19A1 and writes byte +0x0C. W3DPropDraw's factory 0x00064CE5 allocates 0x10 bytes. Floor ctor writes four byte flags at +0x14..+0x17; xfer 0x000CF074 takes their addresses at +0x16,+0x17,+0x15; setters 0x000CF4AE/0x000CF4C2 write +0x15/+0x16.
// Target facts: ctor first stores VA 0x00C1C780 (one __purecall slot) at +0x10, then VA 0x00BCD4E0 at +0 and VA 0x00BCD4D8 at +0x10; dtor 0x000CF1A6 restores the same final pair and calls DrawModule dtor 0x000CEB6F. Primary table has 62 slots, ending at ModuleData table VA 0x00BCD5D8; slots 0/2/3/4/9/10/11/16/18/38 target 0x000CF492/0x000CF14F/0x000CF074/0x000CF161/0x000CF155/0x000CF155/0x000CF3BA/0x000CF4AE/0x000CF4C2/0x000CF25F. Secondary table has one slot, 0x000CF370, whose this is object+0x10 (reads this-0x0C, writes this+7, calls 0x000CF2CF with this-0x10); it has no virtual destructor.
// Target facts: 0x000CF14F returns VA 0x00BC5B94 "W3DFloorDraw", also passed by key getter 0x000CF161. Ledger names ctor/dtor, name, getModuleNameKey, xfer, doDrawModule, updateRecordMatch, factory and rva000CF20C/25F/2CF/4AE/4C2 at their corresponding RVAs. 0x000CF25F returns with RET12; 0x000CF370 with RET12; 0x000CF155 returns object+0x10. Unknown field and interface names below describe offsets or slots only.
#pragma once

#ifndef __BFME2_W3DFLOORDRAW_H_
#define __BFME2_W3DFLOORDRAW_H_

#include "W3DPropDrawClass.h"

class AsciiString;
class Rva000CF0D6;

class W3DFloorDrawIface
{
public:
	virtual void updateRecordMatch(const Rva000CF0D6 *what, int, int) = 0;
};

class W3DFloorDraw : public W3DPropDraw, public W3DFloorDrawIface
{
public:
	W3DFloorDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DFloorDraw();
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
	const char *name() const;
	virtual NameKeyType getModuleNameKey() const;
	virtual void *vslot09();
	virtual void *vslot10();
	virtual void doDrawModule(const Matrix3D *transformMtx);
	virtual void setHidden(bool hidden);
	virtual void vslot18(int);
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle);
	virtual void updateRecordMatch(const Rva000CF0D6 *what, int, int);
	void rva000CF20C(AsciiString *out);
	void rva000CF25F(unsigned int, unsigned int, unsigned int);
	void rva000CF2CF();
	void rva000CF4AE(bool value);
	void rva000CF4C2(bool value);

protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	bool m_14;
	bool m_15;
	bool m_16;
	bool m_17;
};

#endif
