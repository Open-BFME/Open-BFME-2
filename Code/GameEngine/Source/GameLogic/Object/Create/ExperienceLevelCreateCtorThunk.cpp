// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ExperienceLevelCreate module ctor.
// Out-of-line base MI, then three most-derived vtbls at +0/+0xC/+0x10.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
// ExperienceLevelCreate derives from CreateModule (as in ExperienceLevelCreate.cpp): its
// getCreate fills behavior-interface slot 3 (0x002533D3) and its +0x10 table is
// CreateModuleInterface's.
#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"

class ExperienceLevelCreate : public CreateModule
{
public:
	ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData);
public:
	// retail slot 4: the rowed ?getModuleNameKey@ExperienceLevelCreate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
	// +0x10 table slot 1: the rowed ?onBuildComplete@ExperienceLevelCreate@@UAEXXZ (0x004B9231)
	virtual void onBuildComplete();
};

// ??0ExperienceLevelCreate@@QAE@PAVThing@@PBVModuleData@@@Z
ExperienceLevelCreate::ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData)
	: CreateModule(thing, moduleData)
{
}
