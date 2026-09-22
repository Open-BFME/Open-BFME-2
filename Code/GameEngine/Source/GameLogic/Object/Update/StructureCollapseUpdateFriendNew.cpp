// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StructureCollapseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024ED97, 56 bytes. Dedicated TU: retail news 0x44 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A42E4. Class identity is the
// "StructureCollapseUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StructureCollapseUpdate
{
public:
	StructureCollapseUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x44];
};

// ?friend_newModuleInstance@StructureCollapseUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StructureCollapseUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StructureCollapseUpdate(thing, moduleData));
}
