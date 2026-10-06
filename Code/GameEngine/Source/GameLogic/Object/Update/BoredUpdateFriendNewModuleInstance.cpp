// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BoredUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E0EA, 56 bytes. Dedicated TU: the single-phase factory news
// 0x24 and forwards thing plus data to the declared-only Update ctor (pinned
// at 0x496791, UpdateModule-base body with random init still unrowed).
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x20 pad). Recipe:
// BoredUpdateModuleDataFriendNew.cpp. Class identity rides the BoredUpdate
// file-unit: the ctor starts where the rowed BoredUpdateModuleData proc ends
// (0x496791) and the factory is its sole E8 caller.
class Thing;
class ModuleData;
class Module;

class BoredUpdate
{
public:
	BoredUpdate(Thing *thing, const ModuleData *data);
	virtual ~BoredUpdate();
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *data);

private:
	unsigned char m_pad[0x24 - 4];
};

// ?friend_newModuleInstance@BoredUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BoredUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	BoredUpdate *update = new BoredUpdate(thing, data);
	return reinterpret_cast<Module *>(update);
}
