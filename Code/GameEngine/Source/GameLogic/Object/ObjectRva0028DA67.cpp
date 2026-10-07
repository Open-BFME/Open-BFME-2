// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?rva0028DA67@Object@@QAEXXZ @0x0028DA67 82B: Object helper gating on +0x480 flag and template +0x618/+0x61C.
// Checks testStatus 0x57 and 2, then notifies via controlling Player Rva002A9B58 and sets +0x480.
// ?rva0028DAB9@Object@@QAEXXZ @0x0028DAB9 86B: One-shot team-player refresh gating on +0x480 flag.
// Evidence: neighbours ObjectRva0028DA28 and ObjectGetVisionRange share Object shard and flags;
// callees testStatus getControllingPlayer and Rva dict are rowed; unblocks 0x002A9D02 and 0x002934E7.
#include "ascii_string.h"

enum ObjectStatusTypes
{
	RVA_2 = 2,
	STATUS_3E = 0x3E,
	RVA_57 = 0x57
};
class Player;
struct Rva002A7588In;
class Rva002A9B58
{
public:
	void rva002A9B35(Rva002A7588In *in);
	void rva002A9B58(Rva002A7588In *in);
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

class ThingTemplate
{
public:
	unsigned char m_pad00[0x618];
	int m_618; // +0x618
	int m_61C; // +0x61C
};
class Object
{
public:
	void rva0028DA67();
	void rva0028DAB9();
	bool testStatus(ObjectStatusTypes s) const;
	Player *getControllingPlayer() const;
private:
	unsigned char m_pad00[0x04];
	ThingTemplate *m_tmpl; // +0x04
	unsigned char m_pad08[0x480 - 0x08];
	unsigned char m_480; // +0x480
};

void Object::rva0028DA67()
{
	if (m_480 != 0)
		return;
	if (m_tmpl->m_618 <= 0 && m_tmpl->m_61C <= 0)
		return;
	if (testStatus(RVA_57))
		return;
	if (testStatus(RVA_2))
		return;
	((Rva002A9B58 *)getControllingPlayer())->rva002A9B35((Rva002A7588In *)this);
	m_480 = 1;
}

void Object::rva0028DAB9()
{
	if (m_480 == 0)
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

