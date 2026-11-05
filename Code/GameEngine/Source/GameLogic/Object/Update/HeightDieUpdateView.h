#pragma once

// Partial BFME 2 receiver shared by the matched update, transfer and pool-key
// bodies. No constructor is defined through this view. The update interface
// is at +0x10; fields retain their measured +0x20..+0x30 positions. Transfer
// uses primary slot 3 and the existing name-key method occupies slot 4.
// This declaration union does not recover the complete retail class hierarchy.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Xfer;
class ModuleData;
class Object;

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class HeightDieUpdateModuleData
{
public:
	HeightDieUpdateModuleData();

	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04 (not initialized by retail)
	Real m_targetHeightAboveTerrain; // +0x08
	Bool m_targetHeightIncludesStructures; // +0x0C
	Bool m_onlyWhenMovingDown; // +0x0D
	Real m_destroyAttachedParticlesAtHeight; // +0x10
	Bool m_snapToGroundOnDeath; // +0x14
	UnsignedInt m_initialDelay; // +0x18
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual void xfer(Xfer *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class HeightDieUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void xfer(Xfer *xfer);

	const HeightDieUpdateModuleData *getHeightDieUpdateModuleData() const
	{
		return (const HeightDieUpdateModuleData *)m_moduleData;
	}

	Bool m_hasDied; // +0x20
	Bool m_particlesDestroyed; // +0x21
	Coord3D m_lastPosition; // +0x24
	UnsignedInt m_earliestDeathFrame; // +0x30
};
