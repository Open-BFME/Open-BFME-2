// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Game-mode-keyed preferences (vtable 0x00C3EF60, retail 0x0044D50D-
// 0x0044D774): a UserPreferences whose typed accessors store every key as
// "<mode>:<key>", with mode 0 = "Rts", 1 = "Strat" (War of the Ring) and
// anything else unprefixed. The prefixed key is formatted into a scratch
// AsciiString member (+0x18) and handed to the base accessor; write is a
// plain forward. The class name is descriptive -- no retail spelling is
// known. LANPreferences (vtable 0x00C3EF04) derives from it. The
// UserPreferences model is the one in Common/UserPreferences.cpp.

#include <map>
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

class GameSlot;

class GameModePreferences : public UserPreferences
{
public:
	GameModePreferences(Int mode);
	virtual ~GameModePreferences();

	virtual Bool write(void);
	virtual Bool getBool(const AsciiString &key, Bool defaultValue) const;
	virtual Real getReal(const AsciiString &key, Real defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
	virtual void setBool(const AsciiString &key, Bool val);
	virtual void setReal(const AsciiString &key, Real val);
	virtual void setInt(const AsciiString &key, Int val);

	Int getStrategicScenario(void);
	void setStrategicScenario(Int scenario);
	Int rva0054F5A4(void);
	void rva0054F7C0(Int val);
	void rva0044DDFB(int *vals);
	Int rva0044D836(void);
	Int rva0044D88C(void);
	AsciiString rva0044DAA8(const AsciiString &def);
	AsciiString rva0044DBA5(void);
	AsciiString rva0044D986(void);
	Bool rva0044DB54(int *vals);
	Bool rva0044D774(GameSlot *slot);
	void rva0044DC54(Int val);
	void rva0044DCB9(Int val);
	void rva0044DD1E(Int val);
	void rva0044DD83(AsciiString val);

private:
	const AsciiString &makeKey(const char *key) const;

	Int m_mode;
	mutable AsciiString m_key;
};

// Target-backed GameSlot fields: AptMpGameSetup::rva0043DD34 reads/writes
// +0x50 through +0x5C; the +0x5C dword setter is rowed at 0x003FF0E7.
class GameSlot
{
public:
	unsigned char m_pad00[0x50];
	int m_heroKind;
	int m_hero0c;
	int m_hero10;
	int m_hero;
};

class Rva003FF0E7DwordSlot
{
public:
	void set(int value);
};

// Create-A-Hero data offsets are also read by rowed lobby slot code.
class CreateAHeroData
{
public:
	unsigned char m_pad00[0x0C];
	int m_0c;
	int m_10;
	unsigned char m_pad14[0x48 - 0x14];
	bool m_48;
};

class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A32F(int index);
};

class CreateAHeroManager
{
public:
	Rva0040A3F9 *rva0021F797();
};

extern CreateAHeroManager *TheCreateAHeroManager;

// ?write@GameModePreferences@@UAE_NXZ @0x44D50D
Bool GameModePreferences::write(void)
{
	return UserPreferences::write();
}

// ?makeKey@GameModePreferences@@ABEABVAsciiString@@PBD@Z @0x44D512
const AsciiString &GameModePreferences::makeKey(const char *key) const
{
	const char *prefix = "";
	switch (m_mode)
	{
		case 0: prefix = "Rts"; break;
		case 1: prefix = "Strat"; break;
	}
	m_key.format("%s:%s", prefix, key);
	return m_key;
}

// ??0GameModePreferences@@QAE@H@Z @0x44D54B
GameModePreferences::GameModePreferences(Int mode) : m_mode(mode)
{
}

// ??1GameModePreferences@@UAE@XZ @0x44D56A
GameModePreferences::~GameModePreferences()
{
}

// ?getStrategicScenario@GameModePreferences@@QAEHXZ @0x44D5A5
Int GameModePreferences::getStrategicScenario(void)
{
	return getInt("StrategicScenario", -1);
}

