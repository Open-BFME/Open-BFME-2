// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HeightDieUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D37E, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48FCB2. Class identity is the
// "HeightDieUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HeightDieUpdate
{
public:
	HeightDieUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@HeightDieUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HeightDieUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HeightDieUpdate(thing, moduleData));
}
