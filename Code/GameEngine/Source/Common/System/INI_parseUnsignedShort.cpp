// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseUnsignedShort@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EF09, 76 bytes.
// Dedicated ebp-frame TU (same INI scanner family as INI_parseShort.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseUnsignedShort): range-checked unsigned-half store. Same BFME2
// deltas as parseShort (explicit NULL seps, member scanInt, filler plus throw).

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanInt(const char *token);
	static void parseUnsignedShort(INI *ini, void *instance, void *store, const void *userData);
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


// ?parseUnsignedShort@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseUnsignedShort(INI *ini, void *instance, void *store, const void *userData)
{
	int value = ini->scanInt(ini->getNextToken(0));
	if (value < 0 || value > 0xFFFF) {
		throw INIException(3, "value out of range, expected 0..65535");
	}
	*(unsigned short *)store = (unsigned short)value;
}
