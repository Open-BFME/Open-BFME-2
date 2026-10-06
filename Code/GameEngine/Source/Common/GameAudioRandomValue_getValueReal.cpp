// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameAudioRandomValueReal@@YAMMMPADH@Z @ 0x00234159 (72B) trial port
// from Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameAudioRandomValueReal). Dedicated TU mirroring the landed client
// Real twin; release drops the assert. Audio seed follows the client seed
// by 24 bytes.
typedef float Real;
typedef unsigned int UnsignedInt;

static const Real theMultFactor = 1.0f / 4294967295.0f;

static UnsignedInt theGameAudioSeed[6] =
{
	0xf22d0e56u, 0x883126e9u, 0xc624dd2fu, 0x0702c49cu, 0x9e353f7du, 0x6fdf3b64u
};

UnsignedInt __fastcall randomValue(UnsignedInt *seed);

// ?GetGameAudioRandomValueReal@@YAMMMPADH@Z
Real GetGameAudioRandomValueReal(Real lo, Real hi, char *file, int line)
{
	Real delta = hi - lo;
	Real rval;

	if (delta <= 0.0f)
		return hi;

	rval = ((Real)(randomValue(theGameAudioSeed)) * theMultFactor) * delta + lo;

	return rval;
}
