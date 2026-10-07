// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Skirmish preferences (vtable 0x00C3D658, retail 0x0043C128).
// A UserPreferences with a small int tag at +0x14, a UserNames
// list<UnicodeString> at +0x18 and a CurrentUserName AsciiString
// at +0x1C. The constructor stores its int argument, loads
// "Skirmish.ini", decodes the "UserNames" value from quoted-printable
// to Unicode and splits it on "," into the list, then copies the
// "CurrentUserName" value into the trailing string. The destructor
// tears the string and the list down before the base. Write rebuilds
// the "UserNames" entry from the list through the 0x0043C559 helper
// before forwarding to UserPreferences::write.

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

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

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase();
	Int compare(const char *other) const;
	Int compareNoCase(const char *other) const;
	Bool startsWith(const StringBase &other) const throw();
	void set(const T *text);
	void set(const StringBase<T> &other);
	void trim(void);
	Bool nextToken(StringBase *token, const char *seps);
	void concat(const StringBase<T> &other);

protected:
	BfmeStringData<T> *m_data;
};

template <> class StringBase<unsigned short>
{
	friend class UnicodeString;
	StringBase(const StringBase &other);
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	bool isEmpty() const;
	int compare(const StringBase &other) const;
	int compareNoCase(const StringBase &other) const throw();
	void set(const StringBase &other);
	void trim(void);
	Bool nextToken(StringBase *token, const unsigned short *seps);
	void concat(const StringBase &other);
	void concat(const unsigned short *text);

protected:
	BfmeStringData<unsigned short> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	static const AsciiString TheEmptyString;

	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString &operator=(const AsciiString &other);
	AsciiString &operator=(const char *text) { set(text); return *this; }

	const char *str() const { return m_data ? &m_data->text[0] : ""; }
	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	void format(const char *fmt, ...);
	void toLower();
	Bool operator==(const char *other) const { return compare(other) == 0; }
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	int compare(const UnicodeString &other) const
	{
		return StringBase<unsigned short>::compare(other);
	}
	void translate(const char *text);
	void trim(void) { StringBase<unsigned short>::trim(); }
	Bool nextToken(UnicodeString *token, const unsigned short *seps)
	{
		return StringBase<unsigned short>::nextToken(token, seps);
	}
	const unsigned short *str() const { return m_data ? &m_data->text[0] : L""; }
};

inline bool operator==(const UnicodeString &a, const UnicodeString &b)
{
	return a.compare(b) == 0;
}

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

	void rva00535781(void);

protected:
	UnicodeString m_filename;
};

UnicodeString QuotedPrintableToUnicodeString(AsciiString original);

// Zero Hour QP encoder for the write path: the wide-to-Ascii direction
// (retail 0x0053544C, rowed from quoted_printable_encoders.cpp).
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);

// Retail's map lookup is throw(): the key temporaries carry EH state for
// their own construction but no extra state across the find call itself.
// _STL::map::find is not throw(), so the lookup goes through this
// layout-compatible shim whose find is declared throw(). Its call is
// pinned to the shared _M_find worker at 0x001F8437.
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

extern UnicodeString g_emptyProfilePath;

class ProfilePreferences : public UserPreferences
{
public:
	ProfilePreferences(int profileKind);
};

class RealTimeStatsPreferences : public ProfilePreferences
{
public:
	RealTimeStatsPreferences(const UnicodeString &profilePath);
	virtual ~RealTimeStatsPreferences();
	virtual void loadProfileStats(const UnicodeString &profilePath);
	static Bool deleteStatsFile(const UnicodeString &profilePath);
};

class StrategicStatsPreferences : public ProfilePreferences
{
public:
	StrategicStatsPreferences(const UnicodeString &profilePath);
	virtual ~StrategicStatsPreferences();
	virtual void loadProfileStats(const UnicodeString &profilePath);
	static Bool deleteStatsFile(const UnicodeString &profilePath);
};

