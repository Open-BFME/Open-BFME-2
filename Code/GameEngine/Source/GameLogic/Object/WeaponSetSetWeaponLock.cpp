// cl: /O1 /Oy /G7 /arch:SSE /DNDEBUG /MD
//
// WeaponSet::setWeaponLock, retail 0x002C8AAE (237 bytes).
// Identity: Zero Hour WeaponSet.cpp setWeaponLock (false for NOT_LOCKED or an
// empty slot; LOCKED_PERMANENTLY always takes the slot, LOCKED_TEMPORARILY only
// when not permanently locked; true otherwise), called with m_weaponSet as this
// by the matched Object::setWeaponLock 0x00290B24. Layout from the body:
// m_weapons at +0x08, current weapon +0x20, lock status +0x24, owner ObjectID
// +0x3C.
// BFME2 additions: look the owner up first; clear the five weapon-slot model
// conditions 0x90..0x94 on it (mask built by the verified address-derived row
// 0x000B6253 in a 0x4C-byte local, i.e. a 19-word model-condition mask, and
// applied by the verified address-derived row 0x001E42F2, whose this is the Object;
// both rows keep their placeholder class names, hence the casts) and set the
// one of the current slot (switch with literal cases; cl merges the five
// masked-word test/or tails). The false path is laid out last, which needs the
// early-out tests folded into one guarding if.

class WeaponTemplateSet;
class ThingTemplate;
enum ObjectID
{
	INVALID_ID = 0
};
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
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[4];
 ThingTemplate *m_template;
 unsigned char m_pad008[0x74-8];
 ObjectID m_id;
 unsigned char m_pad078[0x10C-0x78];
	Rva0010CBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
