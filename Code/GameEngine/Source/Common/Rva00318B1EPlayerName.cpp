// cl: /O1 /Ireference/shims/bfme2_ascii
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// ?rva00318B1E@Rva00318B1E@@QBEABVAsciiString@@XZ @ 0x00318B1E: look the
// player id at +0x54 up through TheLivingWorldLogic (rowed
// Rva002BA8F1Logic::find(int, unsigned int *) 0x002B51F8, null index) and
// return the AsciiString at +4 of the found player's +0x40 record, else
// AsciiString::TheEmptyString (VA 0x00DE0878).
// Boundary: the body runs 0x00318B1E..0x00318B3F; its empty-string tail
// 0x00318B39 (the je target) is rowed separately as Rva00318B39Get, so this
// row claims the 27 bytes before it. Names are address-derived.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva00318B1ERecord
{
	int m_00;
	AsciiString m_name;	// +0x04
};

class Rva002E2903Player
{
public:
	char m_pad00[0x40];
	Rva00318B1ERecord *m_40;
};

#include "../../Include/GameLogic/Rva002BA8F1Logic.h"

class Rva00318B1E
{
public:
	const AsciiString &rva00318B1E() const;
private:
	char m_pad00[0x54];
	int m_playerId;	// +0x54
};

const AsciiString &Rva00318B1E::rva00318B1E() const
{
	Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(m_playerId, 0);
	if (player)
		return player->m_40->m_name;
	return AsciiString::TheEmptyString;
}
