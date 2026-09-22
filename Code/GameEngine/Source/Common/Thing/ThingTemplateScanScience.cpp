// cl: /O1 /DNDEBUG /MD /EHsc
//
// Retail RE: ?scanScience@INI@@SA?AW4ScienceType@@PBD@Z @0x00338A8D (11B).
//
// BFME1-attested INI static: a frameless forwarder pushing the token,
// loading the ScienceStore singleton global (0x00DFE0E0, DIR32-masked) and
// tail-calling the rowed worker at 0x001FF65D. Four science-parse callers
// (0x00339700, 0x00339B1A, 0x0033A396, 0x0033EAE1).

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ScienceStore
{
public:
	ScienceType lookupScience(const char *token) const;
};

extern ScienceStore *TheScienceStore;

class INI
{
public:
	static ScienceType scanScience(const char *token);
};

// ?scanScience@INI@@SA?AW4ScienceType@@PBD@Z
ScienceType INI::scanScience(const char *token)
{
	return TheScienceStore->lookupScience(token);
}
