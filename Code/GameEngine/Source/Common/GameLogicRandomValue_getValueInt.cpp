// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameLogicRandomValue@@YAHHHPADH@Z @ 0x00233FF4 (86B) trial port
// from Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameLogicRandomValue). Dedicated TU mirroring the landed Real twin;
// integer divide plus the logic-random log-file block.
// Retail calls strrchr through msvcr71's IAT slot at VA 0x00BBA5A8.
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP

typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" UnsignedInt theGameLogicSeed[6];

static void *theLogicRandomLogFile;

// The existing _fprintf owner at RVA 0x002CEC42 appends to a game object;
// this is not the CRT stream operation declared by stdio.h.
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

UnsignedInt __fastcall randomValue(UnsignedInt *seed);

// ?GetGameLogicRandomValue@@YAHHHPADH@Z
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line)
{
	UnsignedInt delta = hi - lo + 1;
	Int rval;

	if (delta == 0)
		return hi;

	rval = ((Int)(randomValue(theGameLogicSeed) % delta)) + lo;

	if (theLogicRandomLogFile)
		fprintf(theLogicRandomLogFile, "logicrandom = %i (%s, %i)\n", rval, strrchr(file, '\\') + 1, line);

	return rval;
}
