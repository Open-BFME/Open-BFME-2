// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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
// UserPreferences slot except slot 0. The matching destructor is the
// opaque Rva00535776 row at 0x00535776 (tail-calls UserPreferences dtor).
//
// loadStatsFile at 0x00537D33 is the shared stats loader the subclasses
// below will forward to: it clears the preference map, and unless the
// incoming profile path equals the empty wide sentinel (global at
// 0x00E0C898, default-constructed at 0x007B6740), it appends the leaf name
// and runs UserPreferences::load on the result. Helper and class names
// are descriptive -- no retail spellings are known.

#include <map>
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
	void set(const T *text);
	void trim(void);
	Bool nextToken(StringBase *token, const char *seps);

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
	Int compare(const StringBase &other) const;
	bool isEmpty() const;
	void set(const StringBase &other);
	void concat(const StringBase &other);

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
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
	void translate(const char *text);
	const unsigned short *str() const { return m_data ? &m_data->text[0] : L""; }
};

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

// Empty wide sentinel the loader compares the profile path against.
extern UnicodeString g_emptyProfilePath;

// Per-class stats leaves appended to the profile path.
extern UnicodeString g_strategicStatsLeaf;
extern UnicodeString g_realTimeStatsLeaf;

class ProfilePreferences : public UserPreferences
{
public:
	ProfilePreferences(int profileKind);

protected:
	void loadStatsFile(const UnicodeString &profilePath, const UnicodeString &leafName);
};

// StrategicStatsPreferences (vtable 0x00C6913C) loads the global leaf
// "StrategicStats.ini" (UnicodeString static at 0x00E05E04, built by the
// dynamic initializer at 0x007B3AA5 from the .rdata leaf at 0x00C691D4).
// Its vtable keeps the thirteen UserPreferences slots, overrides slot 0
// with the shared deleting destructor at 0x00537E60 (already rowed), and
// appends the loadProfileStats thunk at slot 13.
class StrategicStatsPreferences : public ProfilePreferences
{
public:
	StrategicStatsPreferences(const UnicodeString &profilePath);
	virtual ~StrategicStatsPreferences();
	virtual void loadProfileStats(const UnicodeString &profilePath);
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
	virtual ~RealTimeStatsPreferences();
	virtual void loadProfileStats(const UnicodeString &profilePath);
};

// ??0ProfilePreferences@@QAE@H@Z
ProfilePreferences::ProfilePreferences(int profileKind)
{
	(void)profileKind;
}

// ?loadStatsFile@ProfilePreferences@@IAEXABVUnicodeString@@0@Z @0x537D33
void ProfilePreferences::loadStatsFile(const UnicodeString &profilePath, const UnicodeString &leafName)
{
	clear();

	if (profilePath.compare(g_emptyProfilePath) == 0)
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
