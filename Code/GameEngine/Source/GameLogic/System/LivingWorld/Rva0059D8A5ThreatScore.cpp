// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0059D8A5@Rva0059DD3F@@QAEIHHPAVRva0059CFAACallee@@@Z
// retail 0x0059D8A5..0x0059D90C (103 bytes) thiscall RET 0xC; this unused.
//
// Resolves the region id to its territory key through the rowed
// Rva004FF997Owner::rva004FF997 (0x004FF997) on the armies object then adds
// 10 when the closest hero (0x004FFB00 thiscall RET 0xC: entry in EAX and
// distance through the third argument) is nearer than three steps and
// another 10 when 0x00500659 (rowed; returns vector<ObjectID> by value and
// the caller frees it: the inlined destructor calling _free 0x00030830)
// counts fewer than three defenders. Both counts share one local.
// Evidence (target): both retail callers (0x0059DE4A 0x0059DE6A) sit in
// 0x0059DD3F and pass its own ECX (mov ecx edi) so the receiver is the
// object the rowed 0x004FB27E reaches at +0x8C and calls 0x0059DD3F on (the
// Rva0059DD3F view there); they keep both results in locals compared
// unsigned (jbe) hence the unsigned return. WorldBuilder twin 0x014FF410
// (unnamed) has the same calls and +10 steps. Names are address-derived.

#include <vector>

enum ObjectID
{
	INVALID_ID = 0
};

struct Rva004FFB00Hero;

class Rva0059CFAACallee
{
public:
	_STL::vector<ObjectID> rva00500659(int playerId, int *territory, int *count);
	Rva004FFB00Hero *rva004FFB00(int playerId, int *territory, int *distance);
};

class Rva004FF997Owner
{
public:
	int rva004FF997(int id);
};

class Rva0059DD3F
{
public:
	unsigned int rva0059D8A5(int playerId, int regionId, Rva0059CFAACallee *armies);
};

unsigned int Rva0059DD3F::rva0059D8A5(int playerId, int regionId, Rva0059CFAACallee *armies)
{
	unsigned int score = 0;
	int count = 0;
	int *territory = (int *)((Rva004FF997Owner *)armies)->rva004FF997(regionId);
	armies->rva004FFB00(playerId, territory, &count);
	if (count < 3)
		score += 10;
	armies->rva00500659(playerId, territory, &count);
	if (count < 3)
		score += 10;
	return score;
}
