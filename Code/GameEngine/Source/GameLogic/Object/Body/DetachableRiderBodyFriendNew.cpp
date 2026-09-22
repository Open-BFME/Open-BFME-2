// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DetachableRiderBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251705, 59 bytes. Dedicated TU: retail news 0x108 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C1C82. Class identity is the
// "DetachableRiderBody" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DetachableRiderBody
{
public:
	DetachableRiderBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x108];
};

// ?friend_newModuleInstance@DetachableRiderBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DetachableRiderBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DetachableRiderBody(thing, moduleData));
}
