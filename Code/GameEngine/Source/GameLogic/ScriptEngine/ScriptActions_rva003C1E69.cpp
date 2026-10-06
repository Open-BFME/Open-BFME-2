// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?rva003C1E69@Rva003C1E69@@QAEPAVTeam@@ABVAsciiString@@0@Z @0x003C1E69 35B
// Team lookup via rowed getTeamNamed 0x003584E9 with false.
// Evidence: caller 0x003CD484; neighbours 0x003C1D70 0x003C1FAD;
// globals g_Va009FE16C; StringBase copy 0x000365F0.
#include "ascii_string.h"

class Team;
class Rva003C1E69;

class ScriptEngine {
public:
	Team *getTeamNamed(AsciiString name, bool flag);
};

extern class ScriptEngine *TheScriptEngine;

class Rva003C1E69 {
public:
	Team *rva003C1E69(const AsciiString &, const AsciiString &a2);
};

Team *Rva003C1E69::rva003C1E69(const AsciiString &, const AsciiString &a2)
{
	return TheScriptEngine->getTeamNamed(a2, false);
}
