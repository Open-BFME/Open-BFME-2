// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva003BF9C8Do@@YGXABVAsciiString@@@Z @0x003BF9C8 50B.
// Script team action via landed rva003570D1 prototype then handler at
// proto+8 forwarding proto.
// Evidence: rowed rva003570D1 rva002A9DCF copy-ctor, extern g_Va009FE16C,
// caller 0x003CB896, ret 4, prev/next Hunt/Do pattern.
#include "ascii_string.h"

class TeamPrototype;
class Rva002A9DCF
{
public:
	void rva002A9DCF(void *a1);
};

class ScriptEngine
{
public:
	TeamPrototype *rva003570D1(AsciiString name);
};

class TeamPrototype
{
public:
	char m_pad00[8];
	Rva002A9DCF *m_handler08;
};

extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BF9C8Do(const AsciiString &a1)
{
	TeamPrototype *proto = TheScriptEngine->rva003570D1(a1);
	if (proto == 0)
		return;
	Rva002A9DCF *handler = proto->m_handler08;
	if (handler == 0)
		return;
	handler->rva002A9DCF(proto);
}
