// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DSailModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064F98, 59 bytes. Dedicated TU: retail news 0x2F0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0xD078F. Class identity is the
// "W3DSailModelDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DSailModelDraw
{
public:
	W3DSailModelDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2F0];
};

// ?friend_newModuleInstance@W3DSailModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DSailModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DSailModelDraw(thing, moduleData));
}
