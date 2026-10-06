// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F1BA, 34 bytes.
// Dedicated frameless TU (same INI verb family as INI_parseAngleReal.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parsePercentToReal): tokenize with the percent seps, scale to a
// fraction, store. BFME2 deltas (all retail-measured): the separator is the
// m_sepsPercent member at this+0x41C (direct read), and the scaling routes
// through the macro-aware scanReal times 0.01 (the matched dup_002EE10 row;
// BFME1's scanPercentToReal divides sscanf output by 100 instead). Name
// proven by ten FieldParse tables (MinHealth/MaxHealth/FriendlyOpacityMin/
// FirstPercentIndent/... percent fields).

class INI
{
public:
	const char *getNextToken(const char *seps);
	float dup_002EE10(const char *token);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);

private:
	char _pad[0x418];
	const char *m_seps;
	const char *m_sepsPercent;
};

// ?parsePercentToReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parsePercentToReal(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	*(float *)store = ini->dup_002EE10(ini->getNextToken(ini->m_sepsPercent));
}
