// cl: -DNDEBUG -MD -EHsc

#include "../../Include/Common/INI/INI.h"


// 0x005B7E02 is rowed as CreditsManager::addText (343B, Credits.cpp; WB
// CreditsManager::addText); same member + AsciiString shape, so this
// resolves to the rowed body instead of the unrowed spelling (sole U).
class CreditsManager
{
public:
	void addText(AsciiString s);
};

void bfmeParseD780(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	AsciiString asciiString = ini->getNextQuotedAsciiString();
	((CreditsManager *)instance)->addText(asciiString);
}