// ?setStrategicScenario@GameModePreferences@@QAEXH@Z @0x44D5EE
void GameModePreferences::setStrategicScenario(Int scenario)
{
	setInt("StrategicScenario", scenario);
}

// ?setBool@GameModePreferences@@UAEXABVAsciiString@@_N@Z @0x44D636
void GameModePreferences::setBool(const AsciiString &key, Bool val)
{
	UserPreferences::setBool(makeKey(key.str()), val);
}

// ?setReal@GameModePreferences@@UAEXABVAsciiString@@M@Z @0x44D665
void GameModePreferences::setReal(const AsciiString &key, Real val)
{
	UserPreferences::setReal(makeKey(key.str()), val);
}

// ?setInt@GameModePreferences@@UAEXABVAsciiString@@H@Z @0x44D698
void GameModePreferences::setInt(const AsciiString &key, Int val)
{
	UserPreferences::setInt(makeKey(key.str()), val);
}

// ?getBool@GameModePreferences@@UBE_NABVAsciiString@@_N@Z @0x44D6C7
Bool GameModePreferences::getBool(const AsciiString &key, Bool defaultValue) const
{
	return UserPreferences::getBool(makeKey(key.str()), defaultValue);
}

// ?getReal@GameModePreferences@@UBEMABVAsciiString@@M@Z @0x44D6F6
Real GameModePreferences::getReal(const AsciiString &key, Real defaultValue) const
{
	return UserPreferences::getReal(makeKey(key.str()), defaultValue);
}

// ?getInt@GameModePreferences@@UBEHABVAsciiString@@H@Z @0x44D729
Int GameModePreferences::getInt(const AsciiString &key, Int defaultValue) const
{
	return UserPreferences::getInt(makeKey(key.str()), defaultValue);
}

// ?rva0044D774@GameModePreferences@@QAE_NPAVGameSlot@@@Z @0x0044D774 194B.
// Retail callers 0x00249E75 and 0x00446875 use this Hero preference loader.
// GameSlot +0x50..+0x5C and CreateAHeroData +0x0C/+0x10/+0x48 are supported
// by target reads in the rowed 0x0043DD34 lobby slot handler; the hero list
// helpers are pinned from target call sites at 0x0021F797 and 0x0040A32F.
// The source shape follows the exact permute result for this whole unit.
Bool GameModePreferences::rva0044D774(GameSlot *slot)
{
	if (!slot)
		return false;
	if (!TheCreateAHeroManager)
		return false;
	slot->m_heroKind = 0;
	slot->m_hero0c = 0;
	slot->m_hero10 = 0;
	((Rva003FF0E7DwordSlot *)slot)->set(-1);
	PreferenceMap::const_iterator it = find(makeKey("Hero"));
	if (it == end())
		return false;
	int hero = atoi(it->second.str());
	if (hero == -1)
		return true;
	if (hero == -2) {
		slot->m_heroKind = 1;
		((Rva003FF0E7DwordSlot *)slot)->set(hero);
		return true;
	}
	Rva0040A3F9 *heroes = TheCreateAHeroManager->rva0021F797();
	CreateAHeroData *entry = heroes->rva0040A32F(hero);
	if (!entry)
		return true;
	slot->m_heroKind = entry->m_48 ? 2 : 3;
	((Rva003FF0E7DwordSlot *)slot)->set(hero);
	slot->m_hero0c = entry->m_0c;
	slot->m_hero10 = entry->m_10;
	return true;
}

// ?rva0054F5A4@GameModePreferences@@QAEHXZ retail 0x0054F5A4 58B.
// LobbyRoomID getter over the mode-keyed map: find makeKey("LobbyRoomID")
// and atoi the value or 0 when missing/empty.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; atoi IAT; callers
// 0x00385595 0x003855B6; prev Rva0054F508 ctor 0x0054F52F.
Int GameModePreferences::rva0054F5A4(void)
{
	PreferenceMap::const_iterator it = find(makeKey("LobbyRoomID"));
	if (it == end())
		return 0;
	return atoi(it->second.str());
}

