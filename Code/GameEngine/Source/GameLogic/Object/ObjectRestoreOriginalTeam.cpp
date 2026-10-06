// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// Object::restoreOriginalTeam, retail 0x0029A0A6 (105B), from the WorldBuilder
// lead (Object.cpp) and Zero Hour's Object.cpp: with a current team (+0x304)
// and an original team name (+0x308), look the team up by name
// (TheTeamFactory 0x003A40F5) and switch to it (Object::setTeam) when it
// differs. BFME2 then kills the object (DamageType 8) when its new controlling
// player is flagged by Player 0x002AA22A (WorldBuilder's byte getter).
//
// Target facts: the lookup and the player flag keep address-derived names.

#include "ascii_string.h"

class Team;

class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};

class Player
{
};

class TeamFactory
{
public:
	Team *rva003A40F5(const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

enum DamageType
{
	DAMAGE_8 = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Object
{
public:
	void restoreOriginalTeam();
	void setTeam(Team *team);
	Player *getControllingPlayer() const;
	void kill(DamageType damageType, DeathType deathType);

private:
	unsigned char m_pad00[0x304];
	Team *m_team;
	AsciiString m_originalTeamName;
};

void Object::restoreOriginalTeam()
{
	if (m_team == 0 || m_originalTeamName.isEmpty())
		return;
	Team *origTeam = TheTeamFactory->rva003A40F5(m_originalTeamName);
	if (origTeam == 0 || m_team == origTeam)
		return;
	setTeam(origTeam);
	if (getControllingPlayer() && ((Rva002AA22AByteField *)getControllingPlayer())->get())
		kill(DAMAGE_8, DEATH_NORMAL);
}
