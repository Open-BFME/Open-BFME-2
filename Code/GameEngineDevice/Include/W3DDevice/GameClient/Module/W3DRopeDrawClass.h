// Target facts (game.dat, RVAs unless marked VA): ctor 0x000CA752 calls DrawModule 0x000B19A1 at unchanged this, stores the three-purecall RopeDrawInterface table VA 0x00BE2B78 at +0x0C, then its own tables VA 0x00BCBD60 at +0 and VA 0x00BCBD50 at +0x0C. Dtor 0x000CA8BC restores the same derived tables, calls tossSegments 0x000CA84D, frees the vector at +0x10, then restores DrawModule VA 0x00BC9690 at 0x000CA8FE before Snapshot teardown 0x0049B47C. Factory 0x000649EE allocates 0x54 and calls that ctor at 0x00064A15. Primary slot 2, 0x000CA83B, returns VA 0x00BC5BDC "W3DRopeDraw"; slot 0 is deleting dtor 0x000CA9D5, so this is a polymorphic class distinct from its bases.
// Target facts: VA 0x00BCBD60 has 62 slots, ending at the source-path literal VA 0x00BCBE58. Slots 1/3/4/11 are 0x0058B03E/0x000CA916/0x000CA7F6/0x000CACA8; slots 12/35 are RET4 0x0047A69C, 13/14/39 are RET 0x000B3FD0, 38 is RET12 0x000D1407, and 45/46 return this+0x0C through 0x000CA841. The remaining slots inherit DrawModule's targets. VA 0x00BCBD50 has exactly three entries (then a zero): initRopeParms 0x000CAC25, setRopeCurLen 0x00101CDA, setRopeSpeed 0x000CA72E, whose receiver is this+0x0C; there is no interface destructor slot. The ctor constructs the 12-byte vector at +0x10 through 0x00211E58 and writes floats at +0x1C/+0x20/+0x24, RGB at +0x28/+0x2C/+0x30, then floats at +0x34/+0x38/+0x3C/+0x40/+0x44/+0x48/+0x4C/+0x50. Xfer 0x000CA916 confirms these groups. buildSegments 0x000CA9F1 and tossSegments 0x000CA84D prove 16-byte segments with line pointers at +0/+4 and float axes at +8/+0x0C.
// Names and storage: the matched ledger supplies the constructor, public virtual destructor, factory, snapshot name, xfer, draw, rope methods, tossSegments, buildSegments and static rva000CA7F6 declarations. Zero Hour GeneralsMD W3DRopeDraw.h and Common/DrawModule.h supply the field, SegInfo, interface and override names; the target tables and member accesses above establish their BFME2 layout. The vector's three storage pointers are represented by a pointer array; its container operations belong in the owning units. Primary slot 4 has Module's getModuleNameKey contract; the separately rowed static spelling is retained as an out-of-line declaration. All rowed bodies remain out of line.
#pragma once

#ifndef __BFME2_W3DROPEDRAWCLASS_H_
#define __BFME2_W3DROPEDRAWCLASS_H_

#include "../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"
#include "../../../../../Libraries/Include/Lib/RGBColor.h"

class Line3DClass;

class RopeDrawInterface
{
public:
	virtual void initRopeParms(float length, float width, const RGBColor &color, float wobbleLen, float wobbleAmp, float wobbleRate) = 0;
	virtual void setRopeCurLen(float length) = 0;
	virtual void setRopeSpeed(float curSpeed, float maxSpeed, float accel) = 0;
};

class W3DRopeDraw : public DrawModule, public RopeDrawInterface
{
public:
	W3DRopeDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DRopeDraw();
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
	static NameKeyType rva000CA7F6();
	virtual NameKeyType getModuleNameKey() const;

	virtual void doDrawModule(const Matrix3D *transformMtx);
	virtual void setShadowsEnabled(bool enable) { }
	virtual void releaseShadows() { }
	virtual void allocateShadows() { }
	virtual void setFullyObscuredByShroud(bool fullyObscured) { }
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle) { }
	virtual void reactToGeometryChange() { }
	virtual RopeDrawInterface *getRopeDrawInterface() { return this; }
	virtual const RopeDrawInterface *getRopeDrawInterface() const { return this; }

	virtual void initRopeParms(float length, float width, const RGBColor &color, float wobbleLen, float wobbleAmp, float wobbleRate);
	virtual void setRopeCurLen(float length);
	virtual void setRopeSpeed(float curSpeed, float maxSpeed, float accel);

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	struct SegInfo
	{
		Line3DClass *line;
		Line3DClass *softLine;
		float wobbleAxisX;
		float wobbleAxisY;
	};

	SegInfo *m_segments[3];
	float m_curLen;
	float m_maxLen;
	float m_width;
	RGBColor m_color;
	float m_curSpeed;
	float m_maxSpeed;
	float m_accel;
	float m_wobbleLen;
	float m_wobbleAmp;
	float m_wobbleRate;
	float m_curWobblePhase;
	float m_curZOffset;

	void tossSegments();
	void buildSegments();
};

#endif
