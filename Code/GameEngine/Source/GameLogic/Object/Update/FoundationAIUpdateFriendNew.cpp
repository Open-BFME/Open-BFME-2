// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FoundationAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AA26, 56 bytes. Dedicated TU: retail news 0x30 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4551B3. Class identity is the
// "FoundationAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FoundationAIUpdate
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@FoundationAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FoundationAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FoundationAIUpdate(thing, moduleData));
}
