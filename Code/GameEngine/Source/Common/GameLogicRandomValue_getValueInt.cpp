// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameLogicRandomValue@@YAHHHPADH@Z @ 0x00233FF4 (86B) trial port
// from Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameLogicRandomValue). Dedicated TU mirroring the landed Real twin;
// integer divide plus the logic-random log-file block.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef void FILE;

static UnsignedInt theGameLogicSeed[6] =
{
	0xf22d0e56u, 0x883126e9u, 0xc624dd2fu, 0x0702c49cu, 0x9e353f7du, 0x6fdf3b64u
};

static FILE *theLogicRandomLogFile;

extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *string, int c);
extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

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

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?entEnragedInitialValue@@YAHHIPBXH@Z=?GetGameLogicRandomValue@@YAHHHPADH@Z")
