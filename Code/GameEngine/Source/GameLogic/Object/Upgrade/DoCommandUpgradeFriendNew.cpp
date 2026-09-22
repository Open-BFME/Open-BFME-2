// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DoCommandUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002500AE, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B4C2E. Class identity is the
// "DoCommandUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DoCommandUpgrade
{
public:
	DoCommandUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@DoCommandUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DoCommandUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DoCommandUpgrade(thing, moduleData));
}
