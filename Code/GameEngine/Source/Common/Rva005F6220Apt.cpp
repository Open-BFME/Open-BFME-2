// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?SetLeaderQuantityString@Impl@HeroArmyDetailsMovieClip@StrategicHUD@@QAEXABVUnicodeString@@@Z retail 0x005F6220 103B
// Evidence: format APT:_level%u.%s_LeaderQuantity via rowed 0x00038150; pinned bfmeSetText 0x00225301; rowed releaseBuffer 0x00036410; globals 0x009FE4CC 0x007BAC1C; caller 0x005F67CA; precedent Rva005FB770 103B method Rva005FDF1C
#include "ascii_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva005F6220Team
{
	char m_pad8[8];
	char m_name[1];
};

#include "unicode_string.h"

UnicodeString __cdecl Rva005F632AFormat(int rank);

namespace StrategicHUD {
class HeroArmyDetailsMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::HeroArmyDetailsMovieClip::Impl
{
public:
	void SetLeaderQuantityString(const UnicodeString &text);
	void SetLeaderRankString(const UnicodeString &text);
	void rva005F63EC(int rank);
	void ShowLeaderRankProgress(float value);
private:
	char m_pad00[4];
	unsigned int m_level04;
	Rva005F6220Team *m_team08;
	char m_pad0C[0x2C - 0x0C];
	int m_rank2C;
};

void StrategicHUD::HeroArmyDetailsMovieClip::Impl::SetLeaderQuantityString(const UnicodeString &text)
{
	AsciiString key;
	const char *mid = m_team08 ? (const char *)((char *)m_team08 + 8) : "";
	key.format("APT:_level%u.%s_LeaderQuantity", m_level04, mid);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
}

void StrategicHUD::HeroArmyDetailsMovieClip::Impl::SetLeaderRankString(const UnicodeString &text)
{
	AsciiString key;
	const char *mid = m_team08 ? (const char *)((char *)m_team08 + 8) : "";
	key.format("APT:_level%u.%s_LeaderRank", m_level04, mid);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
}

void StrategicHUD::HeroArmyDetailsMovieClip::Impl::rva005F63EC(int rank)
{
	if (rank != m_rank2C) {
		SetLeaderRankString(Rva005F632AFormat(rank));
		m_rank2C = rank;
	}
}

class Rva005F64C0
{
public:
	void rva005F64C0(int rank);
	void rva005F64C8(float progress);
private:
	char m_pad00[8];
	StrategicHUD::HeroArmyDetailsMovieClip::Impl *m_ptr08;
};

void Rva005F64C0::rva005F64C0(int rank)
{
	return m_ptr08->rva005F63EC(rank);
}

void Rva005F64C0::rva005F64C8(float progress)
{
	m_ptr08->ShowLeaderRankProgress(progress);
}
