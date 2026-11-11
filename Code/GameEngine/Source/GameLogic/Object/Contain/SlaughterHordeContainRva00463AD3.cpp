// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00463AD3@Rva00463AD3@@QAEXH@Z, retail 0x00463AD3..0x00463C6E (411
// bytes, RET 4). The rowed SlaughterHordeContain slot 120 (0x004642D3) calls
// it on every contained-list value (an Object) with the contain object as
// receiver; the caller's pinned integer spelling is kept. WorldBuilder's twin
// 0x0119A6C0 (OpenContain.cpp asserts) gives the flow, close to Zero Hour's
// OpenContain::processDamageToContained body for one rider:
//   - a rider of the (0x5E, 0x61) kind mask is hidden and destroyed;
//   - with the module data's +0x83 flag it is removed through the contain
//     interface at +0x20 (slot 0xA4), flung along its transform's X column
//     (Z 1) scaled by a random 2..5 through the +0x25C physics consumer
//     0x003909FA, killed, and the kill credited (rowed 0x00294D61) to the
//     object the owner's +0x254 module names through its slot 0x3C;
//   - otherwise it takes unresistable damage (type 8, death 3) of its max
//     health times the data's +0x6C percentage from the owner, and is killed
//     when it survives a full (1.0) percentage.

#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

template <int N> class BitFlags
{
public:
	unsigned m_words[7];
};

struct Rva0006EE7A : public BitFlags<69>
{
	Rva0006EE7A(int unused, int b1, int b2);
};

#include "../../../Common/Thing/thing.h"
#include "../../../../Include/GameClient/Drawable.h"


enum DamageType { DAMAGE_UNRESISTABLE_8 = 8 };
enum DeathType { DEATH_0 = 0 };

// Layout of the 0x68-byte input record (rowed ctor Rva00263653); the
// forwarder below constructs it, so this view declares no constructor.
class Rva00263653
{
public:
	const void *m_vptr;
	ObjectID m_sourceID;	// +0x04
	int m_08;
	int m_damageType;	// +0x0C
	int m_10;
	int m_14;
	int m_deathType;	// +0x18
	float m_amount;		// +0x1C
	unsigned char m_rest[0x68 - 0x20];
};

// Retail builds it through the rowed initializer Rva00263895Member
// (Rva00263895Init.cpp); the inline forwarder binds the call there.
class Rva00263895Member
{
public:
	Rva00263895Member() throw();	// 0x00263895
};
class DamageInfo
{
public:
	__declspec(dllimport) __forceinline DamageInfo() { ((Rva00263895Member *)this)->Rva00263895Member::Rva00263895Member(); }
	const void *m_vptr;
	Rva00263653 in;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};

#include "../../../../Include/GameLogic/Module/BodyModule.h"

// WWMath Vector3 as the WorldBuilder twin uses it (vector3.h operator*=).
#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../Include/Common/Rva003909FAObj.h"

struct Rva00463AD3Credit
{
	char m_pad00[8];
	ObjectID m_id;		// +0x08
};

class Rva00463AD3CreditSource
{
public:
	virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
	virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
	virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
	virtual void vf30(); virtual void vf34(); virtual void vf38();
	virtual Rva00463AD3Credit *getCredit();	// slot 0x3C
};

class Object : public Thing
{
public:
	void kill(DamageType damageType, DeathType deathType);
	void attemptDamage(DamageInfo *damageInfo);
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

	char m_pad60[0x74 - 0x60];
	ObjectID m_id;			// +0x74
	char m_pad78[0x254 - 0x78];
	union
	{
		BodyModuleInterface *m_body;	// +0x254
		Rva00463AD3CreditSource *m_creditSource;
	};
	char m_pad258[0x25C - 0x258];
	Rva003909FAObj *m_physics;	// +0x25C
	char m_pad260[0x438 - 0x260];
	unsigned char m_privateStatus;	// +0x438
};

class Rva00463AD3
{
public:
	void rva00463AD3(int value);
};

class Rva00294D61
{
public:
	void report(Object*,int);
};

struct Rva00463AD3Data
{
	char m_pad00[0x6C];
	float m_damagePercentageToUnits;	// +0x6C
	char m_pad70[0x83 - 0x70];
	bool m_flingRiders;			// +0x83
};

class Rva00463AD3ContainInterface
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40)
#undef V
	virtual void removeFromContain(Object *obj, bool exposeStealthUnits);	// slot 0xA4
};

class Rva00463AD3Contain
{
public:
	void *m_vtbl;
	Rva00463AD3Data *m_data;		// +0x04
	Object *m_object;			// +0x08
	char m_pad0C[0x20 - 0x0C];
	Rva00463AD3ContainInterface m_contain;	// +0x20
};

void Rva00463AD3::rva00463AD3(int value)
{
	Rva00463AD3Contain *self = reinterpret_cast<Rva00463AD3Contain *>(this);
	Object *rider = reinterpret_cast<Object *>(value);
	const Rva00463AD3Data *data = self->m_data;

	if (rider->isAnyKindOf(Rva0006EE7A(0, 0x5E, 0x61)))
	{
		if (rider->getDrawable())
			rider->getDrawable()->setDrawableHidden(true);
		TheGameLogic->destroyObject(rider);
		return;
	}

	if (data->m_flingRiders)
	{
		self->m_contain.removeFromContain(rider, false);
		Rva003909FAObj *physics = rider->m_physics;
		if (physics)
		{
			Vector3 dir(rider->m_transform[0][0], rider->m_transform[1][0], 1.0f);
			float scale = (float)GetGameLogicRandomValue(2, 5,
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\OpenContain.cpp",
				0x8DE);
			dir *= scale;
			Coord3D force;
			force.x = dir.X;
			force.y = dir.Y;
			force.z = dir.Z;
			physics->consume(&force, 0, 0);
		}
		rider->kill(DAMAGE_UNRESISTABLE_8, DEATH_0);
		Rva00463AD3CreditSource *source = self->m_object->m_creditSource;
		if (source)
		{
			Rva00463AD3Credit *credit = source->getCredit();
			if (credit)
			{
				Object *killer = TheGameLogic->findObjectByID(credit->m_id);
				if (killer)
					reinterpret_cast<Rva00294D61 *>(killer)->report(rider, 1);
			}
		}
		return;
	}

	const Rva00463AD3Data *damageData = self->m_data;
	float damage = rider->m_body->getMaxHealth() * damageData->m_damagePercentageToUnits;
	DamageInfo damageInfo;
	damageInfo.in.m_damageType = DAMAGE_UNRESISTABLE_8;
	damageInfo.in.m_deathType = 3;
	damageInfo.in.m_sourceID = self->m_object->m_id;
	damageInfo.in.m_amount = damage;
	rider->attemptDamage(&damageInfo);
	if (!rider->isEffectivelyDead() && self->m_data->m_damagePercentageToUnits == 1.0f)
		rider->kill(DAMAGE_UNRESISTABLE_8, DEATH_0);
}
