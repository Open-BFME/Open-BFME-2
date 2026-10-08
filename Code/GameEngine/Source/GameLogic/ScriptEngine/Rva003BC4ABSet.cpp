// cl: /Ireference/shims/bfme2_ascii
// ?Rva003BC4ABSet@@YGXABVAsciiString@@H@Z @0x003BC4AB 38B: script set buildable override via template lookup.
// Evidence: push [esp+4] mov ecx,[0xDFF000]=g_009FF000 call rowed rva002D06CA 0x002D06CA test eax je ret 8; push [esp+8] mov ecx,[0xFE78C]=TheGameLogic push eax call rowed setBuildableStatusOverride 0x00246F71; caller 0x003CD142; sibling Rva003BC5CESet same (AsciiString,int) stdcall shape.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;

class ThingTemplate;
enum BuildableStatus
{
	BUILDABLE_STATUS_UNKNOWN = 0
};
class GameLogic
{
public:
	void setBuildableStatusOverride(const ThingTemplate *tt, BuildableStatus bs);
};
extern GameLogic *TheGameLogic;

void __stdcall Rva003BC4ABSet(const AsciiString &name, int status)
{
	void *tt = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&name);
	if (tt == 0)
		return;
	TheGameLogic->setBuildableStatusOverride((const ThingTemplate *)tt, (BuildableStatus)status);
}
