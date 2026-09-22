// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DBuffDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064C5C, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xCEDE1. Class identity is the
// "W3DBuffDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DBuffDraw
{
public:
	W3DBuffDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@W3DBuffDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DBuffDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DBuffDraw(thing, moduleData));
}
