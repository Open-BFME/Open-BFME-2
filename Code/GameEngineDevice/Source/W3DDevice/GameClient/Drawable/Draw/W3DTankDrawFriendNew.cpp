// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DTankDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064B44, 59 bytes. Dedicated TU: retail news 0x364 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0xCEA6C. Class identity is the
// "W3DTankDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DTankDraw
{
public:
	W3DTankDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x364];
};

// ?friend_newModuleInstance@W3DTankDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTankDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DTankDraw(thing, moduleData));
}