// TheSkirmishGameInfo (0x00E02EF0) and its rowed getMap.
class GameSlot
{
public:
	char m_pad[0x5C];
	int m_heroIndex5C;
};

class GameInfo
{
public:
	AsciiString getMap() const;
	GameSlot *getSlot(int index);
};

extern GameInfo *TheSkirmishGameInfo;

AsciiString GameInfoToAsciiString(const GameInfo *info, bool flag);

class SkirmishPreferences : public UserPreferences
{
public:
	SkirmishPreferences(Int profileIndex);
	virtual ~SkirmishPreferences();
	virtual Bool write(void);
	_STL::list<UnicodeString> getUserNames_Rva0043C2D0(void);
	void setCurrentUserName(const UnicodeString &newName);
	AsciiString formatProfileKey(const AsciiString *keySource, const char *name);
	AsciiString buildProfileKey(const char *name);
	AsciiString encodeUserKey(const UnicodeString &user, const char *name);
	void Rva0043BFDB(const UnicodeString &user, int profileIndex);
	UnicodeString Rva0043B9F5(void);
	Bool Rva0043B9E8(void);
	UnicodeString Rva0043BB88(void);
	void Rva0043BE36(const AsciiString &mapName);
	void rva0043BE7C(void);
	// Unrowed 0x0043BD36 (256 bytes; reads TheSkirmishGameInfo's slots into
	// the preferences), pinned by address.
	void rva0043BD36(void);
	int Rva0043BBB6(UnicodeString user);
	void Rva0043C2EB(const UnicodeString &user);
	void rva0043C612(const UnicodeString &user);

private:
	void rebuildUserNamesEntry(void);

	Int m_profileIndex;
	_STL::list<UnicodeString> m_userNames;
	AsciiString m_currentUserName;
};

// ??0SkirmishPreferences@@QAE@H@Z @0x43C128
SkirmishPreferences::SkirmishPreferences(Int profileIndex)
	: m_profileIndex(profileIndex), m_userNames(0)
{
	UserPreferences::load("Skirmish.ini");

	UnicodeString userNames;
	UnicodeString token;

	SkirmishFindNode *it;
	{
		AsciiString key("UserNames");
		it = ((const SkirmishFindMap *)(const PreferenceMap *)this)->find(key);
	}
	if (it == ((const SkirmishFindMap *)(const PreferenceMap *)this)->end())
		return;

	userNames = QuotedPrintableToUnicodeString(it->m_value);
	userNames.trim();
	while (userNames.nextToken(&token, L","))
		m_userNames.push_back(token);

	{
		AsciiString currentKey("CurrentUserName");
		it = ((const SkirmishFindMap *)(const PreferenceMap *)this)->find(currentKey);
	}
	if (it == ((const SkirmishFindMap *)(const PreferenceMap *)this)->end())
		return;

	((StringBase<char> *)&m_currentUserName)->set(*(const StringBase<char> *)&it->m_value);
}

// ??1SkirmishPreferences@@UAE@XZ @0x43C286
SkirmishPreferences::~SkirmishPreferences()
{
}

// ?getUserNames_Rva0043C2D0 @0x43C2D0: returns m_userNames by value
// (copy ctor 0x43C0D0); callers at 0x522589/0x5226F0 iterate the list.
_STL::list<UnicodeString> SkirmishPreferences::getUserNames_Rva0043C2D0(void)
{
	return m_userNames;
}

// ?write@SkirmishPreferences@@UAE_NXZ @0x43C6C7
Bool SkirmishPreferences::write(void)
{
	rebuildUserNamesEntry();
	return UserPreferences::write();
}