// Placeholder rows: 0x000B6253 fills a 0x4C-byte (19-word) model-condition mask
// with up to five bits and returns it; 0x001E42F2 clears such a mask on an
// Object (its this is the Object).
class Rva000B6253
{
public:
	Rva000B6253 *rva000B6253(int count, unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
private:
	unsigned int m_words[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};
class Weapon;
class WeaponSet
{
public:
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
 void updateWeaponSet(const Object *);
 void releaseWeaponLock(WeaponLockType);
private:
	unsigned char m_pad00[4];
 const WeaponTemplateSet *m_set; // +0x04
 Weapon *m_weapons[6]; // +0x08 through +0x1C
	WeaponSlotType m_curWeapon; // +0x20
	WeaponLockType m_curWeaponLockedStatus; // +0x24
	unsigned m_filled,m_anti,m_damage; // +28/+2C/+30
 bool m_pitch,m_hasDamage; // +34/+35
 unsigned char m_pad36[6];
	ObjectID m_ownerID; // +0x3C
};
bool WeaponSet::setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType)
{
	Object *owner = TheGameLogic->findObjectByID(m_ownerID);
	if (lockType != NOT_LOCKED && m_weapons[weaponSlot] != 0)
	{
		if (lockType == LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = lockType;
			m_curWeapon = weaponSlot;
		}
		else if (lockType == LOCKED_TEMPORARILY && m_curWeaponLockedStatus != LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = lockType;
			m_curWeapon = weaponSlot;
		}
		if (owner)
		{
			Rva000B6253 mask;
			((Rva001E42F2 *)owner)->rva001E42F2((const int *)mask.rva000B6253(0, 0x90, 0x91, 0x92, 0x93, 0x94));
		}
		switch (m_curWeapon)
		{
		case 0:
			if (owner)
				setModelConditionBit(owner, 0x90);
			break;
		case 1:
			if (owner)
				setModelConditionBit(owner, 0x91);
			break;
		case 2:
			if (owner)
				setModelConditionBit(owner, 0x92);
			break;
		case 3:
			if (owner)
				setModelConditionBit(owner, 0x93);
			break;
		case 4:
			if (owner)
				setModelConditionBit(owner, 0x94);
			break;
		}
		return true;
	}
	return false;
}

// Native 0x002C8C97..0x002C8E39: 418B RET4. WB WeaponSet.cpp553/576
// proves the operation; native offsets below are supported by ctor60 and
// this body. Six 20B saved reload states preserve shared reload across sets;
// the supplied reference has the reset/allocation loop but lacks this state
// transfer and the native owner-ID/model-condition additions. Donor lead:
// BFME1 ba7ddda inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngine/Source/GameLogic/Object/WeaponSet.cpp; WB independently proves
// the added save/restore branches and native helpers establish their ABI.
// /O1 /Oy reproduces the biased native frame and preserves setWeaponLock237.
// Only the existing reference ABI is used; the flag layout is opaque here.
template<int N> class BitFlags;
class WeaponTemplateSet;
class ThingTemplate { public: const WeaponTemplateSet *findWeaponTemplateSet(const BitFlags<117> &) const; };
class Rva0028B7AELeaGetter { public: void *get() const; };
class Rva002C9424 { public: Rva002C9424 *rva002C9424(); };
struct Rva002C943BSrc;
class Rva002C943B { public: void rva002C943B(const Rva002C943BSrc *); };
struct SavedWeaponState { int fields[5]; SavedWeaponState() { ((Rva002C9424 *)this)->rva002C9424(); } };
class WeaponTemplate { public:
 char pad0[0xc]; int m_key; char pad10[0x58-0x10]; int m_damageType;
 char pad5C[0x10c-0x5c]; unsigned m_anti; char pad110[4]; bool m_damage;
};
class Weapon { public:
 virtual void *nativeSlot0(unsigned)=0;
 void rva002CE226(const Object *,const SavedWeaponState *);
 WeaponTemplate *m_template; unsigned m_ownerID;
 char padC[0x4c-0xc]; bool m_pitch;
};
class WeaponStore { friend class WeaponSet; private:
 const WeaponTemplate *Rva002CADBE(int) const; public:
 Weapon *allocateNewWeapon(const WeaponTemplate *,WeaponSlotType) const;
}; extern WeaponStore *TheWeaponStore;
class WeaponTemplateSet { public:
 char pad0[0x14]; const WeaponTemplate *m_weapons[6]; char pad2C[0x35c-0x2c]; bool m_sharedReload,m_sharedLock;
};
void WeaponSet::updateWeaponSet(const Object *obj)
{
 ThingTemplate *templ=obj->m_template;
 const WeaponTemplateSet *set=templ->findWeaponTemplateSet(*(const BitFlags<117> *)((const Rva0028B7AELeaGetter *)obj)->get());
 if(set && set!=m_set) {
   SavedWeaponState state[6];
   SavedWeaponState *saved=0;
   if(m_set && m_set->m_sharedReload && set->m_sharedReload) {
     saved=state;
     for(int i=5;i>=0;--i) if(m_weapons[i]) ((Rva002C943B *)&state[i])->rva002C943B((const Rva002C943BSrc *)m_weapons[i]);
   }
   if(!set->m_sharedLock) { releaseWeaponLock(LOCKED_PERMANENTLY); m_curWeapon=PRIMARY_WEAPON; }
   m_filled=0; m_anti=0; m_damage=0; m_pitch=false; m_hasDamage=false;
   for(int i=5;i>=0;--i) {
     if(m_weapons[i]) { ::operator delete(m_weapons[i]->nativeSlot0(0)); m_weapons[i]=0; }
     if(set->m_weapons[i]) {
       const WeaponTemplate *weaponTemplate=TheWeaponStore->Rva002CADBE(set->m_weapons[i]->m_key);
       if(weaponTemplate) {
         m_weapons[i]=TheWeaponStore->allocateNewWeapon(weaponTemplate,(WeaponSlotType)i);
         m_weapons[i]->m_ownerID=obj->m_id;
         m_weapons[i]->rva002CE226(obj,saved);
         m_filled|=1u<<i; m_anti|=m_weapons[i]->m_template->m_anti;
         m_damage|=1u<<m_weapons[i]->m_template->m_damageType;
         if(m_weapons[i]->m_pitch) m_pitch=true;
         if(m_weapons[i]->m_template->m_damage) m_hasDamage=true;
       }
     }
   }
   m_set=set; m_ownerID=obj->m_id;
 }
}

// Native 0x002C8B9B..0x002C8C06: 107B RET4. Zero Hour WeaponSet.cpp
// releaseWeaponLock (PERMANENTLY always clears, TEMPORARILY only a temporary
// lock); called by the matched Object::releaseWeaponLock 0x0028D8B6 and by
// updateWeaponSet above. BFME2 addition, as in setWeaponLock: look the owner
// up first and clear its five weapon-slot model conditions 0x90..0x94 when
// the lock is released.
static __forceinline void clearSlotConditions(Object *owner)
{
	if (owner)
	{
		Rva000B6253 mask;
		((Rva001E42F2 *)owner)->rva001E42F2((const int *)mask.rva000B6253(0, 0x90, 0x91, 0x92, 0x93, 0x94));
	}
}
void WeaponSet::releaseWeaponLock(WeaponLockType lockType)
{
	Object *owner = TheGameLogic->findObjectByID(m_ownerID);
	if (m_curWeaponLockedStatus != NOT_LOCKED)
	{
		if (lockType == LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = NOT_LOCKED;
			clearSlotConditions(owner);
		}
		else if (lockType == LOCKED_TEMPORARILY)
		{
			if (m_curWeaponLockedStatus == LOCKED_TEMPORARILY)
			{
				m_curWeaponLockedStatus = NOT_LOCKED;
				clearSlotConditions(owner);
			}
		}
	}
}
