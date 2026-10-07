// ?rva0028DAB9@Object@@AAEXXZ
// partial score=0.98 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?rva0028DAB9@Object@@AAEXXZ @0x0028DAB9 86B.
// One-shot team-player refresh gated by +0x480 flag: when set, refresh via
// controlling Player and TeamFactory lookup of original team name at +0x308,
// then notify via Player Rva002A9B58 and clear +0x480. Returns early when
// +0x480 is clear or no Player. Evidence: callers 0x0028FC42 onDestroy and
// 0x004BDA9B ActiveBody; callees testStatus 0x4E536 getControllingPlayer
// 0x28AFA9 TeamFactory rva003A40F5 Team getControllingPlayer Rva002A9B58
// rowed or pinned; TheTeamFactory global; layout from ObjectRestoreOriginalTeam
// +0x304 team +0x308 AsciiString and ObjectRva0028DA67 +0x480 flag idiom.
#include "ascii_string.h"

class Player;
struct Rva002A7588In;

class Rva002A9B58
{
public:
	void rva002A9B58(Rva002A7588In *p);
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class TeamFactory
{
public:
	Team *rva003A40F5(const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

enum ObjectStatusTypes
{
	STATUS_3E = 0x3E
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes s) const;
private:
	void rva0028DAB9();
	unsigned char m_pad00[0x480];
	bool m_480;
};

void Object::rva0028DAB9()
{
	if (m_480 == false)
		return;
	Player *player = getControllingPlayer();
	if (testStatus(STATUS_3E))
	{
		const AsciiString &teamName = *(const AsciiString *)((const char *)this + 0x308);
		Team *team = TheTeamFactory->rva003A40F5(teamName);
		if (team != 0)
			player = team->getControllingPlayer();
	}
	if (player == 0)
		return;
	((Rva002A9B58 *)player)->rva002A9B58((Rva002A7588In *)this);
	m_480 = 0;
}
