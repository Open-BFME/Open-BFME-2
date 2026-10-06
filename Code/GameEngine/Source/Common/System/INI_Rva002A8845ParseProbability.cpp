// cl: /DNDEBUG /MD /GX-
// Rva002A8845_ParseProbability (retail 0x002A8845, 118 bytes). Parses the
// EconomyUpgradeProbability / SpecialPowerActivationProbability /
// OffensiveTacticActivationProbability entries of the table at 0xBFD768
// (used by the DifficultyTuning temp through initFromINI). Token 0 is the
// numerator (stored at +0x00), token 1 is a separator, token 2 is the
// denominator (stored at +0x04, must be >= 1 or INIException 3 fires
// through _CxxThrowException). All callees are rowed: getNextToken at
// 0x002DF97, scanInt at 0x002ECCF, getNextTokenOrNull at 0x002DEED,
// INIException ctor at 0x002F681 and _CxxThrowException at 0x00629094
// (pinned). The struct name is address-derived; the owning struct is
// BFME2-new (no BFME1 donor).

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	int scanInt(const char *token);
	static void Rva002A8845_ParseProbability(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);

	char *mFailureMessage;
	int m_argumentCount;
	INIException(const INIException &that);
	~INIException();
};


// ?Rva002A8845_ParseProbability@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002A8845_ParseProbability(INI *ini, void *, void *store, const void *)
{
	int *slot = (int *)store;
	int index = 0;
	for (const char *token = ini->getNextToken(0); token != 0; token = ini->getNextTokenOrNull(0), index++) {
		switch (index) {
		case 0:
			slot[0] = ini->scanInt(token);
			break;
		case 2: {
			int denominator = ini->scanInt(token);
			slot[1] = denominator;
			if (denominator < 1) {
				throw INIException(3, "invalid Probability Denominator must be greater than zero (%d)", denominator);
			}
			break;
		}
		default:
			break;
		}
	}
}
