// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CastleMemberBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AAEE, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x395B66. Class identity is the
// "CastleMemberBehavior" literal ModuleFactory registers alongside this stub and the
// CastleMemberBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CastleMemberBehavior
{
public:
	CastleMemberBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@CastleMemberBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CastleMemberBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CastleMemberBehavior(thing, moduleData));
}
