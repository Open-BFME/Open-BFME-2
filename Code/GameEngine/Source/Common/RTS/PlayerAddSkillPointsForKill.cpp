// cl: /O1 /DNDEBUG /MD /arch:SSE
// Player::addSkillPointsForKill, retail 0x002AA6DE (120 bytes):
// ?addSkillPointsForKill@Player@@QAE_NPBVObject@@0@Z
// Identity (target): WorldBuilder's debug Player.cpp body of this name calls
// Object::testStatus, Object::getControllingPlayer, the experience
// tracker's 0x0039ACE3, 0x0039B683 on the +0x3BC member and 0x003805BB on
// the +0x08 member, as retail does.
// Donor (Zero Hour Player::addSkillPointsForKill): no killer or victim, or
// a victim under construction (status 2), earns nothing. BFME 2 deltas
// (target): the value is the victim's experience tracker (+0x264) value
// for the killer, counted only when the victim belongs to this player
// (else 0); it is added to the +0x3BC accumulator and handed to the +0x08
// member's 0x003805BB with true, whose answer is returned.
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

class Object;
class Player;

class Rva0039ACBD
{
public:
	int rva0039ACE3(const Object *killer);
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Rva0039ACBD *getExperienceTracker() const { return m_experienceTracker; }

private:
	unsigned char m_pad000[0x264];
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
	bool addSkillPointsForKill(const Object *killer, const Object *victim);

private:
	unsigned char m_pad000[0x08];
	Rva003805BB m_skillPoints; // +0x08
	unsigned char m_pad009[0x3BC - 0x09];
	Rva0039B683 m_accumulator; // +0x3BC
};

bool Player::addSkillPointsForKill(const Object *killer, const Object *victim)
{
	if (!killer || !victim)
		return false;
	if (victim->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return false;
	float skillValue = 0.0f;
	if (victim->getControllingPlayer() == this)
		skillValue = (float)victim->getExperienceTracker()->rva0039ACE3(killer);
	m_accumulator.rva0039B683(skillValue);
	return m_skillPoints.rva003805BB(skillValue, true);
}
