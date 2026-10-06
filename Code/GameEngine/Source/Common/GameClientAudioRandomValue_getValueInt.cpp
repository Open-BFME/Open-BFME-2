// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameClientRandomValue@@YAHHHPADH@Z @ 0x0023404A (36B) and
// ?GetGameAudioRandomValue@@YAHHHPADH@Z @ 0x0023406E (36B) trial ports
// from Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameClientRandomValue, GetGameAudioRandomValue). Release builds drop
// the DEBUG_LOG block, leaving delta plus divide plus return. The client
// seed (RVA 0x9BA3A0) matches the landed client Real twin; the audio seed
// follows 24 bytes later, matching the BFME1 seed order.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef void FILE;

static UnsignedInt theGameClientSeed[6] =
{
	0xf22d0e56u, 0x883126e9u, 0xc624dd2fu, 0x0702c49cu, 0x9e353f7du, 0x6fdf3b64u
};

static UnsignedInt theGameAudioSeed[6] =
{
	0xf22d0e56u, 0x883126e9u, 0xc624dd2fu, 0x0702c49cu, 0x9e353f7du, 0x6fdf3b64u
};

UnsignedInt __fastcall randomValue(UnsignedInt *seed);

// ?GetGameClientRandomValue@@YAHHHPADH@Z
Int GetGameClientRandomValue(Int lo, Int hi, char *file, int line)
{
	UnsignedInt delta = hi - lo + 1;
	Int rval;

	if (delta == 0)
		return hi;

	rval = ((Int)(randomValue(theGameClientSeed) % delta)) + lo;

	return rval;
}

// ?GetGameAudioRandomValue@@YAHHHPADH@Z
Int GetGameAudioRandomValue(Int lo, Int hi, char *file, int line)
{
	UnsignedInt delta = hi - lo + 1;
	Int rval;

	if (delta == 0)
		return hi;

	rval = ((Int)(randomValue(theGameAudioSeed) % delta)) + lo;

	return rval;
}
