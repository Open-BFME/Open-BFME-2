// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Per-profile online preference files: Zero Hour's QuickMatchPreferences,
// GameSpyMiscPreferences and LadderPreferences constructors, which BFME 2 roots under
// "Online Files" (Zero Hour used "GeneralsOnline"). Retail keeps them far
// from UserPreferences.cpp (0x005DF1A3 and 0x00559711), so they get their
// own unit. The UserPreferences model is the one in
// Code/GameEngine/Source/Common/UserPreferences.cpp.

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <stdlib.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../../Include/Common/BfmeStringData.h"

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

// Declaration-only: the rowed map<AsciiString,AsciiString>::operator[] is bound,
// this TU emits no per-flag copy of it or of the tree internals it pulls in.
namespace _STL {
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &);
}
typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

#include "../../../Include/Common/UserPreferences.h"

// The GameSpy session info singleton (0x00E02320), as far as the ignore
// list reaches it: getLocalProfileID sits in vtable slot 0x7C.
class GameSpyInfoInterface
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual Int getLocalProfileID();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class QuickMatchPreferences : public UserPreferences
{
public:
	QuickMatchPreferences();
	virtual ~QuickMatchPreferences();
	void setColor(Int val);
	Int getColor(void);
	void setSide(Int val);
	Int getSide(void);
	void setHighest1vs1Rank(Int val);
	Int getHighest1vs1Rank(void);
	void setHighest2vs2Rank(Int val);
	Int getHighest2vs2Rank(void);
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();
	int rva00559782();
	void rva005597CB(int val);
	void rva0055986F(AsciiString val);
	void rva00559924(AsciiString val);
	AsciiString rva00559813();
	AsciiString rva005598C8();
	Bool rva0055997D();
	int rva005599C8();
};

// ??0QuickMatchPreferences@@QAE@XZ @0x5DF1A3
QuickMatchPreferences::QuickMatchPreferences()
{
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\QMPref%d.ini", "Online Files", TheGameSpyInfo->getLocalProfileID());
	load(userPrefFilename);
}

// ??1QuickMatchPreferences@@UAE@XZ @0x5DF17C
// Vtable 0xC776DC slot 0 is the deleting dtor 0x5DF187, which calls this:
// store the vtable and tail-call ~UserPreferences.
QuickMatchPreferences::~QuickMatchPreferences()
{
}

void QuickMatchPreferences::setColor(Int val)
{
	setInt("Color", val);
}

Int QuickMatchPreferences::getColor(void)
{
	return getInt("Color", 0);
}

void QuickMatchPreferences::setSide(Int val)
{
	setInt("Side", val);
}

Int QuickMatchPreferences::getSide(void)
{
	return getInt("Side", 0);
}

// BFME 2's two ladder-rank keys, after setSide/getSide in the same order.
void QuickMatchPreferences::setHighest1vs1Rank(Int val)
{
	setInt("Highest1vs1Rank", val);
}

Int QuickMatchPreferences::getHighest1vs1Rank(void)
{
	return getInt("Highest1vs1Rank", 0);
}

void QuickMatchPreferences::setHighest2vs2Rank(Int val)
{
	setInt("Highest2vs2Rank", val);
}

Int QuickMatchPreferences::getHighest2vs2Rank(void)
{
	return getInt("Highest2vs2Rank", 0);
}

// ??0GameSpyMiscPreferences@@QAE@XZ @0x559711
GameSpyMiscPreferences::GameSpyMiscPreferences()
{
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\GSMiscPref%d.ini", "Online Files", TheGameSpyInfo->getLocalProfileID());
	load(userPrefFilename);
}

// ??1GameSpyMiscPreferences@@UAE@XZ @0x5596EA
// Vtable 0xC6B3AC slot 0 is the deleting dtor 0x5596F5, which calls this.
GameSpyMiscPreferences::~GameSpyMiscPreferences()
{
}

int GameSpyMiscPreferences::rva00559782()
{
	return getInt("Locale", 0);
}

void GameSpyMiscPreferences::rva005597CB(int val)
{
	setInt("Locale", val);
}

void GameSpyMiscPreferences::rva0055986F(AsciiString val)
{
	setAsciiString("ToolTipCachedStats", val);
}

void GameSpyMiscPreferences::rva00559924(AsciiString val)
{
	setAsciiString("AllOtherCachedStats", val);
}

AsciiString GameSpyMiscPreferences::rva00559813()
{
	return getAsciiString("ToolTipCachedStats", AsciiString::TheEmptyString);
}

AsciiString GameSpyMiscPreferences::rva005598C8()
{
	return getAsciiString("AllOtherCachedStats", AsciiString::TheEmptyString);
}

// Zero Hour's GameSpyMiscPreferences reads the same two keys with the same
// defaults (QMResLock false, MaxMessagesPerUpdate 100); the names stay
// address-derived like the class's other accessors.
Bool GameSpyMiscPreferences::rva0055997D()
{
	return getBool("QMResLock", false);
}

int GameSpyMiscPreferences::rva005599C8()
{
	return getInt("MaxMessagesPerUpdate", 100);
}

typedef unsigned short UnsignedShort;

class LadderPref
{
public:
	LadderPref();
	LadderPref(const LadderPref &other);
	~LadderPref();
	LadderPref &operator=(const LadderPref &other);

	UnicodeString name;
	AsciiString address;
	UnsignedShort port;
	time_t lastPlayDate;
};

AsciiString AsciiStringToQuotedPrintable(AsciiString original);
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);
AsciiString QuotedPrintableToAsciiString(AsciiString original);
UnicodeString QuotedPrintableToUnicodeString(AsciiString original);

typedef _STL::map<time_t, LadderPref> LadderPrefMap;

// Zero Hour's recent-ladder preferences: a UserPreferences file plus the
// parsed LadderPrefMap at +0x14; write is overridden (vtable 0x00C77788
// slot 3 is 0x005E0026).
class LadderPreferences : public UserPreferences
{
public:
	LadderPreferences();
	virtual ~LadderPreferences();
	virtual Bool write(void);
	Bool loadProfile(Int profileID);

private:
	LadderPrefMap m_ladders;
};



// ??1LadderPref@@QAE@XZ @0x5BA3C0
inline LadderPref::~LadderPref()
{
}

inline LadderPref::LadderPref()
{
}



// ?Rva0055A087Format@@YAXPAHPAVAsciiString@@@Z @0x0055A087 (86B): formats ten
// ints from the array as "%d " into a temp then concats into the output.
// Evidence: caller 0x0044DE18 passes its int array plus temp AsciiString;
// shared "%d " literal at 0x007E3AC0 plus rowed format 0x00038150 and concat
// 0x00006987; loop 0xa matches ten ints.
void __cdecl Rva0055A087Format(int *vals, AsciiString *out)
{
	AsciiString tmp;
	for (int i = 0; i < 10; ++i) {
		tmp.format("%d ", vals[i]);
		((StringBase<char> *)out)->concat(*(const StringBase<char> *)&tmp);
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeLadderPrefInlineAnchor@@YAXPAVLadderPref@@@Z absent-from-retail
void _bfmeLadderPrefInlineAnchor(LadderPref *p)
{
    p->LadderPref::~LadderPref();
}
#pragma inline_depth()
