// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseByte@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EE22, 74 bytes.
// Dedicated ebp-frame TU (same INI scanner family as INI_scanBool.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseByte): range-checked signed-byte store. BFME2 deltas: getNextToken
// takes an explicit NULL separator set, scanInt is a member, and the failure
// runs through the shared filler at 0x002F681 ("value out of range, expected
// -128..127", no token argument) plus _CxxThrowException. Registered for the
// CrushableLevel/MountedCrusherLevel/MountedCrushableLevel/CrushKnockback
// byte fields (offsets 0x5F9..0x5FC).

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanInt(const char *token);
	static void parseByte(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};


// ?parseByte@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseByte(INI *ini, void *instance, void *store, const void *userData)
{
	int value = ini->scanInt(ini->getNextToken(0));
	if (value < -128 || value > 127) {
		throw INIException(3, "value out of range, expected -128..127");
	}
	*(unsigned char *)store = (unsigned char)value;
}