// Color-limit globals at 0x00A022F4: +0x38 count source plus +0x40 cached limit.
struct Rva00A022F4
{
	char m_pad[0x38];
	int m_38;
	int m_3C;
	int m_40;
};

// ?g_00A022F4@@3PAURva00A022F4@@A: the global at this VA is ?TheMultiplayerSettings@@3PAVMultiplayerSettings@@A; this name is an alias for it.
extern Rva00A022F4 * g_00A022F4;
#pragma comment(linker, "/alternatename:?g_00A022F4@@3PAURva00A022F4@@A=?TheMultiplayerSettings@@3PAVMultiplayerSettings@@A")

// ?rva0044D836@GameModePreferences@@QAEHXZ @0x0044D836 (86B): Color getter
// over the mode-keyed map with -1 for missing or out of range plus lazy
// cached limit from 0x00A022F4.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; atoi IAT; limit
// 0x00A022F4 plus 0x38 plus 0x40; callers 0x00249E23 0x00446853.
Int GameModePreferences::rva0044D836(void)
{
	PreferenceMap::const_iterator it = find(makeKey("Color"));
	if (it == end())
		return -1;
	int v = atoi(it->second.str());
	if (v < -1)
		return -1;
	int *limit = &g_00A022F4->m_40;
	if (*limit == 0)
		*limit = g_00A022F4->m_38;
	if (v < *limit)
		return v;
	return -1;
}

