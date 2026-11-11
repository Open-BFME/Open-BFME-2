// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?Rva002D2EEFPlayerFromMask@@YAPAVPlayer@@AAH@Z retail 0x002D2EEF (67B): pull
// players out of the mask with the rowed PlayerList::getEachPlayerFromMask
// (0x002A7BC9, which clears each bit it returns) until one passes the rowed
// 0x002AA231 test and its +0x34 record has the +0x151 flag set; NULL once the
// mask is empty. Names are address-derived; the test's own name
// (BfmeMemberRV::bfmeAskRV) is the ledger's spelling.

class Player;

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../Include/Common/BfmeMemberRV.h"

struct Rva002D2EEFRecord
{
	char m_pad00[0x151];
	bool m_151; // +0x151
};

struct Rva002D2EEFPlayer
{
	char m_pad00[0x34];
	Rva002D2EEFRecord *m_34; // +0x34
};

Player *Rva002D2EEFPlayerFromMask(int &mask)
{
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player && ((BfmeMemberRV *)player)->bfmeAskRV()) {
			Rva002D2EEFRecord *record = ((Rva002D2EEFPlayer *)player)->m_34;
			if (record && record->m_151)
				return player;
		}
	}
	return 0;
}
