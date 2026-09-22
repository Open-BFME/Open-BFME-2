// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DLightDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064DF7, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xCF91D. Class identity is the
// "W3DLightDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DLightDraw
{
public:
	W3DLightDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@W3DLightDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DLightDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DLightDraw(thing, moduleData));
}
