// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@OathbreakerBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251794, 59 bytes. Dedicated TU: retail news 0x100 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C1EC7. Class identity is the
// "OathbreakerBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class OathbreakerBody
{
public:
	OathbreakerBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x100];
};

// ?friend_newModuleInstance@OathbreakerBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OathbreakerBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new OathbreakerBody(thing, moduleData));
}
