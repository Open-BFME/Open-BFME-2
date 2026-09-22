// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DetachableRiderUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F86D, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4AE883. Class identity is the
// "DetachableRiderUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DetachableRiderUpdate
{
public:
	DetachableRiderUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@DetachableRiderUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DetachableRiderUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DetachableRiderUpdate(thing, moduleData));
}
