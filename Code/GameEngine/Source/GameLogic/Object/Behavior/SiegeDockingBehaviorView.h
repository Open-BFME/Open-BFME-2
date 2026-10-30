#pragma once

#include <vector>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
#include "../../../../Include/Common/ObjectModule.h"

enum NameKeyType { NK_UNKNOWN = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data) : ObjectModule(thing, data) {}
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	// UpdateModuleCtor.cpp owns retail 0x00253390; derived constructors call it.
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void setWakeFrame(Object *object, unsigned int frame);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

// Retail installs table 0x00C4EF80 at +0x20 before the derived table 0x00C41404.
// Every base slot is __purecall (0x0003B810).
class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot() = 0;
};

class SiegeDockingBehavior : public UpdateModule, public SiegeDockingBehaviorSecondaryBase
{
public:
	SiegeDockingBehavior(Thing *thing, const ModuleData *data);
	virtual ~SiegeDockingBehavior();
	virtual NameKeyType getModuleNameKey() const;

private:
	_STL::vector<int> m_vector; // +0x24
	bool m_enabled; // +0x30
};
