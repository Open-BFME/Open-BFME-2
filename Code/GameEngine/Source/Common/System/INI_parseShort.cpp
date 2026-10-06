// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseShort@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EEB9, 79 bytes.
// Dedicated ebp-frame TU (same INI scanner family as INI_parseByte.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseShort): range-checked signed-half store. Same BFME2 deltas as
// parseByte (explicit NULL seps, member scanInt, filler plus throw).

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanInt(const char *token);
	static void parseShort(INI *ini, void *instance, void *store, const void *userData);
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


// ?parseShort@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseShort(INI *ini, void *instance, void *store, const void *userData)
{
	int value = ini->scanInt(ini->getNextToken(0));
	if (value < -32768 || value > 32767) {
		throw INIException(3, "value out of range, expected -32768..32767");
	}
	*(unsigned short *)store = (unsigned short)value;
}
