// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Per-profile online preference files: Zero Hour's QuickMatchPreferences,
// GameSpyMiscPreferences and LadderPreferences constructors, which BFME 2 roots under
// "Online Files" (Zero Hour used "GeneralsOnline"). Retail keeps them far
// from UserPreferences.cpp (0x005DF1A3 and 0x00559711), so they get their
// own unit. The UserPreferences model is the one in
// Code/GameEngine/Source/Common/UserPreferences.cpp.

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <stdlib.h>

struct _iobuf;
typedef struct _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *name, const unsigned short *mode);
extern "C" __declspec(dllimport) int __cdecl fprintf(FILE *fp, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *fp);
extern "C" __declspec(dllimport) char *__cdecl fgets(char *buf, int n, FILE *fp);

typedef bool Bool;
typedef int Int;
typedef float Real;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

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

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();

	// MSVC lays overloaded virtuals out in reverse declaration order, so
	// load(UnicodeString) takes slot 1 and load(AsciiString) slot 2.
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

protected:
	UnicodeString m_filename;
};

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
	void rva005DF336(Int val);
	Int rva005DF37E(void);
	void rva005DF3C7(Int val);
	Int rva005DF40F(void);
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
void QuickMatchPreferences::rva005DF336(Int val)
{
	setInt("Highest1vs1Rank", val);
}

Int QuickMatchPreferences::rva005DF37E(void)
{
	return getInt("Highest1vs1Rank", 0);
}

void QuickMatchPreferences::rva005DF3C7(Int val)
{
	setInt("Highest2vs2Rank", val);
}

Int QuickMatchPreferences::rva005DF40F(void)
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

typedef long time_t;
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
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s) throw();

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

// ??0LadderPreferences@@QAE@XZ @0x5DFFD3
LadderPreferences::LadderPreferences()
{
}

// ??1LadderPreferences@@UAE@XZ @0x5DFF7B
LadderPreferences::~LadderPreferences()
{
}

// ??1LadderPref@@QAE@XZ @0x5BA3C0
inline LadderPref::~LadderPref()
{
}

inline LadderPref::LadderPref()
{
}

// ?write@LadderPreferences@@UAE_NXZ @0x5E0026
Bool LadderPreferences::write(void)
{
	clear();

	static const Int MAX_LADDERS = 5;
	LadderPrefMap::iterator lpIt;
	Int count;
	for (lpIt = m_ladders.begin(), count = 0;
		lpIt != m_ladders.end() && count < MAX_LADDERS;
		++lpIt, ++count)
	{
		LadderPref p = lpIt->second;
		AsciiString ladName;
		AsciiString ladData;
		ladName.format("%s:%d", AsciiStringToQuotedPrintable(p.address).str(), p.port);
		ladData.format("%s:%d", UnicodeStringToQuotedPrintable(p.name).str(), p.lastPlayDate);
		AsciiString &slot = (*this)[ladName];
		slot = ladData;
	}

	return UserPreferences::write();
}

// ?loadProfile@LadderPreferences@@QAE_NH@Z @0x005E0201 501B
// BFME2 port of ZH LadderPreferences::loadProfile: Online Files root,
// parses base map entries into m_ladders via QP decoders. Evidence: rowed
// load slot 0x005E0026 neighbours, strings Online Files plus %s\Ladders%d.ini,
// rowed clear/format/atoi/QP/map ops, caller at 0x005BC3B1.
Bool LadderPreferences::loadProfile(Int profileID)
{
	clear();
	m_ladders.clear();
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\Ladders%d.ini", "Online Files", profileID);
	Bool success = load(userPrefFilename);
	if (!success)
		return success;

	for (LadderPreferences::iterator it = begin(); it != end(); ++it)
	{
		LadderPref p;
		AsciiString ladName = it->first;
		AsciiString ladData = it->second;

		const char *ptr = ladName.reverseFind(':');
		if (!ptr)
			continue;

		p.port = (UnsignedShort)atoi(ptr + 1);
		Int i;
		for (i = 0; i < strlen(ptr); ++i)
		{
			ladName.removeLastChar();
		}
		p.address = QuotedPrintableToAsciiString(ladName);

		ptr = ladData.reverseFind(':');
		if (!ptr)
			continue;

		p.lastPlayDate = atoi(ptr + 1);
		for (i = 0; i < strlen(ptr); ++i)
		{
			ladData.removeLastChar();
		}
		p.name = QuotedPrintableToUnicodeString(ladData);

		m_ladders[p.lastPlayDate] = p;
	}

	return true;
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
