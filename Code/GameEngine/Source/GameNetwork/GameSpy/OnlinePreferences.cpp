// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Per-profile online preference files: Zero Hour's QuickMatchPreferences and
// GameSpyMiscPreferences constructors, which BFME 2 roots under
// "Online Files" (Zero Hour used "GeneralsOnline"). Retail keeps them far
// from UserPreferences.cpp (0x005DF1A3 and 0x00559711), so they get their
// own unit. The UserPreferences model is the one in
// Code/GameEngine/Source/Common/UserPreferences.cpp.

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
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();
};

// ??0QuickMatchPreferences@@QAE@XZ @0x5DF1A3
QuickMatchPreferences::QuickMatchPreferences()
{
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\QMPref%d.ini", "Online Files", TheGameSpyInfo->getLocalProfileID());
	load(userPrefFilename);
}

// ??0GameSpyMiscPreferences@@QAE@XZ @0x559711
GameSpyMiscPreferences::GameSpyMiscPreferences()
{
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\GSMiscPref%d.ini", "Online Files", TheGameSpyInfo->getLocalProfileID());
	load(userPrefFilename);
}
