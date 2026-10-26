// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?scanLookupList@INI@@QAEHPBDPBULookupListRec@@@Z, retail 0x002BD85, 108 bytes.
// Dedicated TU (same INI family as INI_parseBitString32.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::scanLookupList): linear case-insensitive walk over the name/value
// records, returning the hit value. BFME2 deltas (all retail-measured): the
// static is a thiscall member (ecx carries INI through, ret 8; BFME2
// member-ifies BFME1's static), and both failures (null table, missed token)
// throw through the shared filler plus _CxxThrowException (DEBUG_CRASH/throw
// pairs in BFME1) with the retail formats ("INTERNAL ERROR! scanLookupList:
// No name list provided!", "Token '%s' is not a valid member of the lookup
// list"), which prove the name outright.

#define NULL 0

struct LookupListRec
{
	const char *name;
	int value;
};

class INI
{
public:
	int scanLookupList(const char *token, const LookupListRec *lookupList);
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

// ?scanLookupList@INI@@QAEHPBDPBULookupListRec@@@Z
int INI::scanLookupList(const char *token, const LookupListRec *lookupList)
{
	if (lookupList == NULL || lookupList[0].name == NULL) {
		throw INIException(2, "INTERNAL ERROR! scanLookupList: No name list provided!");
	}

	// search for matching name
	for (const LookupListRec *lookup = &lookupList[0]; lookup->name; lookup++) {
		if (_strcmpi(lookup->name, token) == 0) {
			return lookup->value;
		}
	}

	throw INIException(3, "Token '%s' is not a valid member of the lookup list", token);
}