// ?setCurrentUserName@SkirmishPreferences@@QAEXABVUnicodeString@@@Z @0x43C4D2
void SkirmishPreferences::setCurrentUserName(const UnicodeString &newName)
{
	((StringBase<char> *)&m_currentUserName)->set(
		(const StringBase<char> &)UnicodeStringToQuotedPrintable(newName));

	AsciiString key("CurrentUserName");
	AsciiString &slot = (*this)[key];
	((StringBase<char> *)&slot)->set(*(const StringBase<char> *)&m_currentUserName);
}

// ?formatProfileKey@SkirmishPreferences@@QAE?AVAsciiString@@PBV2@PBD@Z @0x43BA95
AsciiString SkirmishPreferences::formatProfileKey(const AsciiString *keySource, const char *name)
{
	AsciiString key;
	key.format(":%d:%s:%s", m_profileIndex, keySource->str(), name);
	return key;
}

// ?buildProfileKey@SkirmishPreferences@@QAE?AVAsciiString@@PBD@Z @0x43BB6A
AsciiString SkirmishPreferences::buildProfileKey(const char *name)
{
	return formatProfileKey(&m_currentUserName, name);
}

// ?encodeUserKey@SkirmishPreferences@@QAE?AVAsciiString@@ABVUnicodeString@@PBD@Z @0x43BB08
AsciiString SkirmishPreferences::encodeUserKey(const UnicodeString &user, const char *name)
{
	return formatProfileKey(&UnicodeStringToQuotedPrintable(user), name);
}

void SkirmishPreferences::Rva0043BFDB(const UnicodeString &user, int profileIndex)
{
	int saved = m_profileIndex;
	m_profileIndex = profileIndex;
	AsciiString prefix = encodeUserKey(user, "");
	for (PreferenceMap::iterator it = begin(); it != end(); ) {
		const AsciiString &key = it->first;
		if (key.startsWith(prefix)) {
			PreferenceMap::iterator cur = it;
			++it;
			erase(cur);
		} else {
			++it;
		}
	}
	m_profileIndex = saved;
}

static UnicodeString g_emptyUserName;

UnicodeString SkirmishPreferences::Rva0043BB88(void)
{
	if (m_userNames.empty())
		return g_emptyUserName;
	return m_userNames.front();
}

void SkirmishPreferences::Rva0043BE36(const AsciiString &mapName)
{
	setAsciiString(buildProfileKey("Map"), mapName);
}

int SkirmishPreferences::Rva0043BBB6(UnicodeString user)
{
	int index = 0;
	for (_STL::list<UnicodeString>::iterator it = m_userNames.begin(); it != m_userNames.end(); ++it, ++index) {
		if (user.compareNoCase(*it) == 0)
			return index;
	}
	return -1;
}

void SkirmishPreferences::Rva0043C2EB(const UnicodeString &user)
{
	m_userNames.remove(user);
	write();
	Rva0043BFDB(user, 0);
	RealTimeStatsPreferences::deleteStatsFile(user);
	Rva0043BFDB(user, 1);
	StrategicStatsPreferences::deleteStatsFile(user);
}

// ?Rva0043B9F5@SkirmishPreferences@@QAE?AVUnicodeString@@XZ @0x0043B9F5 160B
// Current-user-name getter: QP-decodes m_currentUserName (+0x1c) via rowed
// 0x005355F2, trims, defaults empty to UnicodeString::TheEmptyString
// (0x00A0C898) and returns by value. Class proven by same-object calls in
// 0x00521B56 (edi+0x698 used for Rva0043BBB6/setCurrentUserName/write and
// this body) and by +0x1c matching m_currentUserName in ctor 0x43C128 and
// setter 0x43C4D2. Honest Rva name; no donor proves a real method name.
UnicodeString SkirmishPreferences::Rva0043B9F5(void)
{
	UnicodeString tmp;
	tmp = QuotedPrintableToUnicodeString(m_currentUserName);
	tmp.trim();
	if (tmp.isEmpty())
		tmp = UnicodeString::TheEmptyString;
	return tmp;
}

