// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DLaserDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "W3DLaserDraw"
// (addModule pairs the name with it). news 0x5C and runs the declared-only
// module ctor, pinned at 0x000C9D38.

class Thing;
class ModuleData;
class Module;

class W3DLaserDraw
{
public:
	W3DLaserDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x5C];
};

// ?friend_newModuleInstance@W3DLaserDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DLaserDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DLaserDraw(thing, moduleData));
}
