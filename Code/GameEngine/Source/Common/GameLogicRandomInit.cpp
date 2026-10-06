// cl: /Ob0 /MD /DNDEBUG
// ?InitRandom@@YAXI@Z @ 0x00233F82 (69B) and ?InitGameLogicRandom@@YAXI@Z
// @ 0x00233FC7 (44B). Seeded-random initializers ported from Open-BFME-1
// Code/GameEngine/Source/Common/System/random_value.cpp
// (InitRandom/InitGameLogicRandom), with BFME2's frame-override check:
// when TheGameLogic runs a frame other than -1 the frame number seeds the
// generators instead of the passed seed. /Ob0 keeps the seedRandom calls
// out of line in retail's mov-reg form; the static emits the same 48-byte
// body the ledger already owns at 0x00233F3A, so the calls resolve there.
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

// Upstream layout: GameLogic::m_frame read directly (no call). Only the
// +0x1228 offset is modeled; everything else is padding.
class GameLogic
{
public:
	unsigned char m_pad[0x1228];
	UnsignedInt m_frame;
};

static GameLogic *TheGameLogic;

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
	if (TheGameLogic != 0 && TheGameLogic->m_frame != (UnsignedInt)-1)
		seed = TheGameLogic->m_frame;
	seedRandom(seed, theGameAudioSeed);
	seedRandom(seed, theGameClientSeed);
	seedRandom(seed, theGameLogicSeed);
	theGameLogicBaseSeed = seed;
}

// ?InitGameLogicRandom@@YAXI@Z
void InitGameLogicRandom(UnsignedInt seed)
{
	if (TheGameLogic != 0 && TheGameLogic->m_frame != (UnsignedInt)-1)
		seed = TheGameLogic->m_frame;
	seedRandom(seed, theGameLogicSeed);
	theGameLogicBaseSeed = seed;
}