// ?Rva0043B9E8@SkirmishPreferences@@QAE_NXZ @0x0043B9E8 13B
// User-names non-empty test: reads m_userNames (+0x18) head and returns
// ![head==head]. Class proven by +0x18 matching m_userNames in ctor
// 0x43C128 and Rva0043BB88; callers at 0x5217C4/0x522352/0x52288E.
// Honest Rva name.
Bool SkirmishPreferences::Rva0043B9E8(void)
{
	return !m_userNames.empty();
}

// ?rva0043C612@SkirmishPreferences@@QAEXABVUnicodeString@@@Z @0x0043C612 181B
// Add-user: appends the profile to m_userNames (+0x18), rebuilds the
// UserNames entry, saves Skirmish.ini through slot-3 write, then resets
// both stats files for the new profile (empty-path ctor, load user file,
// clear entries, stamp ProfileCreatedDate, write back). Class proven by
// +0x18 matching m_userNames in ctor 0x43C128 and Rva0043BB88; callees all
// rowed or pinned. Honest Rva name.
void SkirmishPreferences::rva0043C612(const UnicodeString &user)
{
	m_userNames.push_back(user);
	rebuildUserNamesEntry();
	write();
	RealTimeStatsPreferences realTime(g_emptyProfilePath);
	realTime.loadProfileStats(user);
	realTime.clear();
	realTime.rva00535781();
	realTime.write();
	StrategicStatsPreferences strategic(g_emptyProfilePath);
	strategic.loadProfileStats(user);
	strategic.clear();
	strategic.rva00535781();
	strategic.write();
}
// ?g_emptyProfilePath@@3VUnicodeString@@A: the global at VA 0xe0c898 is ?TheEmptyString@UnicodeString@@2V1@A.
#pragma comment(linker, "/alternatename:?g_emptyProfilePath@@3VUnicodeString@@A=?TheEmptyString@UnicodeString@@2V1@A")

// Retail 0x0043BE7C, 77 bytes. Name unknown: with a skirmish game set up,
// keeps its map and then its slots (0x0043BD36) in the preferences.
void SkirmishPreferences::rva0043BE7C(void)
{
	if (!TheSkirmishGameInfo)
		return;
	Rva0043BE36(TheSkirmishGameInfo->getMap());
	rva0043BD36();
}

// ?rva0043BD36@SkirmishPreferences@@QAEXXZ @0x0043BD36 256B.
// Keeps the skirmish map plus 8 hero indexes in the preferences: writes the
// GameInfo string under the GameInfo profile key, then accumulates "%d:"
// slot values and writes them under HeroIndexes. Evidence: pin
// ?rva0043BD36@SkirmishPreferences@@QAEXXZ; caller 0x0043BEB7 in
// rva0043BE7C; rowed GameInfoToAsciiString 0x00400AF8 plus buildProfileKey
// 0x0043BB6A plus setAsciiString slot 0x30 plus getSlot 0x003FF29F plus
// format 0x00038150 plus concat 0x00006987 plus releaseBuffer 0x00036410;
// TheSkirmishGameInfo 0x00A02EF0; strings GameInfo HeroIndexes %d:.
void SkirmishPreferences::rva0043BD36(void)
{
	if (!TheSkirmishGameInfo)
		return;
	AsciiString gameInfoValue = GameInfoToAsciiString(TheSkirmishGameInfo, true);
	setAsciiString(buildProfileKey("GameInfo"), gameInfoValue);
	gameInfoValue.set(":");
	AsciiString num;
	for (unsigned int i = 0; i < 8; ++i) {
		GameSlot *slot = TheSkirmishGameInfo->getSlot(i);
		int v = -1;
		if (slot)
			v = slot->m_heroIndex5C;
		num.format("%d:", v);
		((StringBase<char> *)&gameInfoValue)->concat(*(StringBase<char> *)&num);
	}
	setAsciiString(buildProfileKey("HeroIndexes"), gameInfoValue);
}
