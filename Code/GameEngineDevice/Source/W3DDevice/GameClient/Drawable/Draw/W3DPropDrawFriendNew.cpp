// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DPropDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064CE5, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xCEEC0. Class identity is the
// "W3DPropDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DPropDraw
{
public:
	W3DPropDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@W3DPropDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DPropDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DPropDraw(thing, moduleData));
}
