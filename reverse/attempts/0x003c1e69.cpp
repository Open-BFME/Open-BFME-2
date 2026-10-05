// ?rva003C1E69@Rva003C1E69@@QAEPAVTeam@@ABVAsciiString@@0@Z
// partial score=0.97 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva003C1E69@Rva003C1E69@@QAEPTeam@@ABVAsciiString@@0@Z @0x003C1E69 35B
// Team lookup via rowed getTeamNamed 0x003584E9 with false.
// Evidence: caller 0x003CD484; neighbours 0x003C1D70 0x003C2662;
// globals g_Va009FE16C; StringBase copy 0x000365F0.
#include "ascii_string.h"

class Team;
class Rva003C1E69;

class ScriptEngine {
public:
	Team *getTeamNamed(AsciiString name, bool exact, void *extra) throw();
};

extern ScriptEngine *g_Va009FE16C;

class Rva003C1E69 {
public:
	Team *rva003C1E69(const AsciiString &, const AsciiString &a2);
};

// ?rva003C1E69@Rva003C1E69@@QAEPTeam@@ABVAsciiString@@0@Z present-unmatched
Team *Rva003C1E69::rva003C1E69(const AsciiString &, const AsciiString &a2)
{
	return g_Va009FE16C->getTeamNamed((AsciiString &)a2, false, this);
}
