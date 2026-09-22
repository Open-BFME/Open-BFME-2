// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AssaultTransportAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D263, 59 bytes. Dedicated TU: retail news 0x444 (push-imm32)
// and runs the pinned behavior ctor (0x0048F5A3, six-vtable MI installs over
// the Transport-family base with 0xA at +0x43C) with the Thing plus
// ModuleData args. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size (0x444). Recipe:
// InvisibilityUpdateFriendNew.cpp. Class identity is the AssaultTransport
// retail cluster (pool key plus name getter plus beginAssault rowed;
// ModuleData triple rowed at 0x24D248/0x24D221/0x24D29E); the ctor has a
// single raw caller (this factory).

class Thing;
class ModuleData;
class Module;

class AssaultTransportAIUpdate
{
public:
	AssaultTransportAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x444];
};

// ?friend_newModuleInstance@AssaultTransportAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AssaultTransportAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AssaultTransportAIUpdate(thing, moduleData));
}
