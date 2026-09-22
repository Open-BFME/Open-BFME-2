// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CastleBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AA5E, 59 bytes. Dedicated TU: retail news 0xAC (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x3983D4. Class identity is the
// "CastleBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CastleBehavior
{
public:
	CastleBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xAC];
};

// ?friend_newModuleInstance@CastleBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CastleBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CastleBehavior(thing, moduleData));
}
