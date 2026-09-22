// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DHordeModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064E80, 59 bytes. Dedicated TU: retail news 0x2F4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x78A82. Class identity is the
// "W3DHordeModelDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DHordeModelDraw
{
public:
	W3DHordeModelDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2F4];
};

// ?friend_newModuleInstance@W3DHordeModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DHordeModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DHordeModelDraw(thing, moduleData));
}
