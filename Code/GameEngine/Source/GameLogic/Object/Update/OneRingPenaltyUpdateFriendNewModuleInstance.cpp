// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@OneRingPenaltyUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E3F4, 56 bytes. Dedicated TU: the single-phase factory news
// 0x34 and forwards thing plus data to the declared-only Update ctor (pinned
// at 0x499A70, UpdateModule-base body still unrowed). Operator new and
// __EH_prolog resolve via their rows. The TU-local class keeps only size and
// virtuality (vptr plus 0x30 pad). Class identity rides the OneRingPenalty
// file-unit: the Update ctor starts where the rowed OneRingPenaltyUpdateModuleData
// proc ends (0x499A70) in the same 0x4999xx page as the pool key, the MD ctor
// and the MD factory, and this factory ends where the rowed MD factory starts
// (0x24E42C) and is its sole E8 caller.
class Thing;
class ModuleData;
class Module;

class OneRingPenaltyUpdate
{
public:
	OneRingPenaltyUpdate(Thing *thing, const ModuleData *data);
	virtual ~OneRingPenaltyUpdate();
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *data);

private:
	unsigned char m_pad[0x34 - 4];
};

// ?friend_newModuleInstance@OneRingPenaltyUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OneRingPenaltyUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	OneRingPenaltyUpdate *update = new OneRingPenaltyUpdate(thing, data);
	return reinterpret_cast<Module *>(update);
}
