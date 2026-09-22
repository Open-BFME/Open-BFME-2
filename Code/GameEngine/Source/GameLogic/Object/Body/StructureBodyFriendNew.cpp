// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StructureBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002514CA, 59 bytes. Dedicated TU: retail news 0x104 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C0951. Class identity is the
// "StructureBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StructureBody
{
public:
	StructureBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x104];
};

// ?friend_newModuleInstance@StructureBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StructureBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StructureBody(thing, moduleData));
}
