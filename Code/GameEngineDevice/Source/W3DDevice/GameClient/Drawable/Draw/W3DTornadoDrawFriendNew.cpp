// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DTornadoDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "W3DTornadoDraw"
// (addModule pairs the name with it). news 0x10 and runs the declared-only
// module ctor, pinned at 0x000D181D.

class Thing;
class ModuleData;
class Module;

class W3DTornadoDraw
{
public:
	W3DTornadoDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@W3DTornadoDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTornadoDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DTornadoDraw(thing, moduleData));
}
