// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DProjectileStreamDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x000650B0, 56 bytes. Dedicated TU: retail news 0x64 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xD1370. Class identity is the
// "W3DProjectileStreamDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class W3DProjectileStreamDraw
{
public:
	W3DProjectileStreamDraw(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x64];
};

// ?friend_newModuleInstance@W3DProjectileStreamDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DProjectileStreamDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DProjectileStreamDraw(thing, moduleData));
}
