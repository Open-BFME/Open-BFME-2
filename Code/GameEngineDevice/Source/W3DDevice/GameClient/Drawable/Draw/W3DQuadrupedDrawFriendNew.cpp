// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DQuadrupedDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x000649B3, 59 bytes. Dedicated TU: retail news 0x2E8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0xCA0A4. Class identity is the
// "W3DQuadrupedDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DQuadrupedDraw
{
public:
	W3DQuadrupedDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2E8];
};

// ?friend_newModuleInstance@W3DQuadrupedDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DQuadrupedDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DQuadrupedDraw(thing, moduleData));
}
