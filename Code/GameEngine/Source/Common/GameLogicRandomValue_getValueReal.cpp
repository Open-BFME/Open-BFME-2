// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameLogicRandomValueReal@@YAMMMPADH@Z @ 0x00234092 (127B) trial port
// from Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameLogicRandomValueReal). Dedicated TU mirroring the landed
// GameClient twin at 0x00234111; adds the logic-random log-file block
// (game-side logging helper, strrchr import).
// Retail calls strrchr through msvcr71's IAT slot at VA 0x00BBA5A8.
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP

typedef float Real;
typedef unsigned int UnsignedInt;

// Shared writable multiplier initialized by RandomValueMultFactorInit.cpp.
extern "C" Real theMultFactor;

extern "C" UnsignedInt theGameLogicSeed[6];

static void *theLogicRandomLogFile;

// The existing _fprintf owner at RVA 0x002CEC42 appends to a game object;
// this is not the CRT stream operation declared by stdio.h.
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

UnsignedInt __fastcall randomValue(UnsignedInt *seed);

// ?GetGameLogicRandomValueReal@@YAMMMPADH@Z
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line)
{
	Real delta = hi - lo;
	Real rval;

	if (delta <= 0.0f)
		return hi;

	rval = ((Real)(randomValue(theGameLogicSeed)) * theMultFactor) * delta + lo;

	if (theLogicRandomLogFile)
		fprintf(theLogicRandomLogFile, "logicrandom = %f (%s, %i)\n", rval, strrchr(file, '\\') + 1, line);

	return rval;
}
