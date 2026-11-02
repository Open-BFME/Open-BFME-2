// Target facts (game.dat, RVAs unless marked VA): DrawModule ctor 0x000B19A1 calls DrawableModule ctor 0x00306B19 with unchanged this, then stores VA 0x00BC9690. Destructor 0x000CEB6F stores the same table and jumps to 0x0049B47C, which restores Snapshot's VA 0x00BBB554. Deleting thunk 0x000CEF83 calls 0x000CEB6F. DrawableModule ctor stores ModuleData at +4, the result of Thing slot +0x10 at +8, and VA 0x00C07E54 at +0. Its eleven slots extend Module's nine with two zero-return slots. W3DBoatWakeModelDraw ctor 0x000D0B34 and W3DPropDraw ctor 0x000CEEC0 call DrawModule and start their own fields at +0x0C; the W3DDefaultDraw factory 0x00064863 allocates 0x0C bytes: both bases occupy 0x0C, with no DrawModule data or secondary vptr.
// Target facts: VA 0x00BC9690 has 62 slots, ending at the DrawModule literal VA 0x00BC9788. Slots 0/1/2/3 are 0x000CEF83/0x000B3FD0/0x000B19BD/0x004CBF58; slot 4 and slots 11-14,35,38,39 are __purecall 0x0003B810. Empty slots 15,28,34,36,57,61 use RET 0x000B3FD0; slots 16,18-20,22-24,26,29-32,53,58,59 use RET4 0x0047A69C; slots 21,25,27,54,56 use RET8 0x0050B238; slot 33 uses RET12 0x000D1407. Slots 17,40,55 return false at 0x0047A699; 37,60 return true at 0x0050B5C6; 9,10,41-49,51,52 return zero at 0x000D43D0; 50 returns float zero at 0x002BFBF0.
// Names: the ledger names DrawModule's ctor, protected destructor, loadPostProcess, const GetSnapshotName and xfer at the RVAs above; laser post-load 0x000C92E8 directly calls the base hook. VA 0x00BCBFC0 binds doDrawModule, setShadowsEnabled, releaseShadows, setHidden, setTerrainDecal, setTerrainDecalSize, setTerrainDecalOpacity, isVisible and reactToTransformChange at slots 11,12,13,16,20,21,22,37,38 (RVAs 0x000C7BC4,0x000B2E29,0x000B2E14,0x000B6F6D,0x000B9CE8,0x000B314B,0x000B316B,0x000B37F0,0x000B7FE8); slot 14 is allocateShadows 0x000B9B4A. Drawable 0x00278C29 calls +0x8C for shroud and 0x002742E5 calls +0x98 for transform. Zero Hour Common/DrawModule.h supplies those declarations, neighboring reactToGeometryChange/isLaser, and the interface names. Object getter pair 41,42 is witnessed by Drawable 0x00272393 and VA 0x00BCBFC0; debris 43,44 by creation nugget 0x001F22A8 and VA 0x00BC97A8; rope 45,46 by VA 0x00BCBD60; laser 47,48 by LaserUpdate 0x00363193 and VA 0x00BCB9E0. Each pair's override returns this+0x0C at 0x000CA841. W3DGhostObject 0x00063426 calls slot 49 for RenderObjClass, named getRenderObject in Zero Hour W3DModelDraw.h; its snapshot 0x00064675 calls the neutral bool slot 17. Unidentified entries retain neutral names and only the stack widths and constant results established above.

#pragma once

#ifndef __BFME2_DRAWMODULE_H_
#define __BFME2_DRAWMODULE_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../Common/Module.h"

class Thing;
class Drawable;
class Matrix3D;
struct Coord3D;
class ObjectDrawInterface;
class DebrisDrawInterface;
class RopeDrawInterface;
class LaserDrawInterface;
class RenderObjClass;
enum TerrainDecalType;

class DrawableModule : public Module
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual void *vslot09() { return 0; }
	virtual void *vslot10() { return 0; }

protected:
	virtual ~DrawableModule();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	Drawable *getDrawable() { return m_drawable; }
	const Drawable *getDrawable() const { return m_drawable; }
	Drawable *m_drawable;
};

class DrawModule : public DrawableModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

	virtual void doDrawModule(const Matrix3D *transformMtx) = 0; // 11
	virtual void setShadowsEnabled(bool enable) = 0; // 12
	virtual void releaseShadows() = 0; // 13
	virtual void allocateShadows() = 0; // 14
	virtual void vslot15() { }
	virtual void setHidden(bool hidden) { } // 16
	virtual bool v17() { return false; }
	virtual void vslot18(int) { }
	virtual void vslot19(int) { }
	virtual void setTerrainDecal(TerrainDecalType type) { } // 20
	virtual void setTerrainDecalSize(float x, float y) { } // 21
	virtual void setTerrainDecalOpacity(float opacity) { } // 22
	virtual void vslot23(int) { }
	virtual void vslot24(int) { }
	virtual void vslot25(int, int) { }
	virtual void vslot26(int) { }
	virtual void vslot27(int, int) { }
	virtual void vslot28() { }
	virtual void vslot29(int) { }
	virtual void vslot30(int) { }
	virtual void vslot31(int) { }
	virtual void vslot32(int) { }
	virtual void vslot33(int, int, int) { }
	virtual void vslot34() { }
	virtual void setFullyObscuredByShroud(bool fullyObscured) = 0; // 35
	virtual void vslot36() { }
	virtual bool isVisible() const { return true; } // 37
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle) = 0; // 38
	virtual void reactToGeometryChange() = 0; // 39
	virtual bool isLaser() const { return false; } // 40
	virtual ObjectDrawInterface *getObjectDrawInterface() { return 0; } // 42
	virtual const ObjectDrawInterface *getObjectDrawInterface() const { return 0; } // 41
	virtual DebrisDrawInterface *getDebrisDrawInterface() { return 0; } // 44
	virtual const DebrisDrawInterface *getDebrisDrawInterface() const { return 0; } // 43
	virtual RopeDrawInterface *getRopeDrawInterface() { return 0; } // 46
	virtual const RopeDrawInterface *getRopeDrawInterface() const { return 0; } // 45
	virtual LaserDrawInterface *getLaserDrawInterface() { return 0; } // 48
	virtual const LaserDrawInterface *getLaserDrawInterface() const { return 0; } // 47
	virtual RenderObjClass *getRenderObject() { return 0; } // 49
	virtual float vslot50() { return 0.0f; }
	virtual void *vslot51() { return 0; }
	virtual void *vslot52() { return 0; }
	virtual void vslot53(int) { }
	virtual void vslot54(int, int) { }
	virtual bool vslot55() { return false; }
	virtual void vslot56(int, int) { }
	virtual void vslot57() { }
	virtual void vslot58(int) { }
	virtual void vslot59(int) { }
	virtual bool vslot60() { return true; }
	virtual void vslot61() { }

protected:
	virtual ~DrawModule();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

#endif
