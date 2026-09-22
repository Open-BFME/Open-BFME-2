// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DBoatWakeModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00065027, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xD0B34. Class identity is the
// "W3DBoatWakeModelDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DBoatWakeModelDraw
{
public:
	W3DBoatWakeModelDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@W3DBoatWakeModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DBoatWakeModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DBoatWakeModelDraw(thing, moduleData));
}
