// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
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

private:
	const AsciiString &makeKey(const char *key) const;

	Int m_mode;
	mutable AsciiString m_key;
};

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
Bool LANPreferences::loadFromIniFile(void)
{
	return UserPreferences::load("NetworkPref.ini");
}

// ??0LANPreferences@@QAE@H@Z @0x44D2F5
LANPreferences::LANPreferences(Int mode) : GameModePreferences(mode)
{
	loadFromIniFile();
}
