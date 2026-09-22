// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CritterEmitterUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002528CE, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C8D86. Class identity is the
// "CritterEmitterUpdate" literal ModuleFactory registers alongside this stub and the
// CritterEmitterUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CritterEmitterUpdate
{
public:
	CritterEmitterUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@CritterEmitterUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CritterEmitterUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CritterEmitterUpdate(thing, moduleData));
}
