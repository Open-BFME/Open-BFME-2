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
	AsciiString rva0044DBA5(void);
	UnicodeString rva0044D330(void);
	void rva0044DC54(Int val);
	void rva0044DCB9(Int val);
	void rva0044DD1E(Int val);

private:
	const AsciiString &makeKey(const char *key) const;

	Int m_mode;
	mutable AsciiString m_key;
};

// ?write@GameModePreferences@@UAE_NXZ @0x44D50D
// GameModePreferences::write: defined in GameModePreferences.cpp (its row's unit).

// ?makeKey@GameModePreferences@@ABEABVAsciiString@@PBD@Z @0x44D512
// GameModePreferences::makeKey: defined in GameModePreferences.cpp (its row's unit).

// ??0GameModePreferences@@QAE@H@Z @0x44D54B
// GameModePreferences::GameModePreferences: defined in GameModePreferences.cpp (its row's unit).

// ??1GameModePreferences@@UAE@XZ @0x44D56A
// GameModePreferences::~GameModePreferences: defined in GameModePreferences.cpp (its row's unit).

// ?getStrategicScenario@GameModePreferences@@QAEHXZ @0x44D5A5
// GameModePreferences::getStrategicScenario: defined in GameModePreferences.cpp (its row's unit).

// ?setStrategicScenario@GameModePreferences@@QAEXH@Z @0x44D5EE
// GameModePreferences::setStrategicScenario: defined in GameModePreferences.cpp (its row's unit).

// ?setBool@GameModePreferences@@UAEXABVAsciiString@@_N@Z @0x44D636
// GameModePreferences::setBool: defined in GameModePreferences.cpp (its row's unit).

// ?setReal@GameModePreferences@@UAEXABVAsciiString@@M@Z @0x44D665
// GameModePreferences::setReal: defined in GameModePreferences.cpp (its row's unit).

// ?setInt@GameModePreferences@@UAEXABVAsciiString@@H@Z @0x44D698
// GameModePreferences::setInt: defined in GameModePreferences.cpp (its row's unit).

// ?getBool@GameModePreferences@@UBE_NABVAsciiString@@_N@Z @0x44D6C7
// GameModePreferences::getBool: defined in GameModePreferences.cpp (its row's unit).

// ?getReal@GameModePreferences@@UBEMABVAsciiString@@M@Z @0x44D6F6
// GameModePreferences::getReal: defined in GameModePreferences.cpp (its row's unit).

// ?getInt@GameModePreferences@@UBEHABVAsciiString@@H@Z @0x44D729
// GameModePreferences::getInt: defined in GameModePreferences.cpp (its row's unit).

// ?rva0054F5A4@GameModePreferences@@QAEHXZ retail 0x0054F5A4 58B.
// LobbyRoomID getter over the mode-keyed map: find makeKey("LobbyRoomID")
// and atoi the value or 0 when missing/empty.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; atoi IAT; callers
// 0x00385595 0x003855B6; prev Rva0054F508 ctor 0x0054F52F.
// GameModePreferences::rva0054F5A4: defined in GameModePreferences.cpp (its row's unit).

// Color-limit globals at 0x00A022F4: +0x38 count source plus +0x40 cached limit.
struct Rva00A022F4
{
	char m_pad[0x38];
	int m_38;
	int m_3C;
	int m_40;
};

extern Rva00A022F4 *g_00A022F4;

// ?rva0044D836@GameModePreferences@@QAEHXZ @0x0044D836 (86B): Color getter
// over the mode-keyed map with -1 for missing or out of range plus lazy
// cached limit from 0x00A022F4.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; atoi IAT; limit
// 0x00A022F4 plus 0x38 plus 0x40; callers 0x00249E23 0x00446853.
// GameModePreferences::rva0044D836: defined in GameModePreferences.cpp (its row's unit).

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

// GameModePreferences::rva0044D88C: defined in GameModePreferences.cpp (its row's unit).

// ?rva0044DBA5@GameModePreferences@@QAE?AVAsciiString@@XZ @0x0044DBA5 175B:
// Password getter over the mode-keyed map: find makeKey("Password"), empty
// when missing, else QuotedPrintable decode plus trim.
// Evidence: makeKey 0x0044D512; map find 0x001F8437; quoted 0x005356BF;
// set 0x000366F0; trim 0x00037CF0; TheEmptyString 0x009E0878; callers
// 0x005A0E44 0x005A2961; prev 0x0044D836 next 0x0044DC54.
AsciiString QuotedPrintableToAsciiString(AsciiString original);
// GameModePreferences::rva0044DBA5: defined in GameModePreferences.cpp (its row's unit).

