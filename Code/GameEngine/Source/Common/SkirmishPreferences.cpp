// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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

	m_currentUserName = it->m_value;
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
	m_currentUserName = UnicodeStringToQuotedPrintable(newName);

	AsciiString key("CurrentUserName");
	AsciiString &slot = (*this)[key];
	slot = m_currentUserName;
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
