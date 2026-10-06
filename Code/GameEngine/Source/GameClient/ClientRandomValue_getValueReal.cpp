// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameClientRandomValueReal@@YAMMMPADH@Z @ 0x00234111 (72B) trial port
// from Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (69B). Dedicated TU so GameClientRandomVariable::getValue keeps its
// pin-call shape.
typedef float Real;
typedef unsigned int UnsignedInt;

static const Real theMultFactor = 1.0f / 4294967295.0f;

static UnsignedInt theGameClientSeed[6] =
{
	0xf22d0e56u, 0x883126e9u, 0xc624dd2fu, 0x0702c49cu, 0x9e353f7du, 0x6fdf3b64u
};

UnsignedInt __fastcall randomValue(UnsignedInt *seed);

// ?GetGameClientRandomValueReal@@YAMMMPADH@Z
Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, int line)
{
	Real delta = hi - lo;
	Real rval;

	if (delta <= 0.0f)
		return hi;

	rval = ((Real)(randomValue(theGameClientSeed)) * theMultFactor) * delta + lo;

	return rval;
}
