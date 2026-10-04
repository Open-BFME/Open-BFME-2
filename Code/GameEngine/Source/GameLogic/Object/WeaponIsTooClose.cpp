// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
// ?isTooClose@Weapon@@QBE_NPBVObject@@PBUCoord3D@@@Z @0x002C9B3D (67B).
// Weapon::isTooClose(source, pos): minRange==0 -> false; else shrunkenDistSqr
// (Object::rva002C97E8 of source position vs pos) < sqr(minRange).
// Evidence: [ecx+4] is WeaponTemplate (getMinimumAttackRange rowed 0x002C92FA);
// caller passes source+0x38 and pos to rowed rva002C97E8; ZH donor Weapon.cpp
// isTooClose(const Object*, const Coord3D*) with PartitionManager replaced by
// the BFME2 Object shrunken-distance body.
typedef float Real;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	float rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	float rva00263763(const void *other) const;

private:
	char m_pad00[0x38];
public:
	Coord3D m_position; // +0x38
};

class WeaponTemplate
{
public:
	float getMinimumAttackRange() const;
	char m_pad00[0x13c];
	int m_13c; // +0x13c
};

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;


class Weapon
{
public:
	bool isTooClose(const Object *source, const Coord3D *pos) const;
	bool rva002C9AFE(const Object *source, const void *other) const;
	float rva002C957E() const;
	bool rva002C95F0() const;
	void rva002C95DE(int offset);
	void rva002C959E();

private:
	char m_pad00[4];
	const WeaponTemplate *m_template; // +4
	char m_pad08[0x50 - 8]; // +8..0x50
	volatile unsigned int m_50; // +0x50 volatile forces m_50-first load order (retail 17B vs 16B A1 size opt)
	int m_54; // +0x54
	int m_58; // +0x58
};

bool Weapon::isTooClose(const Object *source, const Coord3D *pos) const
{
	float minRange = m_template->getMinimumAttackRange();
	if (minRange == 0.0f)
		return false;
	float distSqr = source->rva002C97E8(&source->m_position, pos);
	if (distSqr < minRange * minRange)
		return true;
	return false;
}

bool Weapon::rva002C9AFE(const Object *source, const void *other) const
{
	float minRange = m_template->getMinimumAttackRange();
	if (minRange == 0.0f)
		return false;
	float distSqr = source->rva00263763(other);
	if (distSqr < minRange * minRange)
		return true;
	return false;
}

float Weapon::rva002C957E() const
{
	return m_template->getMinimumAttackRange();
}

// ?rva002C95F0@Weapon@@QBE_NXZ @0x002C95F0 17B
// Weapon frame check: m_50 (+0x50 leech/active frame per WeaponCtor) vs GameLogic frame+0x40 via TheGameLogic.
// Evidence: callers 0x00343EAD 0x00343EC0 in 0x00343DD8; unblocks 0x00343DD8; prev/next Weapon owners; pooled TheGameLogic.
bool Weapon::rva002C95F0() const
{
	return m_50 > TheGameLogic->m_frame;
}

// ?rva002C95DE@Weapon@@QAEXH@Z @0x002C95DE 18B
// Weapon frame set: m_50 = GameLogic frame + offset. Caller 0x002C7484 passes 0 in 6-weapon loop (unblocks 0x002C7474).
// Evidence: same Weapon +0x50 and TheGameLogic +0x40 as rva002C95F0 sibling; prev/next same TU and flags.
void Weapon::rva002C95DE(int offset)
{
	m_50 = TheGameLogic->m_frame + offset;
}

// ?rva002C959E@Weapon@@QAEXXZ, retail 0x002C959E, 46 bytes.
// Randomize m_58 from template +0x13C via GetGameLogicRandomValue.
// Evidence: unlock lane; caller 0x002CDC46; same Weapon TU and flags.
int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);
void Weapon::rva002C959E()
{
	int v;
	if (m_template->m_13c)
		v = GetGameLogicRandomValue(0, m_template->m_13c, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp", 3644);
	else
		v = 0;
	m_58 = v;
}
