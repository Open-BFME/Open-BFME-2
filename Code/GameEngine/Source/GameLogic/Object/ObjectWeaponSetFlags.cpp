// cl: /O1 /DNDEBUG /MD
//
// Object::setWeaponSetFlag / Object::clearWeaponSetFlag, retail 0x00290963
// (173 bytes) and 0x00290A10 (177 bytes), adjacent in retail Object.cpp.
// Identity: Zero Hour Object.cpp and the BFME1 donor Object.cpp name these two
// methods with this shape: set or clear the WeaponSetType bit in
// m_curWeaponSetFlags, then m_weaponSet.updateWeaponSet(this), then mirror the
// flag onto the model condition from TheWeaponSetTypeToModelConditionTypeMap.
// Target evidence for the layout: the matched getter 0x0028B7AE (lea eax,
// [ecx+0x370]) is getWeaponSetFlags, the +0x330 member passed as this to
// 0x002C8C97 is m_weaponSet (that body is ZH WeaponSet::updateWeaponSet:
// findWeaponTemplateSet on the template with getWeaponSetFlags, compared with
// the current set at +4; pinned here), and the map is the int table at VA
// 0x00C006C8 indexed by the weapon set type.
// BFME2 deltas: the model condition bits live on the Object (word array at
// +0x10C, the base the variable-index test uses here) instead of the
// Drawable; MODELCONDITION_INVALID (-1) entries are skipped; and the model
// conditions 0x12D/0x12E/0x12F additionally queue 0x1BD/0x1BE/0x1BF on the
// ObjectSMCHelper at +0x230 for g_Va00DBA4E4 frames (0x004DE85F, which sets
// that condition and records its expiry frame; pinned by address).
// Bit indexes are unsigned (shr) as in a bitset; the masked-word test makes cl
// keep the mask in a register and test/or the word in memory.
//
// Object::rva00290AC1, retail 0x00290AC1 (99 bytes), the next method: removes a
// whole WeaponSetFlags mask through the matched 4-word op 0x0028C570 (the flags
// class keeps that row's placeholder name Rva0028C570), updates the weapon set,
// then clears every Object model-condition bit 0..0x67 whose index is set in
// the mask (same index, no map; signed loop counter, unsigned bit accessors).
// Object::setWeaponLock, retail 0x00290B24 (79 bytes): Zero Hour has it inline
// as return m_weaponSet.setWeaponLock(weaponSlot, lockType); BFME2 makes it out
// of line, first notifying slot 90 of the +0x250 interface with both args and
// setting object status 0x51 when a non-primary slot is locked permanently
// (written as two setStatus calls that cl merges, as retail pushes 1 or 0 per
// branch). The callee 0x002C8AAE is WeaponSet::setWeaponLock (ZH body: early
// out on NOT_LOCKED, m_weapons[slot] at +8, lock status +0x24 and current
// weapon +0x20; pinned here).

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
class Object;
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
class WeaponSet
{
public:
	void updateWeaponSet(const Object *obj);
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
private:
	unsigned char m_data[0x40];
};
class Rva0028C570
{
public:
	void set(unsigned int i)
	{
		m_words[i >> 5] |= 1U << (i & 0x1f);
	}
	void clear(unsigned int i)
	{
		m_words[i >> 5] &= ~(1U << (i & 0x1f));
	}
	unsigned int test(unsigned int i) const
	{
		return m_words[i >> 5] & (1U << (i & 0x1f));
	}
	void rva0028C570(const Rva0028C570 &other);
private:
	unsigned int m_words[4];
};
typedef Rva0028C570 WeaponSetFlags;
class Rva0010CConditionBits
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};
// The Object +0x230 helper: ObjectSMCHelper (its update 0x004DE7C2 is slot 0 of
// the vtable 0x00BFC07C just before the matched ??_GObjectSMCHelper table).
// 0x004DE85F queues a timed special model condition (pinned by address).
class ObjectSMCHelper
{
public:
	void setModelConditionState(ModelConditionFlagType mc, unsigned int frames);
};
template <int N> class Rva00290B24Slots : public Rva00290B24Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00290B24Slots<0>
{
};
// The Object +0x250 interface: slots 0..89 placeholders, slot 90 below.
class Rva00290B24Iface : public Rva00290B24Slots<90>
{
public:
	virtual void rva00290B24Slot90(WeaponSlotType weaponSlot, WeaponLockType lockType) = 0;
};
extern const ModelConditionFlagType TheWeaponSetTypeToModelConditionTypeMap[];
extern int g_Va00DBA4E4;
class Object
{
public:
	void rva0028AE6D();
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
	void rva00290AC1(const WeaponSetFlags &flags);
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	void setStatus(ObjectStatusTypes status, bool set);
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
private:
	unsigned char m_pad000[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x230 - 0x15C];
	ObjectSMCHelper *m_smcHelper; // +0x230
	unsigned char m_pad234[0x250 - 0x234];
	Rva00290B24Iface *m_250; // +0x250
	unsigned char m_pad254[0x330 - 0x254];
	WeaponSet m_weaponSet; // +0x330
	WeaponSetFlags m_curWeaponSetFlags; // +0x370
};
void Object::setWeaponSetFlag(WeaponSetType wst)
{
	m_curWeaponSetFlags.set(wst);
	m_weaponSet.updateWeaponSet(this);
	ModelConditionFlagType mc = TheWeaponSetTypeToModelConditionTypeMap[wst];
	if (mc != MODELCONDITION_INVALID)
	{
		if (m_conditionBits.test(mc) == 0)
		{
			m_conditionBits.set(mc);
			rva0028AE6D();
		}
	}
	if (mc == 0x12D)
		m_smcHelper->setModelConditionState((ModelConditionFlagType)0x1BD, g_Va00DBA4E4);
	else if (mc == 0x12E)
		m_smcHelper->setModelConditionState((ModelConditionFlagType)0x1BE, g_Va00DBA4E4);
	else if (mc == 0x12F)
		m_smcHelper->setModelConditionState((ModelConditionFlagType)0x1BF, g_Va00DBA4E4);
}
void Object::clearWeaponSetFlag(WeaponSetType wst)
{
	m_curWeaponSetFlags.clear(wst);
	m_weaponSet.updateWeaponSet(this);
	ModelConditionFlagType mc = TheWeaponSetTypeToModelConditionTypeMap[wst];
	if (mc != MODELCONDITION_INVALID)
	{
		if (m_conditionBits.test(mc) != 0)
		{
			m_conditionBits.clear(mc);
			rva0028AE6D();
		}
	}
	if (mc == 0x12D)
		m_smcHelper->setModelConditionState((ModelConditionFlagType)0x1BD, g_Va00DBA4E4);
	else if (mc == 0x12E)
		m_smcHelper->setModelConditionState((ModelConditionFlagType)0x1BE, g_Va00DBA4E4);
	else if (mc == 0x12F)
		m_smcHelper->setModelConditionState((ModelConditionFlagType)0x1BF, g_Va00DBA4E4);
}
void Object::rva00290AC1(const WeaponSetFlags &flags)
{
	m_curWeaponSetFlags.rva0028C570(flags);
	m_weaponSet.updateWeaponSet(this);
	for (int i = 0; i < 0x68; ++i)
	{
		if (flags.test(i) && m_conditionBits.test(i))
		{
			m_conditionBits.clear(i);
			rva0028AE6D();
		}
	}
}
inline bool Object::setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType)
{
	Rva00290B24Iface *iface = m_250;
	if (iface)
		iface->rva00290B24Slot90(weaponSlot, lockType);
	if (lockType == LOCKED_PERMANENTLY && weaponSlot != PRIMARY_WEAPON)
		setStatus((ObjectStatusTypes)0x51, true);
	else
		setStatus((ObjectStatusTypes)0x51, false);
	return m_weaponSet.setWeaponLock(weaponSlot, lockType);
}

// This method is a header inline in the copier units; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeObjectSetWeaponLockInlineAnchor@@YAXXZ absent-from-retail
void _bfmeObjectSetWeaponLockInlineAnchor()
{
	static_cast<Object *>(0)->setWeaponLock(PRIMARY_WEAPON, NOT_LOCKED);
}
#pragma inline_depth()
// Object::setSpecialModelConditionState, retail 0x0028AEB2 (12 bytes): Zero Hour
// has it on the Object; BFME2 forwards it to the ObjectSMCHelper (tail jump).
void Object::setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames)
{
	m_smcHelper->setModelConditionState(mc, frames);
}
