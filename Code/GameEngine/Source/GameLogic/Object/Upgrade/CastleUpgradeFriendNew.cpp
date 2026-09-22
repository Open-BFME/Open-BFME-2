// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CastleUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002505D2, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B6869. Class identity is the
// "CastleUpgrade" literal ModuleFactory registers alongside this stub and the
// CastleUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CastleUpgrade
{
public:
	CastleUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@CastleUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CastleUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CastleUpgrade(thing, moduleData));
}
