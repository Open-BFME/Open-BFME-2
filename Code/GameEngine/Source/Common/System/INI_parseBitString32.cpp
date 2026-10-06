// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EB38, 277 bytes.
// Dedicated TU (same INI verb family as INI_parseRGBColor.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseBitString32): zero the dword, loop tokens via getNextTokenOrNull:
// NONE clears (and must stand alone), +/- names set/clear single bits, plain
// names clear-then-set; mixing the styles throws. BFME2 deltas (all
// retail-measured): the name lookup is the member scanIndexList(token, table)
// (pinned at 0x2BD39; BFME2 member-ifies BFME1's static), and every failure
// throws through the shared filler (code 2) with its own retail format
// ("INTERNAL ERROR! parseBitString32: No flag list provided!",
// "you may not mix normal and +- ops in bitstring lists") plus
// _CxxThrowException (DEBUG_CRASH/throw pairs in BFME1).

#define NULL 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	int scanIndexList(const char *token, ConstCharPtrArray flagList);
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);
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

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// ?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBitString32(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	ConstCharPtrArray flagList = (ConstCharPtrArray)userData;
	UnsignedInt *bits = (UnsignedInt *)store;

	if (flagList == NULL || flagList[0] == NULL) {
		throw INIException(2, "INTERNAL ERROR! parseBitString32: No flag list provided!");
	}

	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	// loop through all tokens
	for (const char *token = ini->getNextTokenOrNull(NULL); token != NULL; token = ini->getNextTokenOrNull(NULL)) {
		if (_strcmpi(token, "NONE") == 0) {
			if (foundNormal || foundAddOrSub) {
				throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
			}
			*bits = 0;
			break;
		}

		if (token[0] == '+') {
			if (foundNormal) {
				throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
			}
			Int bitIndex = ini->scanIndexList(token + 1, flagList);
			*bits |= (1 << bitIndex);
			foundAddOrSub = true;
		} else if (token[0] == '-') {
			if (foundNormal) {
				throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
			}
			Int bitIndex = ini->scanIndexList(token + 1, flagList);
			*bits &= ~(1 << bitIndex);
			foundAddOrSub = true;
		} else {
			if (foundAddOrSub) {
				throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
			}

			if (!foundNormal)
				*bits = 0;

			Int bitIndex = ini->scanIndexList(token, flagList);
			*bits |= (1 << bitIndex);
			foundNormal = true;
		}
	}
}
