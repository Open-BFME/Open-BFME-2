// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F3FE, 264 bytes.
// Dedicated TU (same INI verb family as INI_parseRGBAColorInt.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseColorInt): R/G/B/A via getNextTokenOrNull plus stricmp match,
// getNextToken plus scanInt on hit, 0..255 range checks, A defaulting to 255
// when omitted, packed through GameMakeColor. BFME2 deltas (all
// retail-measured): the separator is the m_sepsColon member at this+0x420
// (direct read through the inline accessor, as in INI_parseRGBAColorInt.cpp),
// each of the three failures throws through the shared filler with its own
// retail format, and the GameMakeColor call is spelled out in Horner form:
// A<<24|R<<16|G<<8|B over byte-narrowed components (retail's movzx chain),
// proving BFME2's Color is a 32-bit ARGB pack.

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	int scanInt(const char *token);
	const char *getSepsColon() { return m_sepsColon; }
	static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);

private:
	char _pad[0x420];
	const char *m_sepsColon;
};

// BFME2's Color is a 32-bit ARGB pack (retail packs A<<24|R<<16|G<<8|B;
// GameMakeColor(r, g, b, a) callers pass components in R,G,B,A order).
typedef unsigned int Color;

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// ?parseColorInt@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseColorInt(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	const char *names[4] = { "R", "G", "B", "A" };
	int colors[4];
	for (int i = 0; i < 4; i++) {
		const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (token == NULL) {
			if (i < 3) {
				throw INIException(3, "can't omit value for color %s", names[i]);
			} else {
				// it's ok for A to be omitted.
				colors[i] = 255;
			}
		} else {
			// if present, the token must match.
			if (_strcmpi(token, names[i]) != 0) {
				throw INIException(3, "expected '%s'", names[i]);
			}
			colors[i] = ini->scanInt(ini->getNextToken(ini->getSepsColon()));
		}
		if (colors[i] < 0 || colors[i] > 255) {
			throw INIException(3, "color value %s=%i out of range (0..255)", names[i], colors[i]);
		}
	}

	//
	// assign the color components to the "Color" pointer at 'store', keep
	// the numbers as between 0 and 255
	//
	Color *theColor = (Color *)store;
	unsigned int packed = (unsigned char)colors[3];
	packed = (packed << 8) | (unsigned char)colors[0];
	packed = (packed << 8) | (unsigned char)colors[1];
	packed = (packed << 8) | (unsigned char)colors[2];
	*theColor = packed;
}
