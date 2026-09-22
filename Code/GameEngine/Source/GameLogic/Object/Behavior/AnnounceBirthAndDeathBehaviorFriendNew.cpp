// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AnnounceBirthAndDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C7C7, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x485125. Class identity is the
// "AnnounceBirthAndDeathBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AnnounceBirthAndDeathBehavior
{
public:
	AnnounceBirthAndDeathBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@AnnounceBirthAndDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AnnounceBirthAndDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AnnounceBirthAndDeathBehavior(thing, moduleData));
}
