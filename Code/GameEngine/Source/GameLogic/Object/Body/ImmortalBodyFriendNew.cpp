// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ImmortalBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251474, 59 bytes. Dedicated TU: retail news 0x100 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C086E. Class identity is the
// "ImmortalBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ImmortalBody
{
public:
	ImmortalBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x100];
};

// ?friend_newModuleInstance@ImmortalBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ImmortalBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ImmortalBody(thing, moduleData));
}
