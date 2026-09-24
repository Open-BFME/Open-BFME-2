// ??0HordeContainRankInfo@@QAE@XZ
// partial score=0.45 date=2026-09-24
// cl: /O1 /Oy /DNDEBUG /MD /GX- /Oi- /D_STLP_USE_STATIC_LIB
//
// The RankInfo field callback at table 0x00C45530 allocates 0x38 bytes and
// calls this constructor. Its stores and member constructors establish the
// rank-entry layout: rank number, StringBase<char>, a vector of 16-byte
// position records, two 128-bit condition sets, and a trailing presence byte.
// The class name is descriptive; the original EA type name is not recovered.

#include <string.h>

typedef unsigned char Bool;

struct BfmeE16
{
	float words[4];
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class Allocator> class _Vector_base
{
public:
	_Vector_base(const Allocator &);

protected:
	T *m_begin;
	T *m_end;
	T *m_endOfStorage;
};

template <class T> class vector : public _Vector_base<T, allocator<T> >
{
public:
	__forceinline vector() : _Vector_base<T, allocator<T> >(allocator<T>()) {}
};

template <unsigned Bits> class bitset
{
public:
	unsigned long m_words[(Bits + 31) / 32];
	bitset<Bits> &reset();
};

template <> bitset<128> &bitset<128>::reset();
}

struct HordeContainRankPosition
{
	float x;
	float y;
	int leaderRank;
	int leaderIndex;
};

// The vector base's constructor is ICF-folded with the already matched
// BfmeE16 base constructor. Its element type only supplies the verified
// 16-byte stride here; the rank-position contents are float/float/int/int.
typedef BfmeE16 HordeRankPositionVectorElementForCtor;

class HordeContainRankUnitType
{
public:
	HordeContainRankUnitType() : m_data(0) {}
	void set(const char *text);

private:
	void *m_data;
};

class HordeContainRankInfo
{
public:
	HordeContainRankInfo();

private:
	int m_rankNumber;
	HordeContainRankUnitType m_unitType;
	_STL::vector<HordeRankPositionVectorElementForCtor> m_positions;
	_STL::bitset<128> m_grantedWeaponCondition;
	_STL::bitset<128> m_revokedWeaponCondition;
	Bool m_hasWeaponConditions;
};

HordeContainRankInfo::HordeContainRankInfo()
{
	m_grantedWeaponCondition.reset();
	m_revokedWeaponCondition.reset();
	m_rankNumber = 0;
	m_hasWeaponConditions = 0;
	memset(&m_revokedWeaponCondition, 0, 0x10);
	memset(&m_grantedWeaponCondition, 0, 0x10);
}
