// cl: /MD /DNDEBUG
// ?rva004C7F5C@PlayerHealSpecialPower@@QAEXPAVObject@@@Z 222B @0x004C7F5C: heal guard via Thing KindOf plus relationship plus float range plus body mult plus attemptHealing plus doFXObj.
// Evidence: retail push ebp frame plus Thing 0x11B test plus isAnyKindOf via BitFlags at this plus4 plus0x88 plus getRelationship pin 0x28D156 plus float range via BfmeZeroRange and g_00BCEA18 plus body at plus0x254 slot 0x18 mult plus attemptHealing row 0x28FE55 plus doFXObj row 0x0B2235. Caller at 0x004C8128.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

template<int N>
class BitFlags
{
public:
	bool any() const;
	unsigned int m_bits[(N + 31) / 32];
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
};

struct Tmpl
{
	char m_pad00[0x108];
	unsigned char m_108;
	char m_pad109[0x11B - 0x109];
	unsigned char m_11B;
};

enum Relationship
{
	REL_0 = 0,
	REL_1 = 1,
	REL_2 = 2
};

class Object;
class Mult
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual float getMult();
};

class Player;
struct Coord3D;
class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_position; }
	Relationship getRelationship(const Object *other) const;
	void attemptHealing(float amount, const Object *source);
	char m_pad00[0x4];
	Tmpl *m_4; // +0x04
	char m_pad08[0x30];
private:
	Coord3D m_position; // +0x38
	char m_pad44[0x30];
public:
	int m_74; // +0x74
	char m_pad78[0x150];
	BitFlags<11> m_disabledMask; // +0x1C8
	char m_pad1CC[0x88];
	Mult *m_254; // +0x254
	char m_pad258[0x28];
	float m_280; // +0x280
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};


struct Inner
{
	char m_pad00[0x7C];
	float m_7c;
	unsigned char m_80;
	char m_pad81[0xA4 - 0x81];
	FXList *m_a4;
};

class ModuleData;
struct PlayerHealSpecialPowerModuleData;

class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(unsigned int options);					// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);		// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class PlayerHealSpecialPower : public SpecialPowerModule
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C8095(const Coord3D *loc);
	void rva004C7F5C(Object *obj); // the per-object heal
	const PlayerHealSpecialPowerModuleData *getPlayerHealSpecialPowerModuleData() const
	{
		return (const PlayerHealSpecialPowerModuleData *)m_moduleData;
	}
};

void PlayerHealSpecialPower::rva004C7F5C(Object *obj)
{
	const Inner *inner = (const Inner *)m_moduleData;
	if ((obj->m_4->m_11B & 8) != 0)
		return;
	if (((Thing *)obj)->isAnyKindOf(*(const BitFlags<69> *)((char *)inner + 0x88)) == 0)
		return;
	if (obj->m_74 != m_object->m_74)
	{
		if (obj->getRelationship(m_object) != REL_2)
			return;
	}
	if ((obj->m_4->m_108 & 0x80) != 0)
	{
		float *p280 = &obj->m_280;
		if (*p280 >= 0.0f)
		{
			if (99.0f > *p280) // retail's immutable float at RVA 0x007CEA18
				return;
		}
	}
	Mult *mult = obj->m_254;
	int zero = 0;
	if (mult == (Mult *)zero)
		return;
	float amount = inner->m_7c;
	if (inner->m_80 != (unsigned char)zero)
		amount *= mult->getMult();
	if (!(amount > 0.0f))
		return;
	obj->attemptHealing(amount, (const Object *)zero);
	FXList *fx = inner->m_a4;
	if (fx == (FXList *)zero)
		return;
	FXList::doFXObj(fx, obj, (const Object *)zero);
}
