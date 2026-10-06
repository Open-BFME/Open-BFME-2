// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// stlport
//
// ?rva004CBE31@Rva004CBE31@@QAE_NABVAsciiString@@PAURva002C99FB@@@Z, retail 0x004CBE31, 53 bytes.
// Guarded map fetch: reroll via rowed 0x004CBCF2 on this-0xC, false when
// this+4 float >= target+0x1D4 float (SSE comiss/jb), else forward key/out to
// rowed 0x004CBE04 on target at this-8 and return it. Same guard as sibling
// 0x004CBDCF but AsciiString key into map fetch.
// Evidence: callees rowed 0x004CBCF2 plus 0x004CBE04; no callers.
#include "ascii_string.h"

struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva002C99FB
{
	int m_first;
	OpaqueRefElement4 m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

class Rva004CBE31;

class RandomSoundSelectorClientBehavior
{
	friend class Rva004CBE31;
	void reroll();
};

class Rva004CBE04
{
public:
	bool rva004CBE04(const AsciiString &key, Rva002C99FB *out);
};

class Rva004CBE31
{
public:
	bool rva004CBE31(const AsciiString &key, Rva002C99FB *out);
};

bool Rva004CBE31::rva004CBE31(const AsciiString &key, Rva002C99FB *out)
{
	Rva004CBE04 *targ = *(Rva004CBE04 **)((char *)this - 8);
	((RandomSoundSelectorClientBehavior *)((char *)this - 0x0C))->reroll();
	float my = *(float *)((char *)this + 4);
	float targF = *(float *)((char *)targ + 0x1D4);
	if (my >= targF)
		return false;
	return targ->rva004CBE04(key, out);
}
