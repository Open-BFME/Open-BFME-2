// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?scanIndexList@INI@@QAEHPBDPBQBD@Z, retail 0x002BD39, 76 bytes.
// Dedicated TU (same INI family as INI_scanLookupList.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::scanIndexList): checked name-to-index lookup over a 4-byte-per-entry
// table, throwing when the token is absent. BFME2 deltas (all
// retail-measured): the static is a thiscall member (ecx carries INI through,
// ret 8; BFME2 member-ifies BFME1's static), the search itself lives in the
// opaque worker at 0x2BCAB (pinned; takes the found flag and throw flag the
// member does not expose), and the miss throws through the shared filler with
// the retail format ("Token '%s' is not a valid member of the index list")
// plus _CxxThrowException (DEBUG_CRASH/throw pair in BFME1).

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
};

struct INIException
{
	INIException() {}
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's throwinfo at 0xCFE2FC). Content is
// never compared; the real chain lives in the retail image.
struct ScanIndexListThrowInfoAnchor { int a; int b; int c; int d; };
static const ScanIndexListThrowInfoAnchor scanIndexListThrowInfoAnchor = { 0, 0, 0, 0 };

// _rva002bcab_scanIndex, retail 0x002BCAB, 132 bytes. Index-list worker
// behind member scanIndexList: walks the null-terminated 4-byte-per-entry
// table with _strcmpi, reports through the found flag, returns the index.
// A null or empty table always throws INTERNAL ERROR; a clean miss returns 0
// when doThrow is clear and throws the Token tail otherwise (both noreturn
// through the shared INIException filler plus _CxxThrowException).
extern "C" int rva002bcab_scanIndex(const char *token, ConstCharPtrArray nameList, bool *found, bool doThrow)
{
	INIException e;
	ConstCharPtrArray cursor;
	int index;

	*found = false;
	if (nameList == 0 || nameList[0] == 0) {
		e.INIException::INIException(2, "INTERNAL ERROR! scanIndexList: No name list provided!");
		_CxxThrowException(&e, (const _s__ThrowInfo *)&scanIndexListThrowInfoAnchor); __assume(0);
	}
	cursor = nameList;
	index = 0;
	do {
		if (_strcmpi(*cursor, token) == 0) {
			*found = true;
			return index;
		}
		++cursor;
		++index;
	} while (*cursor != 0);
	if (doThrow) {
		e.INIException::INIException(3, "Token '%s' is not a valid member of the index list", token);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&scanIndexListThrowInfoAnchor); __assume(0);
	} else {
		return 0;
	}
	*found = true;
	return index;
}

// ?scanIndexList@INI@@QAEHPBDPBQBD@Z
int INI::scanIndexList(const char *token, ConstCharPtrArray nameList)
{
	bool found = false;
	int index = rva002bcab_scanIndex(token, nameList, &found, 0);
	if (!found) {
		INIException e(3, "Token '%s' is not a valid member of the index list", token);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&scanIndexListThrowInfoAnchor); __assume(0);
	}
	return index;
}
