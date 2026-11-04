// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?rva0028DA67@Object@@QAEXXZ @0x0028DA67 82B: Object helper gating on +0x480 flag and template +0x618/+0x61C.
// Checks testStatus 0x57 and 2, then notifies via controlling Player and sets +0x480.
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
#include "../../../Include/Common/Player.h"
#include "../../../Include/Common/TeamBFME2.h"
#include "../../../Include/Common/TeamFactory.h"
extern TeamFactory *TheTeamFactory;

#include "../../../Include/Common/ThingTemplate.h"
#include "object.h"

void Object::rva0028DA67()
{
	if (m_480 != 0)
		return;
	if (m_template->m_commandPoints <= 0 && m_template->m_commandPointBonus <= 0)
		return;
	if (testStatus(RVA_57))
		return;
	if (testStatus(RVA_2))
		return;
	((Player *)getControllingPlayer())->addCommandPoints((Rva002A7588In *)this);
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
		Team *team = TheTeamFactory->findTeam(teamName);
		if (team != 0)
			player = team->getControllingPlayer();
	}
	if (player == 0)
		return;
	((Player *)player)->removeCommandPoints((Rva002A7588In *)this);
	m_480 = 0;
}

bool Object::rva0028DB0F(bool arg) const
{
	if (m_template->m_shockwaveResistance >= 100.0f)
	{
		if (!arg || !(m_template->m_kindof[5] & 0x80000000U))
			return true;
	}
	return false;
}



