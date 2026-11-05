#pragma once

// Accessed BFME 2 prefixes: the matched constructor fixes the four base
// subobjects at +0, +0x0C, +0x10 and +0x20. The getter fixes interface slot 14.
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"

typedef float Real;
enum NameKeyType;
class Xfer;
class ModuleData;
class BehaviorModule;
class BridgeScaffoldBehaviorInterface;
struct Coord3DBase { float x, y, z; };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum ScaffoldTargetMotion { STM_STILL, STM_RISE, STM_BUILD_ACROSS, STM_TEAR_DOWN_ACROSS, STM_SINK };
class Thing { public: void setPosition(const Coord3D *pos); };
class Object : public Thing
{
public:
 const Coord3D *getPosition() const { return &m_pos; }
 __declspec(dllimport) __forceinline BehaviorModule **getBehaviorModules() const { return m_modules244; }
 unsigned char m_pad00[0x38];
 Coord3D m_pos;
 unsigned char m_pad44[0x244 - 0x44];
 BehaviorModule **m_modules244;
};
class BehaviorModuleBase
{
public:
 virtual void behaviorModuleBaseAnchor();
 const ModuleData *m_moduleData;
 Object *m_object;
};
class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
 virtual BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterface() = 0;
};
class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleInterface
{
public:
 BehaviorModule(Thing *, const ModuleData *);
protected:
 Object *getObject() const { return m_object; }
};
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
 UpdateModule(Thing *, const ModuleData *);
 virtual void xfer(Xfer *);
 void loadPostProcess();
private:
 unsigned m_nextCallFrameAndPhase;
 int m_indexInLogic;
 int m_bfmeReserved;
};
class BridgeScaffoldBehaviorInterface
{
public:
 virtual void setPositions(const Coord3D *, const Coord3D *, const Coord3D *) = 0;
 virtual void setMotion(ScaffoldTargetMotion) = 0;
 virtual ScaffoldTargetMotion getCurrentMotion() = 0;
 virtual void reverseMotion() = 0;
 virtual void setLateralSpeed(float) = 0;
 virtual void setVerticalSpeed(float) = 0;
};
class BridgeScaffoldBehavior : public UpdateModule, public BridgeScaffoldBehaviorInterface
{
public:
 BridgeScaffoldBehavior(Thing *, const ModuleData *);
 static NameKeyType rva0004583BD();
 virtual void setPositions(const Coord3D *, const Coord3D *, const Coord3D *);
 virtual void setMotion(ScaffoldTargetMotion);
 virtual void reverseMotion();
 virtual UpdateSleepTime update();
 static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *);
protected:
 virtual void xfer(Xfer *);
 void loadPostProcess();
private:
 ScaffoldTargetMotion m_targetMotion; // +0x24
 Coord3D m_createPos, m_riseToPos, m_buildPos; // +0x28, +0x34, +0x40
 Real m_lateralSpeed, m_verticalSpeed; // +0x4C, +0x50
 Coord3D m_targetPos; // +0x54
};
