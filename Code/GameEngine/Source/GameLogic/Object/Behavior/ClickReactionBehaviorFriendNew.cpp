// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ClickReactionBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AE9B, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45961D. Class identity is the
// "ClickReactionBehavior" literal ModuleFactory registers alongside this stub and the
// ClickReactionBehaviorModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ClickReactionBehavior
{
public:
	ClickReactionBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@ClickReactionBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ClickReactionBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ClickReactionBehavior(thing, moduleData));
}
