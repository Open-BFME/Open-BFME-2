// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LevelGrantSpecialPower module ctor.
// Base MI: vptrs at +0/+0xC/+0x10/+0x20.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"

class SpecialPowerModuleExtra
{
public:
	virtual void specialPowerExtraAnchor();

private:
	unsigned char m_pad[12];
};

#include "../../../../Include/Common/ModuleInterface.h"

class Rva0044EF5E : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public SpecialPowerModuleExtra,
	public ModuleInterface
{
public:
	Rva0044EF5E( Thing *thing, const ModuleData *moduleData );
};

class LevelGrantSpecialPower : public Rva0044EF5E
{
public:
	LevelGrantSpecialPower( Thing *thing, const ModuleData *moduleData );
};

// ??0LevelGrantSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
LevelGrantSpecialPower::LevelGrantSpecialPower( Thing *thing, const ModuleData *moduleData )
	: Rva0044EF5E( thing, moduleData )
{
}
