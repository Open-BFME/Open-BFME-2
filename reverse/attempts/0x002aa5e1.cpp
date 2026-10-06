// ?addSkillPointsForDamage@Player@@QAE_NPAVObject@@PBV2@M@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE
// Player::addSkillPointsForDamage, retail 0x002AA5E1 (253 bytes):
// ?addSkillPointsForDamage@Player@@QAE_NPBVObject@@0M@Z
// Identity (target): WorldBuilder's debug Player.cpp:3341 body of this name
// (asserting the victim's experience tracker) has retail's tests and callee
// order: Object::testStatus, the attacker's kind-of tests,
// Object::rva002931F5, the 0x004A1828 lookup and its slot 0x20,
// Object::getControllingPlayer, the tracker's 0x0039ACBD, 0x0039B683 on the
// +0x3BC member and 0x003805BB on the +0x08 member.
// Body (target): no attacker or victim, or a victim under construction,
// earns nothing. The attacker can earn when its template has kind 3, not
// kind 7, and not both kinds 10 and 179; failing that, when the object from
// rva002931F5(false) has kind 3; failing that, when it has kind 90; and in
// the first two cases not when the 0x004A1828 interface's slot 0x20 says
// so. Damage to its own units earns nothing; otherwise the tracker value
// (+0x264) scaled by the damage argument, when positive, is accumulated and
// handed to 0x003805BB with true. Kind indices are read off the tested bits.
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

enum KindOfType
{
	KINDOF_3 = 3,
	KINDOF_7 = 7,
	KINDOF_10 = 10,
	KINDOF_90 = 90,
	KINDOF_179 = 179
};

class Object;
class Player;

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

class Rva0039ACBD
{
public:
	int rva0039ACBD(const Object *attacker, bool b);
};

class Rva004A1828Iface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual bool v08(); // slot 0x20
};

Rva004A1828Iface *Rva004A1828Get(const Object *obj);

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Object *rva002931F5(bool b);
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	Rva0039ACBD *getExperienceTracker() const { return m_experienceTracker; }

private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x264 - 0x08];
	Rva0039ACBD *m_experienceTracker; // +0x264
};

class Rva0039B683
{
public:
	void rva0039B683(float delta);
};

class Rva003805BB
{
public:
	bool rva003805BB(float value, bool b);
};

class Player
{
public:
	bool addSkillPointsForDamage(Object *attacker, const Object *victim, float damageScalar);

private:
	unsigned char m_pad000[0x08];
	Rva003805BB m_skillPoints; // +0x08
	unsigned char m_pad009[0x3BC - 0x09];
	Rva0039B683 m_accumulator; // +0x3BC
};

bool Player::addSkillPointsForDamage(Object *attacker, const Object *victim, float damageScalar)
{
	if (!attacker || !victim)
		return false;
	if (victim->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return false;

	bool canGain;
	if (attacker->isKindOf(KINDOF_3) && !attacker->isKindOf(KINDOF_7) &&
		!(attacker->isKindOf(KINDOF_10) && attacker->isKindOf(KINDOF_179)))
	{
		canGain = true;
	}
	else
	{
		canGain = false;
		Object *source = attacker->rva002931F5(false);
		if (source)
			canGain = source->isKindOf(KINDOF_3);
		if (!canGain && attacker->isKindOf(KINDOF_90))
			canGain = true;
	}
	if (canGain)
	{
		Rva004A1828Iface *iface = Rva004A1828Get(attacker);
		if (iface && iface->v08())
			canGain = false;
	}
	if (victim->getControllingPlayer() == this || !canGain)
		return false;

	float value = (float)victim->getExperienceTracker()->rva0039ACBD(attacker, false) * damageScalar;
	if (value <= 0.0f)
		return false;
	m_accumulator.rva0039B683(value);
	return m_skillPoints.rva003805BB(value, true);
}
