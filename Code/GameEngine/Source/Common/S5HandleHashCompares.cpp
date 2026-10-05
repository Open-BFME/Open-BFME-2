// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more of the hash-compare shape S3HandleCompareAssign.cpp already lands
// -- each reads the dword at +0x04 of two objects, hands them to a __cdecl
// helper and tests the answer against a constant that is NOT zero, so the
// helper returns a hash rather than an ordering.  The result is materialised
// as xor ecx,ecx / setne cl / mov al,cl -- a byte, so Bool.
//
// FOUR HELPERS, FOUR SENTINELS, PAIRED ONE TO ONE.  Each helper is only ever
// tested against its own constant, which is what a per-type hash of the empty
// or default value looks like; the constants are not shared and neither are
// the helpers.
//
// THE LEVER IS READ ORDER, not argument order.  Retail loads the OTHER's
// member into eax first and this's into ecx second, then pushes eax and ecx
// so this's member is the first argument.  Passing the two members straight
// into the call gives a third register; naming both as locals with the
// OTHER's read FIRST reproduces retail exactly.
//
// IDENTITY IS NOT RECOVERED.  Four classes at four addresses, each with one
// four-byte head and the compared dword at +0x04.
//
// This TU holds the four rows the BFME 1 donor sweep placed; the donor's
// other eight definitions are omitted.

unsigned int bfmeHash00010AFA(unsigned int left, unsigned int right);	// ILT 0x00010AFA
unsigned int bfmeHash00013412(unsigned int left, unsigned int right);	// ILT 0x00013412
unsigned int bfmeHash0002A473(unsigned int left, unsigned int right);	// ILT 0x0002A473
unsigned int bfmeHash0002BB70(unsigned int left, unsigned int right);	// ILT 0x0002BB70

enum { BFME_HASH_EQUAL_00010AFA = 0x993BA311 };
enum { BFME_HASH_EQUAL_00013412 = 0x342C2BE0 };
enum { BFME_HASH_EQUAL_0002A473 = 0x66DE9C79 };
enum { BFME_HASH_EQUAL_0002BB70 = 0xA69B3F6A };

class Gen_00528EC0
{
public:
	bool bfmeDiffers(const Gen_00528EC0 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054EC50
{
public:
	bool bfmeDiffers(const Gen_0054EC50 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0054EC80
{
public:
	bool bfmeDiffers(const Gen_0054EC80 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

class Gen_0056E190
{
public:
	bool bfmeDiffers(const Gen_0056E190 &other) const;

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
};

// ?bfmeDiffers@Gen_00528EC0@@QBE_NABV1@@Z		34B @0x003F2330
bool Gen_00528EC0::bfmeDiffers(const Gen_00528EC0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0002A473(mine, theirs) != BFME_HASH_EQUAL_0002A473;
}

// ?bfmeDiffers@Gen_0054EC50@@QBE_NABV1@@Z		34B @0x0056FA0C
bool Gen_0054EC50::bfmeDiffers(const Gen_0054EC50 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash0002BB70(mine, theirs) != BFME_HASH_EQUAL_0002BB70;
}

// ?bfmeDiffers@Gen_0054EC80@@QBE_NABV1@@Z		34B @0x0056FA2E
bool Gen_0054EC80::bfmeDiffers(const Gen_0054EC80 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00013412(mine, theirs) != BFME_HASH_EQUAL_00013412;
}

// ?bfmeDiffers@Gen_0056E190@@QBE_NABV1@@Z		34B @0x00435B4F
bool Gen_0056E190::bfmeDiffers(const Gen_0056E190 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return bfmeHash00010AFA(mine, theirs) != BFME_HASH_EQUAL_00010AFA;
}

// ?rva003F2352@Rva003F2352@@QAEPAV1@PAV1@0@Z 31B @0x003F2352
// Retail: dst->m_val = Rva003F1D7CHook(this->m_val, src->m_val); return dst.
// Evidence: contiguous after Gen_00528EC0::bfmeDiffers at 0x003F2330; same
// +4 read order (theirs into eax first, mine into ecx) and same obf slot
// 00DC34DC as bfmeHash0002A473; caller at 0x003F2956 passes (tmp, arg).
int Rva003F1D7CHook(int left, int right);

class Rva003F2352
{
public:
	Rva003F2352 *rva003F2352(Rva003F2352 *dst, Rva003F2352 *src);

private:
	char m_head[4];
	int m_val; // +0x04
};

Rva003F2352 *Rva003F2352::rva003F2352(Rva003F2352 *dst, Rva003F2352 *src)
{
	int theirs = src->m_val;
	int mine = m_val;

	dst->m_val = Rva003F1D7CHook(mine, theirs);
	return dst;
}

// ?rva0056FA50@Rva0056FA50@@QBE_NABV1@@Z @0x0056FA50 34B
// Evidence: unlock lane; contiguous after 0x0056FA2E same 34B hash-compare shape
// reads +0x04 of other then this hands to rowed Rva0056F5DEHook tests != 0xAA37ACC2
// returns byte via xor/setne/mov al; callers 0x00570833 0x0056FCD1
int Rva0056F5DEHook(int left, int right);

class Rva0056FA50
{
public:
	bool rva0056FA50(const Rva0056FA50 &other) const;

private:
	char m_head[4];
	int m_val; // +0x04
};

// ?rva00435B82@Rva00435B82@@QAEPAV1@PAV1@0@Z 31B @0x00435B82
// Retail: dst->m_val = Rva00435441Hook(this->m_val, src->m_val); return dst.
// Evidence: same 31B assign-through-hook shape as 0x003F2352 in this TU; +4 read order theirs-into-eax-first mine-into-ecx and rowed callee Rva00435441Hook; caller at 0x00435D5E passes tmp arg.
int Rva00435441Hook(int left, int right);

class Rva00435B82
{
public:
	Rva00435B82 *rva00435B82(Rva00435B82 *dst, Rva00435B82 *src);

private:
	char m_head[4];
	int m_val; // +0x04
};

Rva00435B82 *Rva00435B82::rva00435B82(Rva00435B82 *dst, Rva00435B82 *src)
{
	int theirs = src->m_val;
	int mine = m_val;

	dst->m_val = Rva00435441Hook(mine, theirs);
	return dst;
}

bool Rva0056FA50::rva0056FA50(const Rva0056FA50 &other) const
{
	int theirs = other.m_val;
	int mine = m_val;

	return Rva0056F5DEHook(mine, theirs) != (int)0xAA37ACC2;
}

// ?rva0056FA72@Rva0056FA72@@QBE_NABV1@@Z @0x0056FA72 34B
// Evidence: unlock lane; contiguous after 0x0056FA50 same 34B hash-compare shape
// reads +0x04 of other then this hands to rowed Rva0056F637Hook tests != 0xAA37ACC2
// returns byte via xor/setne/mov al; callers 0x0057086D 0x0056FCD6
int Rva0056F637Hook(int left, int right);

class Rva0056FA72
{
public:
	bool rva0056FA72(const Rva0056FA72 &other) const;

private:
	char m_head[4];
	int m_val; // +0x04
};

bool Rva0056FA72::rva0056FA72(const Rva0056FA72 &other) const
{
	int theirs = other.m_val;
	int mine = m_val;

	return Rva0056F637Hook(mine, theirs) != (int)0xAA37ACC2;
}