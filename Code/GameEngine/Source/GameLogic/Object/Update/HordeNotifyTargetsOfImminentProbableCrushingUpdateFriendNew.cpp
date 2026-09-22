// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HordeNotifyTargetsOfImminentProbableCrushingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002551CF, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x253D88. Class identity is the
// "HordeNotifyTargetsOfImminentProbableCrushingUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HordeNotifyTargetsOfImminentProbableCrushingUpdate
{
public:
	HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@HordeNotifyTargetsOfImminentProbableCrushingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeNotifyTargetsOfImminentProbableCrushingUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HordeNotifyTargetsOfImminentProbableCrushingUpdate(thing, moduleData));
}
