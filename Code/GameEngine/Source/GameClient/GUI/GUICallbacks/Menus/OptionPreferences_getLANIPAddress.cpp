// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// OptionPreferences::getLANIPAddress, retail 0x002E4F98 (194 bytes). Zero
// Hour's OptionsMenu.cpp body: match the stored IPAddress against the
// enumerated local addresses (case-insensitive) and fall back to
// TheGlobalData's default IP (+0xA48). EnumeratedIP::getIPstring resolves to
// its ICF-shared "copy the AsciiString at +0" body at 0x002E4336. The
// UserPreferences model is the one in Common/UserPreferences.cpp.

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
	Int compareNoCase(const StringBase &other) const throw();

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
	void translate(const char *text);
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

typedef unsigned int UnsignedInt;

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	UnsignedInt getLANIPAddress(void);
};

class EnumeratedIP
{
public:
	AsciiString getIPstring(void);
	UnsignedInt getIP(void) { return m_IP; }
	EnumeratedIP *getNext(void) { return m_next; }

private:
	AsciiString m_IPstring;
	UnsignedInt m_IP;
	EnumeratedIP *m_next;
};

class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	EnumeratedIP *getAddresses(void);

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_000[ 0xA48 ];
	UnsignedInt m_defaultIP;
};

extern GlobalData *TheGlobalData;

// ?getLANIPAddress@OptionPreferences@@QAEIXZ @0x2E4F98
UnsignedInt OptionPreferences::getLANIPAddress(void)
{
	AsciiString selectedIP = (*this)["IPAddress"];
	IPEnumeration IPs;
	EnumeratedIP *IPlist = IPs.getAddresses();
	while (IPlist)
	{
		if (selectedIP.compareNoCase(IPlist->getIPstring()) == 0)
		{
			return IPlist->getIP();
		}
		IPlist = IPlist->getNext();
	}
	return TheGlobalData->m_defaultIP;
}
