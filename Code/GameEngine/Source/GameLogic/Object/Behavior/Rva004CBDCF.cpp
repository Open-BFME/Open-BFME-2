// cl: /DNDEBUG /MD
//
// ?rva004CBDCF@Rva004CBDCF@@QAE_NHPAURva002C99FB@@@Z, retail 0x004CBDCF, 53 bytes.
// Guarded indexed fetch: reroll via rowed 0x004CBCF2 on this-0xC, false when
// this+4 float >= target+0x1D4 float (SSE comiss/jb), else forward idx/out to
// rowed 0x004CBDAC on target at this-8 and return it. Stride and floats from
// retail; honest owner unknown.
// Evidence: callees rowed 0x004CBCF2 plus 0x004CBDAC; no callers.
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

class Rva004CBDCF;

class RandomSoundSelectorClientBehavior
{
	friend class Rva004CBDCF;
	void reroll();
};

class Rva004CBDAC
{
public:
	bool rva004CBDAC(int idx, Rva002C99FB *out);
};

class Rva004CBDCF
{
public:
	bool rva004CBDCF(int idx, Rva002C99FB *out);
};

bool Rva004CBDCF::rva004CBDCF(int idx, Rva002C99FB *out)
{
	Rva004CBDAC *targ = *(Rva004CBDAC **)((char *)this - 8);
	((RandomSoundSelectorClientBehavior *)((char *)this - 0x0C))->reroll();
	float my = *(float *)((char *)this + 4);
	float targF = *(float *)((char *)targ + 0x1D4);
	if (my >= targF)
		return false;
	return targ->rva004CBDAC(idx, out);
}