// ?rva0044D330@GameModePreferences@@QAE?AVUnicodeString@@XZ @0x0044D330 335B:
// UserName getter over the map: find "UserName", machine-name fallback when
// missing or QP-decoded empty, else QP-decode plus trim.
// Evidence: "UserName" 0x0083EF48; map find 0x001F8437; quoted 0x005355F2;
// translate 0x006CB6A0; trim 0x00037F70; IPEnumeration 0x00318329 plus
// getMachineName 0x0050C1FD; callers 0x003817EE 0x004453A2 0x0050CFFA;
// prev 0x0044D2F5 next 0x0044D50D.
class EnumeratedIP;
class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	AsciiString getMachineName(void);
private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};
UnicodeString QuotedPrintableToUnicodeString(AsciiString original);
// Retail's map lookup is throw(): the key temporary carries EH state for its
// own construction but no extra state across the find call itself.
// _STL::map::find is not throw(), so the lookup goes through the
// layout-compatible SkirmishFindMap shim whose find is declared throw().
// Its call is already pinned to the shared _M_find worker at 0x001F8437.
struct SkirmishFindNode
{
	unsigned char m_pad[0x14];
	AsciiString m_value;
};
class SkirmishFindMap
{
public:
	SkirmishFindNode *find(const AsciiString &key) const throw();
	SkirmishFindNode *end() const { return m_end; }
private:
	SkirmishFindNode *m_end;
	unsigned char m_unreconstructed[8];
};
UnicodeString GameModePreferences::rva0044D330(void)
{
	UnicodeString ret;
	SkirmishFindNode *it = ((const SkirmishFindMap *)((const char *)this + 4))->find("UserName");
	if (it == ((const SkirmishFindMap *)((const char *)this + 4))->end())
	{
		IPEnumeration ips;
		ret.translate(ips.getMachineName());
		return ret;
	}
	ret = QuotedPrintableToUnicodeString(it->m_value);
	ret.trim();
	if (((const AsciiString *)(const void *)&ret)->isEmpty())
	{
		IPEnumeration ips;
		ret.translate(ips.getMachineName());
		return ret;
	}
	return ret;
}

// ?rva0054F7C0@GameModePreferences@@QAEXH@Z retail 0x0054F7C0 101B.
// LobbyRoomID setter: format "%d" then map makeKey("LobbyRoomID") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; caller 0x005A3899.
// GameModePreferences::rva0054F7C0: defined in GameModePreferences.cpp (its row's unit).

// ?rva0044DC54@GameModePreferences@@QAEXH@Z @0x0044DC54 (101B): Hero setter
// via "%d" format then map makeKey("Hero") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; callers
// 0x0044579D 0x0059F999; prev 0x0044D836 next 0x0044DDFB.
// GameModePreferences::rva0044DC54: defined in GameModePreferences.cpp (its row's unit).

// ?rva0044DCB9@GameModePreferences@@QAEXH@Z @0x0044DCB9 (101B): Color setter
// via "%d" format then map makeKey("Color") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; callers
// 0x00445593 0x0059F985; prev 0x0044DC54 next 0x0044DDFB.
// GameModePreferences::rva0044DCB9: defined in GameModePreferences.cpp (its row's unit).

// ?rva0044DD1E@GameModePreferences@@QAEXH@Z @0x0044DD1E (101B): PlayerTemplate
// setter via "%d" format then map makeKey("PlayerTemplate") slot assign.
// Evidence: format 0x00038150; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; prev 0x0044DCB9
// next 0x0044DDFB.
// GameModePreferences::rva0044DD1E: defined in GameModePreferences.cpp (its row's unit).

// ?rva0044DDFB@GameModePreferences@@QAEXPAH@Z @0x0044DDFB (95B): Rules setter
// over the mode-keyed map via ten-int array formatter into tmp then slot assign.
// Evidence: formatter 0x0055A087; makeKey 0x0044D512; map subscript 0x002031FB;
// AsciiString assign pin 0x000366F0; releaseBuffer 0x00036410; callers
// 0x004442CB 0x0059EC3F; prev GameModePreferences 0x0044D758.
void __cdecl Rva0055A087Format(int *vals, AsciiString *out);
// GameModePreferences::rva0044DDFB: defined in GameModePreferences.cpp (its row's unit).

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
// under address names in Rva0044D56ADerived.cpp.

// ?loadFromIniFile@LANPreferences@@QAE_NXZ @0x44D2AC
// LANPreferences::loadFromIniFile: defined in GameModePreferences.cpp (its row's unit).

// ??0LANPreferences@@QAE@H@Z @0x44D2F5
// LANPreferences::LANPreferences: defined in GameModePreferences.cpp (its row's unit).
