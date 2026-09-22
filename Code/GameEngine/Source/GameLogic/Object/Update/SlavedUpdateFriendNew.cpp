// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SlavedUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EB7D, 56 bytes. Dedicated TU: retail news 0x48 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A18C5. Class identity is the
// "SlavedUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SlavedUpdate
{
public:
	SlavedUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x48];
};

// ?friend_newModuleInstance@SlavedUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SlavedUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SlavedUpdate(thing, moduleData));
}
