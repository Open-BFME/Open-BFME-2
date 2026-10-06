// cl: /DNDEBUG /MD
//
// ?attemptHealing@Object@@QAEXMPBV1@@Z @0x0028FE55 (82B).
// Object::attemptHealing(float amount, const Object *source): if the body
// module at this+0x254 is present, builds a 0x7C DamageInfo on the stack
// through the pinned ctor at 0x263895, sets damage type 7 (BFME HEALING),
// death type 1 (NONE), source ID from source+0x74 (or 0), amount, then calls
// the body's slot 1 (attemptHealing). Retail shape is body null test plus
// DamageInfo init plus 7/1 stores plus source-ID branch plus float movss
// plus vtable jmp slot 1. BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp:2184
// proves the name, signature and slot; BFME2 deltas are body at +0x254
// (BFME1 +0x200) and DamageInfo 0x7C with death at +0x1C amount at +0x20
// (BFME1 0x5C with death +0x18 amount +0x1C). Callers at 0x0028FFAA,
// 0x00398D9E, 0x00452747, 0x004572B1, 0x00458997 etc pass Object* this with
// float and Object* args.

typedef int ObjectID;
enum { INVALID_ID = 0 };

// 0x7C DamageInfo: source at +0x08, damage at +0x10, death at +0x1C,
// amount at +0x20. Its declared constructor is the pinned 0x263895 body.
class Rva00263895Member
{
public:
	Rva00263895Member();

	char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
	char m_pad0C[0x04]; // +0x0C
	int m_damageType; // +0x10
	char m_pad14[0x08]; // +0x14..0x1B
	int m_deathType; // +0x1C
	float m_amount; // +0x20
	char m_pad24[0x7C - 0x24];
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void attemptHealing(Rva00263895Member *info);
};

class Object
{
public:
	void attemptHealing(float amount, const Object *source);
	int getID() const { return m_id; }

private:
	char m_pad00[0x74];
	int m_id; // +0x74
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254
};

void Object::attemptHealing(float amount, const Object *source)
{
	BodyModuleInterface *body = m_body;
	if (body) {
		Rva00263895Member damageInfo;
		damageInfo.m_damageType = 7;
		damageInfo.m_deathType = 1;
		damageInfo.m_sourceID = source ? source->getID() : INVALID_ID;
		damageInfo.m_amount = amount;
		body->attemptHealing(&damageInfo);
	}
}
