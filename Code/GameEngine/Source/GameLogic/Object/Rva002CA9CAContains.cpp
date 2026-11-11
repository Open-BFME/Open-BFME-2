// cl: /DNDEBUG /MD /EHsc
// ?rva002CA9CA@Rva002CA9CA@@QAE_NHPBX@Z, retail 0x002CA9CA, 143 bytes.
// Recursive contains: +0x58 id fast path, null arg guard, intrusive list at
// +0x17C (sentinel compare), rowed upgrade-mask test 0x00507558, virtual
// slot 0x1C gate, slot 0x28 id compare at +0x158, slot 0x2C child recurse.
// Evidence: unlock lane, 4 callers including self 0x002CAA39, callees rowed,
// prev Rva002CA88BParse.cpp flags.
//
// ?rva002CCED3@Weapon@@QAE_NPBVObject@@0@Z, retail 0x002CCED3, 244 bytes.
// Whether the weapon (its template the Rva002CA9CA view above, at +4) may
// fire for the source object: no template, or out of ammo (computeStatus
// 0x002CC422 == 1) with template +0x128 set, refuses; when template byte
// +0x168 is nonzero, a source whose rowed 0x0028B511 count reaches 16
// refuses, and so does one the CastleBehavior module (rowed key
// 0x003955DA) of the closest kind-0x78 object within 9999 (one
// Rva0004584D mask filter temporary, getClosestObject 0x00625360) holds
// (rowed 0x00396722 on the source's +0x74 id) while its byte +0x44 is set;
// otherwise the template's rva002CAA59 decides. Callers 0x0041BAD2 and the
// WeaponSet lock bodies; WB twin 0x00BB7AA0 (same checks, 9999.0f radius,
// SetBit(0x78) mask over KINDOFMASK_NONE).
#include "../../../Include/GameLogic/Module/Rva00507823.h"

struct ListNode
{
	ListNode *m_next;
	ListNode *m_prev;
	void *m_data;
};

class VirtNode
{
public:
	virtual void v00();
	virtual bool v04(const void *a, int b);
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual bool v1c();
	virtual void v20();
	virtual void v24();
	virtual void *v28();
	virtual void *v2c();
};

struct ChildId
{
	char m_pad[0x158];
	int m_id;
};

struct FilterInner
{
	char m_pad[0x116];
	unsigned char m_flag;
};

struct Filter
{
	char m_pad[4];
	FilterInner *m_weaponTemplate;
};

class VirtNode2
{
public:
	virtual void v00();
	virtual bool v04(int a, const void *b);
	virtual void v08();
	virtual void v0c(int a, const void *b);
	virtual void v10();
	virtual void v14(int a, const void *b);
	virtual void v18();
	virtual bool v1c();
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2c() = 0;
	virtual void v30();
	virtual bool v34();
	virtual void v38();
	virtual void v3c();
};

#include "../../../Include/Common/Rva001E11F8.h"

class Rva002CAC6ENotify
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24(int a, int b);
};

class WeaponBonus;
class Rva002CA9CA
{
private:
	friend class Weapon;
public:
	bool rva002CA9CA(int damageType, const void *weapon);
	void rva002CAA9D(int a1, const void *a2, const void *a3, const WeaponBonus &bonus);
	bool rva002CAA59(int source, const void *weapon);
	void postProcessLoad();
	void rva002CA970(int firingWeapon, int source, const void *weapon, int position);
	float getProjectileNuggetRadiusIfAlliesAffected(const void *arg);
	bool rva002CAD8B();
	void rva002CAC6E(int a, int context);
	bool getAutoReloadsClip() const { return m_128 == 0; }
	float getReal168() const { return m_168; }
	char m_pad00[0x58];
private:
	int m_58; // +0x58
	char m_pad5C[0x48];
	Rva001E11F8 *m_a4; // +0xA4
	Rva001E11F8 *m_a8; // +0xA8
	Rva001E11F8 *m_ac; // +0xAC
	Rva001E11F8 *m_b0; // +0xB0
	char m_padB4[0x4];
	Rva001E11F8 *m_b8; // +0xB8
	Rva001E11F8 *m_bc; // +0xBC
	Rva001E11F8 *m_c0; // +0xC0
	Rva001E11F8 *m_c4; // +0xC4
	char m_padC8[0x48];
	unsigned char m_110; // +0x110
	char m_pad111[0x17];
	int m_128; // +0x128
	char m_pad12C[0x4];
	float m_130; // +0x130
	char m_pad134[0x34];
	unsigned char m_168; // +0x168
	char m_pad169[0x13];
	ListNode *m_17c; // +0x17C
};

class AsciiString;
class ThingTemplate;
#include "../../../Include/Common/ThingFactory.h"

extern class ThingFactory *TheThingFactory;

struct FloatHolder
{
	char m_pad[0x130];
	float m_130;
};