// ?rva0044D88C@GameModePreferences@@QAEHXZ @0x0044D88C 180B:
// PlayerTemplate getter over the mode-keyed map: find makeKey(
// "PlayerTemplate"), -1 when missing unless the writable-global faction
// flag remaps to the store default, else atoi with -2/over-range plus
// empty-faction rejection, and -1 remapped through the same flag.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; atoi IAT;
// getNth 0x001FD3C6; TheWritableGlobalData 0x009FE758 plus 0x9D4 bits 3;
// ThePlayerTemplateStore 0x009FE0D0 plus count 0x0C/0x10 over 0x1DC plus
// default map at 0x18 begin-first; PlayerTemplate byte 0x151;
// callers 0x00249DE4 0x00446861 0x005A22AC 0x005A24F9;
// prev 0x0044D836 next 0x0044DBA5.
class PlayerTemplate
{
public:
	char m_pad151[0x151];
	unsigned char m_151;
	char m_rest[0x1DC - 0x152];
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	char m_pad[0x0C];
	PlayerTemplate *m_first;
	PlayerTemplate *m_last;
	PlayerTemplate *m_end;
	_STL::map<int, int> m_map;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class GlobalData
{
public:
	char m_pad[0x9D4];
	unsigned char m_flag9D4;
};

extern GlobalData *TheWritableGlobalData;

Int GameModePreferences::rva0044D88C(void)
{
	PreferenceMap::const_iterator it = find(makeKey("PlayerTemplate"));
	if (it == end()) {
		if ((TheWritableGlobalData->m_flag9D4 & 3) == 0)
			return -1;
		return ThePlayerTemplateStore->m_map.begin()->first;
	}
	int v = atoi(it->second.str());
	if (v == -2 || v < -2 || v >= (ThePlayerTemplateStore->m_last - ThePlayerTemplateStore->m_first))
		v = -1;
	if (v >= 0) {
		const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(v);
		if (!pt)
			v = -1;
		else if (pt->m_151 == 0)
			v = -1;
	}
	if (v == -1 && (TheWritableGlobalData->m_flag9D4 & 3) != 0)
		return ThePlayerTemplateStore->m_map.begin()->first;
	return v;
}

// ?rva0044D986@GameModePreferences@@QAE?AVAsciiString@@XZ @0x0044D986 290B.
// Target evidence: this entry uses the matched mode-key builder at 0x0044D512
// and MapUtil providers at 0x0030582D / 0x003057AB; the direct helper identities
// and signatures are established by their matched target rows. The surrounding
// GameModePreferences class label is descriptive, so the method stays address-named.
// Donor guidance: ZH SkirmishPreferences::getPreferredMap supplies the map lookup,
// decode, trim, validate and fallback flow; target-specific helpers are retained.
AsciiString getDefaultMap(Bool isMultiplayer);
Bool isValidMap(AsciiString mapName, Bool isMultiplayer);
AsciiString QuotedPrintableToAsciiString(AsciiString original);
AsciiString GameModePreferences::rva0044D986(void)
{
	AsciiString ret;
	PreferenceMap::const_iterator it = find(makeKey("Map"));
	if (it == end()) {
		ret = getDefaultMap(true);
		return ret;
	}
	ret = QuotedPrintableToAsciiString(it->second);
	ret.trim();
	if (ret.isEmpty() || !isValidMap(ret, true)) {
		ret = getDefaultMap(true);
		return ret;
	}
	return ret;
}

// ?rva0044DAA8@GameModePreferences@@QAE?AVAsciiString@@ABV2@@Z @0x0044DAA8 172B:
// GameName getter over the mode-keyed map: find makeKey("GameName"), default
// when missing, else QuotedPrintable decode plus trim.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; quoted 0x005356BF;
// set 0x000366F0; trim 0x00037CF0; callers 0x005A0E14 0x005A28F7;
// prev 0x0044D88C next 0x0044DBA5.
AsciiString QuotedPrintableToAsciiString(AsciiString original);
AsciiString GameModePreferences::rva0044DAA8(const AsciiString &def)
{
	AsciiString ret;
	PreferenceMap::const_iterator it = find(makeKey("GameName"));
	if (it == end())
		return def;
	ret.set(QuotedPrintableToAsciiString(it->second));
	ret.trim();
	return ret;
}

// ?rva0044DB54@GameModePreferences@@QAE_NPAH@Z @0x0044DB54 81B:
// Rules getter over the mode-keyed map: find makeKey("Rules"), missing calls
// pin 0x00559FAC with mode then false, else parse value or empty with
// 0x00559F11 then true.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; pin 0x00559FAC;
// parse 0x00559F11; empty 0x007BAC1C; callers 0x004468A0 0x005A232B;
// prev 0x0044DAA8 next 0x0044DBA5.
void __cdecl Rva00559FAC(int a, void *b);
void __cdecl Rva00559F11Parse(const char *s, int *out);
Bool GameModePreferences::rva0044DB54(int *vals)
{
	PreferenceMap::const_iterator it = find(makeKey("Rules"));
	if (it == end()) {
		Rva00559FAC(m_mode, vals);
		return false;
	}
	Rva00559F11Parse(it->second.str(), vals);
	return true;
}

// ?rva0044DBA5@GameModePreferences@@QAE?AVAsciiString@@XZ @0x0044DBA5 175B:
// Password getter over the mode-keyed map: find makeKey("Password"), empty
// when missing, else QuotedPrintable decode plus trim.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; quoted 0x005356BF;
// set 0x000366F0; trim 0x00037CF0; TheEmptyString 0x009E0878; callers
// 0x005A0E44 0x005A2961; prev 0x0044D836 next 0x0044DC54.
AsciiString QuotedPrintableToAsciiString(AsciiString original);
AsciiString GameModePreferences::rva0044DBA5(void)
{
	AsciiString ret;
	PreferenceMap::const_iterator it = find(makeKey("Password"));
	if (it == end())
		return AsciiString::TheEmptyString;
	ret.set(QuotedPrintableToAsciiString(it->second));
	ret.trim();
	return ret;
}

// ?rva0054F7C0@GameModePreferences@@QAEXH@Z retail 0x0054F7C0 101B.
// LobbyRoomID setter: format "%d" then map makeKey("LobbyRoomID") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; caller 0x005A3899.
void GameModePreferences::rva0054F7C0(Int val)
{
	AsciiString tmp;
	tmp.format("%d", val);
	AsciiString &slot = (*this)[makeKey("LobbyRoomID")];
	slot = tmp;
}

// ?rva0044DC54@GameModePreferences@@QAEXH@Z @0x0044DC54 (101B): Hero setter
// via "%d" format then map makeKey("Hero") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; callers
// 0x0044579D 0x0059F999; prev 0x0044D836 next 0x0044DDFB.
void GameModePreferences::rva0044DC54(Int val)
{
	AsciiString tmp;
	tmp.format("%d", val);
	AsciiString &slot = (*this)[makeKey("Hero")];
	slot = tmp;
}

// ?rva0044DCB9@GameModePreferences@@QAEXH@Z @0x0044DCB9 (101B): Color setter
// via "%d" format then map makeKey("Color") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; callers
// 0x00445593 0x0059F985; prev 0x0044DC54 next 0x0044DDFB.
void GameModePreferences::rva0044DCB9(Int val)
{
	AsciiString tmp;
	tmp.format("%d", val);
	AsciiString &slot = (*this)[makeKey("Color")];
	slot = tmp;
}

// ?rva0044DD1E@GameModePreferences@@QAEXH@Z @0x0044DD1E (101B): PlayerTemplate
// setter via "%d" format then map makeKey("PlayerTemplate") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; prev 0x0044DCB9
// next 0x0044DDFB.
void GameModePreferences::rva0044DD1E(Int val)
{
	AsciiString tmp;
	tmp.format("%d", val);
	AsciiString &slot = (*this)[makeKey("PlayerTemplate")];
	slot = tmp;
}

// ?rva0044DD83@GameModePreferences@@QAEXVAsciiString@@@Z @0x0044DD83 120B:
// Map setter via QuotedPrintable then makeKey Map slot assign.
// Evidence: AsciiStringToQuotedPrintable 0x00535546; makeKey 0x0044D512;
// map subscript 0x002031FB; AsciiString assign pin 0x000366F0;
// releaseBuffer 0x00036410; callers 0x0050CFE6 0x0059F9C2;
// prev 0x0044DD1E next 0x0044DDFB.
AsciiString AsciiStringToQuotedPrintable(AsciiString original);
void GameModePreferences::rva0044DD83(AsciiString val)
{
	(*this)[makeKey("Map")].setCopyInline(AsciiStringToQuotedPrintable(val));
}

// ?rva0044DDFB@GameModePreferences@@QAEXPAH@Z @0x0044DDFB (95B): Rules setter
// over the mode-keyed map via ten-int array formatter into tmp then slot assign.
// Evidence: formatter 0x0055A087; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; callers
// 0x004442CB 0x0059EC3F; prev GameModePreferences 0x0044D758.
void __cdecl Rva0055A087Format(int *vals, AsciiString *out);
void GameModePreferences::rva0044DDFB(int *vals)
{
	AsciiString tmp;
	Rva0055A087Format(vals, &tmp);
	AsciiString &slot = (*this)[makeKey("Rules")];
	slot = tmp;
}

// Zero Hour's LANPreferences on the mode-keyed base (vtable 0x00C3EF04).
// BFME 2 renamed its file NetworkPref.ini and loads it from a separate
// member rather than inline in the constructor.
class LANPreferences : public GameModePreferences
{
public:
	LANPreferences(Int mode);
	virtual ~LANPreferences();

	Bool loadFromIniFile(void);
};

// The destructor (0x0044D285) and its deleting form (0x0044D290) are rowed
// under address names in Rva0044D56ADerived.cpp. The non-deleting body at
// 0x0044D285 is the single-inheritance GameModePreferences-derived destructor.
#pragma comment(linker, "/alternatename:??1LANPreferences@@UAE@XZ=??1Rva0044D285@@UAE@XZ")

// ?loadFromIniFile@LANPreferences@@QAE_NXZ @0x44D2AC
Bool LANPreferences::loadFromIniFile(void)
{
	return UserPreferences::load("NetworkPref.ini");
}

// ??0LANPreferences@@QAE@H@Z @0x44D2F5
LANPreferences::LANPreferences(Int mode) : GameModePreferences(mode)
{
	loadFromIniFile();
}
