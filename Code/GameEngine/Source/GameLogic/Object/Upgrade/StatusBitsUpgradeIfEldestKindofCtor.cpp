// cl: /O1 /DNDEBUG /MD /GX
//
// ??0StatusBitsUpgradeIfEldestKindof@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004B4A32, 84 bytes. Behavior-side ctor (rowed instance factory
// 0x250076 news 0x20 with this pinned 2-arg ctor as its sole raw caller
// at 0x25009D).
//
// Shape follows the rowed StatusBitsUpgrade sibling over 0x4B4960: EH
// prologue via /GX plus the declared-only base dtor, an eldest-frame cache
// member at +0x1C refreshed from the GameLogic frame through its own
// trivial method (sole-called helper 0x485975, pinned here under a
// descriptive name; the +0x40 field is proven to be the frame by the rowed
// getFrame pattern), then the vtable group reinstalling the primary slot
// and the +0x0C/+0x10/+0x18 secondaries. No virtuals are declared anywhere
// so no vtable is emitted here; the vtable stores go through sourced-before
// address-take pointers. Row supersedes the ctor pin.

class Thing;
class ModuleData;

class StatusBitsUpgrade
{
public:
	StatusBitsUpgrade(Thing *thing, const ModuleData *moduleData);
	~StatusBitsUpgrade();

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x08];
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x04];
	const void *m_slot18;
};

struct StatusBitsEldestFrame
{
	void cacheGameLogicFrame(void);

private:
	int m_cachedFrame;
};

class StatusBitsUpgradeIfEldestKindof : public StatusBitsUpgrade
{
public:
	StatusBitsUpgradeIfEldestKindof(Thing *thing, const ModuleData *moduleData);

private:
	StatusBitsEldestFrame m_eldestFrame;
};

// ??0StatusBitsUpgradeIfEldestKindof@@QAE@PAVThing@@PBVModuleData@@@Z
StatusBitsUpgradeIfEldestKindof::StatusBitsUpgradeIfEldestKindof(Thing *thing, const ModuleData *moduleData)
	: StatusBitsUpgrade(thing, moduleData)
{
	m_eldestFrame.cacheGameLogicFrame();
	int *vtab = (int *)&m_vtable;
	*vtab = (int)0x00C57ADC;
	int *sec0C = (int *)&m_secondary0C;
	*sec0C = (int)0x00C57A20;
	int *sec10 = (int *)&m_secondary10;
	*sec10 = (int)0x00C579D8;
	int *slot18 = (int *)&m_slot18;
	*slot18 = (int)0x00C58790;
}