bool Rva002CA9CA::rva002CA9CA(int id, const void *arg)
{
	if (m_58 == id)
		return true;
	if (arg == 0)
		return false;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode *obj = (VirtNode *)cur->m_data;
		if (((Rva00507823 *)obj)->rva00507558(arg))
		{
			if (obj->v1c())
			{
				void *weaponTemplate = obj->v28();
				if (weaponTemplate != 0)
				{
					if (((ChildId *)weaponTemplate)->m_id == id)
						return true;
				}
			}
			void *child = obj->v2c();
			if (child != 0)
			{
				if (((Rva002CA9CA *)child)->rva002CA9CA(id, arg))
					return true;
			}
		}
		cur = cur->m_next;
	}
	return false;
}

bool Rva002CA9CA::rva002CAA59(int source, const void *weapon)
{
	if (source == 0)
		return false;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode *obj = (VirtNode *)cur->m_data;
		if (obj->v04(weapon, source))
			return true;
		cur = cur->m_next;
	}
	return false;
}

void Rva002CA9CA::rva002CA970(int firingWeapon, int source, const void *weapon, int position)
{
	(void)source;
	(void)position;
	const Filter *flt = (const Filter *)weapon;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		if (flt != 0 && (flt->m_weaponTemplate->m_flag & 0x20) != 0)
		{
			if (obj->v04(firingWeapon, weapon))
			{
				obj->v0c(firingWeapon, weapon);
			}
		}
		cur = cur->m_next;
	}
}


float Rva002CA9CA::getProjectileNuggetRadiusIfAlliesAffected(const void *arg)
{
	if (arg == 0)
		return 0.0f;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode *obj = (VirtNode *)cur->m_data;
		if (((Rva00507823 *)obj)->rva00507558(arg))
		{
			Rva002CA9CA *child = (Rva002CA9CA *)obj->v2c();
			if (child != 0 && (child->m_110 & 2) != 0)
			{
				ListNode *inner = child->m_17c->m_next;
				while (inner != child->m_17c)
				{
					VirtNode *iobj = (VirtNode *)inner->m_data;
					if (((Rva00507823 *)iobj)->rva00507558(arg))
					{
						if (iobj->v1c())
						{
							void *weaponTemplate = iobj->v28();
							if (weaponTemplate != 0)
								return ((FloatHolder *)weaponTemplate)->m_130;
						}
					}
					inner = inner->m_next;
				}
			}
		}
		cur = cur->m_next;
	}
	return 0.0f;
}

bool Rva002CA9CA::rva002CAD8B()
{
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		if (obj != 0 && obj->v34())
			return true;
		cur = cur->m_next;
	}
	return false;
}

void Rva002CA9CA::postProcessLoad()
{
	if (TheThingFactory == 0)
		return;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		obj->v20();
		cur = cur->m_next;
	}
}

void Rva002CA9CA::rva002CAC6E(int a, int context)
{
	char *esi = (char *)this + 0xB8;
	int n = 4;
	do {
		Rva001E11F8 *fireFX = *(Rva001E11F8 **)(esi - 0x14);
		if (fireFX)
			fireFX->rva001E11F8(a, context);
		Rva001E11F8 *preAttackFX = *(Rva001E11F8 **)(esi);
		if (preAttackFX)
			preAttackFX->rva001E11F8(a, context);
		esi += 4;
	} while (--n != 0);
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		Rva002CAC6ENotify *obj = (Rva002CAC6ENotify *)cur->m_data;
		if (obj)
			obj->v24(a, context);
		cur = cur->m_next;
	}
}

#include "../../Common/PartitionRangeQueryCallView.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Module;

class Object
{
	friend class Weapon;
public:
	int rva0028B511() const;	// 0x0028B511
	const Coord3D *getPosition() const { return (const Coord3D *)m_38; }
	int getID() const { return m_74; }
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
private:
	char m_pad00[0x38];
	float m_38[3];
	char m_pad44[0x74 - 0x44];
	int m_74;
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

// The CastleBehavior module as Rva00396722Contains.cpp rows its member test.
class Rva00396722
{
public:
	bool rva00396722(void *p);
	bool getFlag44() const { return m_44; }
	char m_pad00[0x44];
	bool m_44;
};

// BFME 2's partition filters (the view AIPlayerIsLocationSafe.cpp documents).
#include "../../../Include/GameLogic/PartitionFilter.h"

#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BC2908: accept what has every kind of the first mask and none
// of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

extern PartitionManager *ThePartitionManager;

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO
};

#include "../../../Include/GameLogic/Weapon.h"

bool Weapon::rva002CCED3(const Object *victim, const Object *source)
{
	(void)victim;
	if (m_template == 0)
		return false;
	if (computeStatus(0) == OUT_OF_AMMO && !((Rva002CA9CA *)m_template)->getAutoReloadsClip())
		return false;
	if (((Rva002CA9CA *)m_template)->getReal168() != 0.0f)
	{
		if (source->rva0028B511() >= 16)
			return false;
		Object *castle = ThePartitionManager->getClosestObject(source->getPosition(), 9999.0f, 0,
			&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x78),
				*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE));
		if (castle != 0)
		{
			NameKeyType key = CastleBehavior::rva0003955DA();
			Rva00396722 *behavior = (Rva00396722 *)castle->findModule(key);
			if (behavior != 0 && behavior->rva00396722((void *)source->getID()) && behavior->getFlag44())
				return false;
		}
	}
	return ((Rva002CA9CA *)m_template)->rva002CAA59((int)source, this);
}
