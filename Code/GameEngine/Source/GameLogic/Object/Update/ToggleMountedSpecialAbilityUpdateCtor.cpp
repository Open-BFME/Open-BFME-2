// cl: /DNDEBUG /MD
//
// ??0ToggleMountedSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004ADAB5, 74 bytes.
// ToggleMountedSpecialAbilityUpdate behavior ctor over the pinned Rva0044EF5E
// intermediate base (0x44EF5E, thing plus data): sets the +0x88 slot from its
// base form to its final form (DIR32-masked provisional table symbols;
// the barrier pins both stores so retail keeps the lea plus double through-
// eax shape), then re-stores the primary vtable slot and the +0x0C/+0x10/
// +0x20 secondary slots (provisional table addresses, DIR32-masked), then
// clears a flag at +0x8C. The rowed name getter at 0x4ADA70 and ModuleData
// factory 0x24F6C5 prove the class; the rowed instance factory 0x24F68A is
// the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C"
{
	void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
}

static int s_slotBase;
static int s_vtable;
static int s_secondary10;

// The data ledger assigns these provisional table symbols to ModuleUpdateDtors.
// Share those definitions rather than allocating another datum for each table.
extern "C"
{
	extern int s_dummy5188;
	extern int s_dummy5198;
	extern const void *const s_dummy62D8[47];
}

enum NameKeyType { NK_UNKNOWN = 0 };
class Object;
struct MountedDataView;

template <int N>
class MountedSlots : public MountedSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <>
class MountedSlots<0>
{
};

// The constructor's real provider is still rowed as Rva0044EF5E. Keep that
// base identity while sharing its retail +0x88 prefix with the behavior bodies.
class Thing;
class ModuleData;

class __declspec(novtable) Rva0044EF5E : public MountedSlots<17>
{
public:
    Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
    const MountedDataView *data;
    Object *owner;
    char padC[0x24 - 0xC];
    int state;
    char pad28[0x88 - 0x28];
};

class __declspec(novtable) ToggleMountedSpecialAbilityUpdate : public Rva0044EF5E
{
public:
    ToggleMountedSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
    virtual NameKeyType getModuleNameKey() const;
    virtual void triggerAbilityEffect();
    void createMountedTemplate();
    void rva004ADCE8(const Object *replacement);

protected:
    const void *m_slotBase;
    bool flag8C;
};

// ??0ToggleMountedSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4ADAB5
ToggleMountedSpecialAbilityUpdate::ToggleMountedSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_slotBase = &s_slotBase;
	_ReadWriteBarrier();
	m_slotBase = &s_dummy5188;
	*(const void **)this = &s_vtable;
	*(const void **)((char *)this + 0x0C) = s_dummy62D8;
	*(const void **)((char *)this + 0x10) = &s_secondary10;
	*(const void **)((char *)this + 0x20) = &s_dummy5198;
	flag8C = false;
}
