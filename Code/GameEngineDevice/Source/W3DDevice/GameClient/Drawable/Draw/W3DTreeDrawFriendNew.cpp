// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DTreeDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064BD3, 56 bytes. Dedicated TU: retail news 0xC (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xCEB4D. Class identity is the
// "W3DTreeDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DTreeDraw
{
public:
	W3DTreeDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xC];
};

// ?friend_newModuleInstance@W3DTreeDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTreeDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DTreeDraw(thing, moduleData));
}
