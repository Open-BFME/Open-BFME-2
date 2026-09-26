// ?setUserName@LanLobbyUserNamePrefs@@QAEXVUnicodeString@@@Z
// partial score=0.99 date=2026-09-26
// ?setUserName@LanLobbyUserNamePrefs@@QAEXVUnicodeString@@@Z
// partial score=0.99 date=2026-09-26
// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// LAN-lobby user-name preference (retail 0x0044D47F): a UserPreferences
// whose setUserName stores the quoted-printable encoding of a wide name
// under the literal "UserName" key. Zero Hour/BFME1 donor is
// LanLobbyUserNamePrefs::setUserName (same key, same shape); BFME2 takes
// the name by const reference where the donor took it by value.

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
	bool isEmpty() const;
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
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
	void translate(const char *text);
	void trim(void) { StringBase<unsigned short>::trim(); }
	Bool nextToken(UnicodeString *token, const unsigned short *seps)
	{
		return StringBase<unsigned short>::nextToken(token, seps);
	}
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

AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);

class LanLobbyUserNamePrefs : public UserPreferences
{
public:
	void setUserName(UnicodeString user);
};

// ?setUserName@LanLobbyUserNamePrefs@@QAEXVUnicodeString@@@Z @0x44D47F
void LanLobbyUserNamePrefs::setUserName(UnicodeString user)
{
	AsciiString key("UserName");
	AsciiString encoded = UnicodeStringToQuotedPrintable(user);
	(*this)[key] = encoded;
}
