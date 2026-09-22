// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DozerAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CD7D, 59 bytes. Dedicated TU: retail news 0x4A8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4894F5. Class identity is the
// "DozerAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DozerAIUpdate
{
public:
	DozerAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x4A8];
};

// ?friend_newModuleInstance@DozerAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DozerAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DozerAIUpdate(thing, moduleData));
}
