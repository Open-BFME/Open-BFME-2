// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@InactiveBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251375, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4BD8BD. Class identity is the
// "InactiveBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class InactiveBody
{
public:
	InactiveBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@InactiveBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *InactiveBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new InactiveBody(thing, moduleData));
}
