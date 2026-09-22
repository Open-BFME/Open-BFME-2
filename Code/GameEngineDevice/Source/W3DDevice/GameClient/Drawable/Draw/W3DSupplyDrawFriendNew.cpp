// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DSupplyDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064A26, 59 bytes. Dedicated TU: retail news 0x2F0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0xCAE43. Class identity is the
// "W3DSupplyDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DSupplyDraw
{
public:
	W3DSupplyDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2F0];
};

// ?friend_newModuleInstance@W3DSupplyDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DSupplyDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DSupplyDraw(thing, moduleData));
}
