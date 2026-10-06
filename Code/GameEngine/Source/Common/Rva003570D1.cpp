// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?rva003570D1@ScriptEngine@@QAEPAVTeamPrototype@@VAsciiString@@@Z @0x003570D1 95B.
// TeamPrototype lookup by resolved name: resolveName via same this then
// TeamFactory findPrototype with tmp and by-value name; false if null.
// Evidence: rowed EH_prolog releaseBuffer, pins resolveName findPrototype,
// extern TheTeamFactory, callers 0x003BF9C8 0x003BF9FA 0x003B3836 0x003C7BBB.
#include "ascii_string.h"

class TeamPrototype;
class TeamFactory;
class BfmeTab1026;

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &a, const AsciiString &b);
};

extern TeamFactory *TheTeamFactory;

class ScriptEngine
{
public:
	TeamPrototype *rva003570D1(AsciiString name);
};

TeamPrototype *ScriptEngine::rva003570D1(AsciiString name)
{
	AsciiString tmp = ((Rva002046C0Owner *)this)->resolveName(name);
	TeamPrototype *proto = ((Rva0039FE6COwner *)TheTeamFactory)->findPrototype(tmp, name);
	return proto;
}
