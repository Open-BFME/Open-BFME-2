// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DRopeDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "W3DRopeDraw"
// (addModule pairs the name with it). news 0x54 and runs the declared-only
// module ctor, pinned at 0x000CA752.

class Thing;
class ModuleData;
class Module;

class W3DRopeDraw
{
public:
	W3DRopeDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x54];
};

// ?friend_newModuleInstance@W3DRopeDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DRopeDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DRopeDraw(thing, moduleData));
}
