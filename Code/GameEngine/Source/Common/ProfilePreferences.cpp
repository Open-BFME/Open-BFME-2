// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Player-profile preferences (vtable 0x00C68DD8, retail 0x00535762).
// A UserPreferences with no extra members: the constructor only runs the
// base constructor and installs its own vtable. It takes a four-byte
// argument its body ignores (both observed callers pass a constant, 0 or 1,
// and the 20-byte body never reads [esp+8]); the name for the parameter
// below only says what the call sites hand it. The class name itself is
// descriptive -- no retail spelling is known. Adjacent .rdata carries the
// profile stat keys (ProfileCreatedDate, Points, TimePlayed,
// LongestGameTime, ShortestGameTime), and the vtable keeps every
// UserPreferences slot except slot 0. The matching destructor (0x00535776,
// deleting dtor 0x00537E60) restores vtable 0x00C68DD8 and tail-calls
// UserPreferences::~UserPreferences; both stats subclasses inherit it via ICF.
//
// loadStatsFile at 0x00537D33 is the shared stats loader the subclasses
// below will forward to: it clears the preference map, and unless the
// incoming profile path equals UnicodeString::TheEmptyString (0x00E0C898,
// default-constructed at 0x007B6740), it appends the leaf name
// and runs UserPreferences::load on the result. Helper and class names
// are descriptive -- no retail spellings are known.

#include <map>
#include <stdlib.h>

// Retail's tree frees nodes through a direct _free; the dllimport+forceinline
// specialization takes __malloc_alloc<0>::deallocate inline so this TU emits
// no copy of its own (retail's is the unoptimized import entry, 0x00023A70).
namespace _STL {
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"



#include "unicode_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

#include "../../Include/Common/UserPreferences.h"

// Per-class stats leaves appended to the profile path (0x00E05E00 and
// 0x00E05E04). Their dynamic initializers (0x007B3A58, 0x007B3AA5) build
// each from a temporary AsciiString of the .rdata leaf and register the
// destructor thunks at 0x007B92B6 and 0x007B92C0, in this order.
UnicodeString g_realTimeStatsLeaf(AsciiString("RealTimeStats.ini"));
UnicodeString g_strategicStatsLeaf(AsciiString("StrategicStats.ini"));

// File deleter shared by the stat-clear helpers below: appends the leaf to
// the profile path and removes that file from the user-data directory.
Bool deleteFileInGlobalDataDir(const UnicodeString &fname);

class ProfilePreferences : public UserPreferences
{
public:
	ProfilePreferences(int profileKind);
	virtual ~ProfilePreferences();
	virtual void loadProfileStats(const UnicodeString &profilePath) = 0;

protected:
	void loadStatsFile(const UnicodeString &profilePath, const UnicodeString &leafName);
};

// StrategicStatsPreferences (vtable 0x00C6913C) loads the global leaf
// "StrategicStats.ini" (UnicodeString static at 0x00E05E04, built by the
// dynamic initializer at 0x007B3AA5 from the .rdata leaf at 0x00C691D4).
// Its vtable keeps the thirteen UserPreferences slots, shares the ICF
// deleting destructor at 0x00537E60 (0x00535776) at slot 0, and appends
// the loadProfileStats thunk at slot 13.
class StrategicStatsPreferences : public ProfilePreferences
{
public:
	StrategicStatsPreferences(const UnicodeString &profilePath);
	virtual void loadProfileStats(const UnicodeString &profilePath);
	static Bool deleteStatsFile(const UnicodeString &profilePath);
};

// RealTimeStatsPreferences (vtable 0x00C69188) loads "RealTimeStats.ini"
// (static at 0x00E05E00, initializer at 0x007B3A58 from 0x00C691C0) and
// defaults the "UseMapListTooltips" key (0x00C69174) to true. Same vtable
// shape as its sibling: thirteen UserPreferences slots, shared deleting
// destructor at slot 0, loadProfileStats thunk at slot 13.
class RealTimeStatsPreferences : public ProfilePreferences
{
public:
	RealTimeStatsPreferences(const UnicodeString &profilePath);
	virtual void loadProfileStats(const UnicodeString &profilePath);
	static Bool deleteStatsFile(const UnicodeString &profilePath);
};

// ??0ProfilePreferences@@QAE@H@Z
ProfilePreferences::ProfilePreferences(int profileKind)
{
	(void)profileKind;
}

// ??1ProfilePreferences@@UAE@XZ @0x535776
ProfilePreferences::~ProfilePreferences()
{
}

// ?loadStatsFile@ProfilePreferences@@IAEXABVUnicodeString@@0@Z @0x537D33
void ProfilePreferences::loadStatsFile(const UnicodeString &profilePath, const UnicodeString &leafName)
{
	clear();

	if (profilePath.compare(UnicodeString::TheEmptyString) == 0)
		return;

	UnicodeString path(profilePath);
	path.concat(leafName);
	UserPreferences::load(path);
}

// ?loadProfileStats@StrategicStatsPreferences@@UAEXABVUnicodeString@@@Z @0x537D9A
void StrategicStatsPreferences::loadProfileStats(const UnicodeString &profilePath)
{
	loadStatsFile(profilePath, g_strategicStatsLeaf);
}

// ?loadProfileStats@RealTimeStatsPreferences@@UAEXABVUnicodeString@@@Z @0x537DAB
void RealTimeStatsPreferences::loadProfileStats(const UnicodeString &profilePath)
{
	loadStatsFile(profilePath, g_realTimeStatsLeaf);
}

// ??0StrategicStatsPreferences@@QAE@ABVUnicodeString@@@Z @0x537DBC
StrategicStatsPreferences::StrategicStatsPreferences(const UnicodeString &profilePath)
	: ProfilePreferences(1)
{
	loadProfileStats(profilePath);
}

// ??0RealTimeStatsPreferences@@QAE@ABVUnicodeString@@@Z @0x537DF9
RealTimeStatsPreferences::RealTimeStatsPreferences(const UnicodeString &profilePath)
	: ProfilePreferences(0)
{
	loadProfileStats(profilePath);
	setBool("UseMapListTooltips", true);
}

// StrategicStatsPreferences::deleteStatsFile @0x53789A: copies the profile
// path, appends the StrategicStats leaf and deletes that file from the
// user-data directory, returning whether the removal succeeded. Called
// directly (not through the vtable) by the profile reset at 0x0043C31F.
Bool StrategicStatsPreferences::deleteStatsFile(const UnicodeString &profilePath)
{
	UnicodeString path(profilePath);
	path.concat(g_strategicStatsLeaf);
	return deleteFileInGlobalDataDir(path);
}

// RealTimeStatsPreferences::deleteStatsFile @0x537A4C: same shape as its
// Strategic sibling, appending the RealTimeStats leaf instead. Called by
// the profile reset at 0x0043C30E.
Bool RealTimeStatsPreferences::deleteStatsFile(const UnicodeString &profilePath)
{
	UnicodeString path(profilePath);
	path.concat(g_realTimeStatsLeaf);
	return deleteFileInGlobalDataDir(path);
}
