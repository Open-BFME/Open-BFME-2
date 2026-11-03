// Target facts (game.dat, RVAs unless marked VA): W3DPropDraw factory 0x00064CE5 allocates 0x10 bytes; ctor 0x000CEEC0 calls DrawModule 0x000B19A1 and writes byte +0x0C.
// W3DFloorDraw (ctor 0x000CF10B) derives from it. The file name carries the Class suffix because units include a shim spelled W3DPropDraw.h.
#pragma once

#ifndef __BFME2_W3DPROPDRAWCLASS_H_
#define __BFME2_W3DPROPDRAWCLASS_H_

#include "../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

class W3DPropDraw : public DrawModule
{
public:
	W3DPropDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void doDrawModule(const Matrix3D *transformMtx);
	virtual void setShadowsEnabled(bool enable);
	virtual void releaseShadows();
	virtual void allocateShadows();
	virtual void setFullyObscuredByShroud(bool fullyObscured);
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle);
	virtual void reactToGeometryChange();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	bool m_0C;
};

#endif
