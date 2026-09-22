// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DScriptedModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0006489B, 59 bytes. Dedicated TU: retail news 0x2E8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0xC0DD8. Class identity is the
// "W3DScriptedModelDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2E8];
};

// ?friend_newModuleInstance@W3DScriptedModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DScriptedModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DScriptedModelDraw(thing, moduleData));
}
