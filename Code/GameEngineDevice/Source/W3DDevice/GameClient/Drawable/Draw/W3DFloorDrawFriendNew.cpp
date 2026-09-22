// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DFloorDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064D6E, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xCF10B. Class identity is the
// "W3DFloorDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DFloorDraw
{
public:
	W3DFloorDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@W3DFloorDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DFloorDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DFloorDraw(thing, moduleData));
}
