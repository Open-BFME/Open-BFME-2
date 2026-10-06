// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameLogicRandomValueReal@@YAMMMPADH@Z @ 0x00234092 (127B) trial port
// from Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameLogicRandomValueReal). Dedicated TU mirroring the landed
// GameClient twin at 0x00234111; adds the logic-random log-file block
// (fprintf via the statically linked CRT body, strrchr import).
typedef float Real;
typedef unsigned int UnsignedInt;
typedef void FILE;

static const Real theMultFactor = 1.0f / 4294967295.0f;

static UnsignedInt theGameLogicSeed[6] =
{
	0xf22d0e56u, 0x883126e9u, 0xc624dd2fu, 0x0702c49cu, 0x9e353f7du, 0x6fdf3b64u
};

static FILE *theLogicRandomLogFile;

extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *string, int c);
extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

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
