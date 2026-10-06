// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseUnsignedByte@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EE6D, 75 bytes.
// Dedicated ebp-frame TU (same INI scanner family as INI_parseByte.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parseUnsignedByte): range-checked unsigned-byte store. Same BFME2
// deltas as parseByte (explicit NULL seps, member scanInt, filler plus throw).

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanInt(const char *token);
	static void parseUnsignedByte(INI *ini, void *instance, void *store, const void *userData);
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


// ?parseUnsignedByte@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseUnsignedByte(INI *ini, void *instance, void *store, const void *userData)
{
	int value = ini->scanInt(ini->getNextToken(0));
	if (value < 0 || value > 0xFF) {
		throw INIException(3, "value out of range, expected 0..255");
	}
	*(unsigned char *)store = (unsigned char)value;
}
