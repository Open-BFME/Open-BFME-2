// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@NotifyTargetsOfImminentProbableCrushingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00255207, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x253E64. Class identity is the
// "NotifyTargetsOfImminentProbableCrushingUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class NotifyTargetsOfImminentProbableCrushingUpdate
{
public:
	NotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@NotifyTargetsOfImminentProbableCrushingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *NotifyTargetsOfImminentProbableCrushingUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new NotifyTargetsOfImminentProbableCrushingUpdate(thing, moduleData));
}
