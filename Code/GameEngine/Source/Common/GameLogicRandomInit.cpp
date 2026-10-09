// cl: /Ob0 /MD /DNDEBUG
// ?InitRandom@@YAXI@Z @ 0x00233F82 (69B) and ?InitGameLogicRandom@@YAXI@Z
// @ 0x00233FC7 (44B). Seeded-random initializers ported from Open-BFME-1
// Code/GameEngine/Source/Common/System/random_value.cpp
// (InitRandom/InitGameLogicRandom), with BFME2's fixed-seed override:
// when GlobalData's fixed seed is not -1 it seeds the generators instead
// of the passed seed. /Ob0 keeps the seedRandom calls
// out of line in retail's mov-reg form. This TU also owns the 48-byte static
// seedRandom body at 0x00233F3A: VC7.1 passes its arguments in eax/ecx and
// preserves edx only while the implementation is visible. An extern declaration
// changes the ABI to stack arguments and breaks all three existing bodies.
typedef unsigned int UnsignedInt;

static UnsignedInt theGameAudioSeed[6] =
{
	0xf22d0e56, 0x883126e9, 0xc624dd2f, 0x702c49c, 0x9e353f7d, 0x6fdf3b64
};

static UnsignedInt theGameClientSeed[6] =
{
	0xf22d0e56, 0x883126e9, 0xc624dd2f, 0x702c49c, 0x9e353f7d, 0x6fdf3b64
};

static UnsignedInt theGameLogicSeed[6] =
{
	0xf22d0e56, 0x883126e9, 0xc624dd2f, 0x702c49c, 0x9e353f7d, 0x6fdf3b64
};

static UnsignedInt theGameLogicBaseSeed;

// The override is GlobalData::m_fixedSeed (ZH GlobalData.h: "fixed random
// seed for game logic", default -1 = disabled), read through
// TheWritableGlobalData at VA 0x00DFE758: the matched -randomSeed parser
// (CommandLineRandomSeed.cpp, 0x003B9D2C) writes the same +0x1228 field of
// that global. Only that offset is modeled; everything else is padding.
class GlobalData
{
public:
	unsigned char m_pad[0x1228];
	UnsignedInt m_fixedSeed;	// +0x1228
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

static void seedRandom(UnsignedInt seed, UnsignedInt *seeds)
{
	UnsignedInt ax;

	ax = seed;
	ax += 0xf22d0e56;
	seeds[0] = ax;
	ax -= 0x69fbe76d;
	seeds[1] = ax;
	ax += 0x3df3b646;
	seeds[2] = ax;
	ax += 0x40dde76d;
	seeds[3] = ax;
	ax -= 0x68cd851f;
	seeds[4] = ax;
	ax += 0xd1a9fbe7;
	seeds[5] = ax;
}

// ?InitRandom@@YAXI@Z
void InitRandom(UnsignedInt seed)
{
	if (TheGlobalData != 0 && TheGlobalData->m_fixedSeed != (UnsignedInt)-1)
		seed = TheGlobalData->m_fixedSeed;
	seedRandom(seed, theGameAudioSeed);
	seedRandom(seed, theGameClientSeed);
	seedRandom(seed, theGameLogicSeed);
	theGameLogicBaseSeed = seed;
}

// ?InitGameLogicRandom@@YAXI@Z
void InitGameLogicRandom(UnsignedInt seed)
{
	if (TheGlobalData != 0 && TheGlobalData->m_fixedSeed != (UnsignedInt)-1)
		seed = TheGlobalData->m_fixedSeed;
	seedRandom(seed, theGameLogicSeed);
	theGameLogicBaseSeed = seed;
}

// Startup overload called by GameEngine::init at RVA 0x0022E2E4.
// BFME1 random_value.cpp (d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c)
// supplies the time(0) seeding role. BFME2 delegates to its existing seeded
// overload, preserving that overload's frame-override behavior.
// Retail 0x0023424C..0x0023425D: time import, InitRandom(seed), RET (17B).
extern "C" __declspec(dllimport) long __cdecl time(long *timer);
void InitRandom()
{
    InitRandom((UnsignedInt)time(0));
}
