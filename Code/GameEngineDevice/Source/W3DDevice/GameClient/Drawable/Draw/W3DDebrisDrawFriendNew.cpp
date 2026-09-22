// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DDebrisDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0006482B, 56 bytes. Dedicated TU: retail news 0x48 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xB1C41. Class identity is the
// "W3DDebrisDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DDebrisDraw
{
public:
	W3DDebrisDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x48];
};

// ?friend_newModuleInstance@W3DDebrisDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DDebrisDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DDebrisDraw(thing, moduleData));
}
