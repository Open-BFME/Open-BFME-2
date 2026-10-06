// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
//
// UserPreferences WinsVs/LossesVs helpers (retail 0x0053740C/82, 0x0053745E/85,
// 0x005374B3/82, 0x00537505/85, plus max-finders 0x0053755A/188 and
// 0x00537616/188).
// Each builds "<outer>WinsVs<inner>" or "<outer>LossesVs<inner>" from a
// by-value outer AsciiString plus "WinsVs"/"LossesVs" plus an inner faction
// string, then forwards to the UserPreferences virtual at slot 6 (getInt,
// +0x18, default 0) or slot 11 (setInt, +0x2C). The max-finders loop the
// six-entry faction table at 0x009BE9B0 (Men/Elves/Dwarves/Isengard/Mordor/
// Wild) and return the faction with the largest WinsVs/LossesVs value.
// Vtable layout mirrors Common/UserPreferences.cpp (13 slots: dtor, 2 loads,
// write, 5 getters, 4 setters) so the indirect offsets match; the mirror
// omits the map base and m_filename since these bodies touch only the vtable.
// Evidence: "WinsVs" at 0x00869120, "LossesVs" at 0x00869128; faction table
// at 0x009BE9B0 (Men/Elves/Dwarves/Isengard/Mordor/Wild); callers 0x0053755A,
// 0x00537616 (outer = [ebp+0x0C]) and 0x005376D2/0x005377B6 (outer/inner loop
// factions), plus 0x005BF4BC (RealTimeStatsPreferences at [ebp-0x2C]) and
// 0x005BFD35 (StrategicStatsPreferences at [ebp-0x28]); no BFME1 donor
// (no WinsVs/LossesVs hits in open-bfme-1/game). Class proven by shared use
// from both RealTime and Strategic stats objects (common UserPreferences base).

typedef int Int;
typedef bool Bool;
typedef float Real;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class UnicodeString;

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual Bool load(const AsciiString &fname);
	virtual Bool load(const UnicodeString &fname);
	virtual Bool write(void);
	virtual Bool getBool(const AsciiString &key, Bool defaultValue) const;
	virtual Real getReal(const AsciiString &key, Real defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
	virtual Int getEnumIndex(const char *key, const char **names, Int count, Int defaultValue) const;
	virtual AsciiString getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const;
	virtual void setBool(const AsciiString &key, Bool val);
	virtual void setReal(const AsciiString &key, Real val);
	virtual void setInt(const AsciiString &key, Int val);
	virtual void setAsciiString(const AsciiString &key, const AsciiString &val);

	Int rva00537505(AsciiString a, const AsciiString &b);
	void rva005374B3(AsciiString a, const AsciiString &b, Int v);
	Int rva0053745E(AsciiString a, const AsciiString &b);
	void rva0053740C(AsciiString a, const AsciiString &b, Int v);
	AsciiString rva0053755A(AsciiString a);
	AsciiString rva00537616(AsciiString a);
};

Int UserPreferences::rva00537505(AsciiString a, const AsciiString &b)
{
	((StringBase<char> *)&a)->concat("LossesVs");
	((StringBase<char> *)&a)->concat(*(const StringBase<char> *)&b);
	return getInt(a, 0);
}

void UserPreferences::rva005374B3(AsciiString a, const AsciiString &b, Int v)
{
	((StringBase<char> *)&a)->concat("LossesVs");
	((StringBase<char> *)&a)->concat(*(const StringBase<char> *)&b);
	setInt(a, v);
}

Int UserPreferences::rva0053745E(AsciiString a, const AsciiString &b)
{
	((StringBase<char> *)&a)->concat("WinsVs");
	((StringBase<char> *)&a)->concat(*(const StringBase<char> *)&b);
	return getInt(a, 0);
}

void UserPreferences::rva0053740C(AsciiString a, const AsciiString &b, Int v)
{
	((StringBase<char> *)&a)->concat("WinsVs");
	((StringBase<char> *)&a)->concat(*(const StringBase<char> *)&b);
	setInt(a, v);
}

static const char *kFactions[] = { "Men", "Elves", "Dwarves", "Isengard", "Mordor", "Wild" };

AsciiString UserPreferences::rva0053755A(AsciiString a)
{
	AsciiString best;
	AsciiString cur;
	Int max = 0;
	for (Int i = 0; i < 6; ++i) {
		((StringBase<char> *)&cur)->set(kFactions[i]);
		Int v = rva0053745E(a, cur);
		if (v > max) {
			best = cur;
			max = v;
		}
	}
	return best;
}

AsciiString UserPreferences::rva00537616(AsciiString a)
{
	AsciiString best;
	AsciiString cur;
	Int max = 0;
	for (Int i = 0; i < 6; ++i) {
		((StringBase<char> *)&cur)->set(kFactions[i]);
		Int v = rva00537505(a, cur);
		if (v > max) {
			best = cur;
			max = v;
		}
	}
	return best;
}
