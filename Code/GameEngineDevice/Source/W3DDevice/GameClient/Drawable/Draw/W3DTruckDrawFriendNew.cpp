// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DTruckDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064AB5, 59 bytes. Dedicated TU: retail news 0x488 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0xCB3FB. Class identity is the
// "W3DTruckDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DTruckDraw
{
public:
	W3DTruckDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x488];
};

// ?friend_newModuleInstance@W3DTruckDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTruckDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DTruckDraw(thing, moduleData));
}
