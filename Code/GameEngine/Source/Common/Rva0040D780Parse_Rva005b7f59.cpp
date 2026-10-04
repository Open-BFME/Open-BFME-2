// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/stringinline /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

#include "StringInline.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	AsciiString getNextQuotedAsciiString();
};

class BfmeObjD540
{
public:
	void bfmeGoD540(AsciiString s);
};

void bfmeParseD780(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	AsciiString s = ini->getNextQuotedAsciiString();
	((BfmeObjD540 *)instance)->bfmeGoD540(s);
}
