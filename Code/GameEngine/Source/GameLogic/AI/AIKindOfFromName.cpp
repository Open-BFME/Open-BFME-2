// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?getAIKindOfFromName@@YAH PBD@Z, retail 0x004E8DE7, 112 bytes.
// Dedicated TU.
//
// Maps an AI-kind name to its 0-based index, throwing INIException on a miss.
// Evidence for the role: the throw formats "invalid AI_KINDOF" (retail literal
// at 0x8627E8) and the loop scans the 16-entry AI table at 0x9D0288
// (INFANTRY, ARCHER, PIKEMAN, CAVALRY, CREEP, CREEP_STRUCTURE, STRUCTURE,
// SIEGEWEAPON, EXPLORABLE_AREA, WALL, HERO, BATTLE_TOWER, SHIP_BATTLESHIP,
// SHIP_BOMBARD, SHIP_TRANSPORT, SHIP_SUICIDE). The two direct callers are the
// neighboring INI parsers: the single-token reader at 0x4E8E57 and the
// token-list reader at 0x4E8EA6. BFME2-added (no ZH/BFME1 source); the name
// follows the getSingleBitFromName/getNameFromSingleBit convention.
//
// Thrown type proven by the throwinfo at 0x8FE2FC: .?AVINIException@@, the
// BFME2 8-byte {message, code} rewrite of ZH's 4-byte INIException. The body
// fills it through the variadic helper at 0x2F681 (pinned under an opaque
// name; true name unknown) and throws via __CxxThrowException.
//
// Shaping notes (all load-bearing for the exact layout):
// - /Oy- keeps the ebp frame; /GX- suppresses funclets (no EH registration
//   around the AsciiString temp, matching retail).
// - The temp must die before the branch: inner braces put the releaseBuffer
//   call between the compare and the test, and `Bool match` survives it in
//   ebx (callee-saved) with the neg/sbb/inc ==0 materialization.
// - `if (i != -1) goto done` over the throw block forces retail's block order
//   (loop, check, throw, return). A plain `return i` there lets the throw
//   block sort before the check and the loop-exit jump lands wrong.
// - The throwinfo is pushed as the address of a TU-local anchor object so the
//   site is a push-immediate DIR32 (copied from retail). Calling through a
//   pointer or `throw e` instead emits a push-memory or a throw-copy that
//   retail does not have.
// - The TU-local AsciiString inherits publicly (the true header inherits
//   privately) so the free function can reach the truly-public compare;
//   layout and emitted calls are identical either way.

typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


// AIKindOfNames: the retail string table at VA 0xdd0288.
const char *AIKindOfNames[16] = {
	"INFANTRY",
	"ARCHER",
	"PIKEMAN",
	"CAVALRY",
	"CREEP",
	"CREEP_STRUCTURE",
	"STRUCTURE",
	"SIEGEWEAPON",
	"EXPLORABLE_AREA",
	"WALL",
	"HERO",
	"BATTLE_TOWER",
	"SHIP_BATTLESHIP",
	"SHIP_BOMBARD",
	"SHIP_TRANSPORT",
	"SHIP_SUICIDE",
};

struct INIException
{
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's throwinfo at 0x8FE2FC). Its content
// is never compared; the real chain lives in the retail image.
struct AIKindOfThrowInfoAnchor { int a; int b; int c; int d; };
static const AIKindOfThrowInfoAnchor aikindThrowInfoAnchor = { 0, 0, 0, 0 };

// ?getAIKindOfFromName@@YAH PBD@Z
int getAIKindOfFromName(const char *name)
{
	int i = 0;
	if (name == 0)
		goto fail;
	for (; i < 16; i++) {
		Bool match;
		{
			AsciiString tmp(AIKindOfNames[i]);
			match = (tmp.compare(name) == 0);
		}
		if (match)
			goto found;
	}
	goto fail;
found:
	if (i != -1)
		goto done;
fail:
	{
		INIException e(2, "invalid AI_KINDOF\n");
		_CxxThrowException(&e, (const _s__ThrowInfo *)&aikindThrowInfoAnchor);
	}
done:
	return i;
}
