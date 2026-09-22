// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DelayedDeathBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002515E7, 59 bytes. Dedicated TU: retail news 0x104 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C15B9. Class identity is the
// "DelayedDeathBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DelayedDeathBody
{
public:
	DelayedDeathBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x104];
};

// ?friend_newModuleInstance@DelayedDeathBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DelayedDeathBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DelayedDeathBody(thing, moduleData));
}
