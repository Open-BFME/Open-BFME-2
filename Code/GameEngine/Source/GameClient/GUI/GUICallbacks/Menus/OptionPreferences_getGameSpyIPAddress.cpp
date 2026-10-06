// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva002E514A@OptionPreferences@@QAEIXZ, retail 0x002E514A, 194 bytes.
// GameSpy twin of the landed getLANIPAddress at 0x002E4F98 (same 194B shape:
// stored pref matched case-insensitively against enumerated locals, fallback
// to writable global default at +0xA48). Differences from the LAN twin, all
// forced by retail: pref key "GameSpyIPAddress", per-address string via the
// rowed ?getTooltipName@MultiplayerColorDefinition (ICF-identical to
// EnumeratedIP::getIPstring copy-at-+0 body at 0x002E4336, called through a
// cast so the call resolves to the existing row), writable global
// TheWritableGlobalData, and a named Bool match flag which is what emits the
// neg/sbb/inc byte. Private StringBase/AsciiString copies with throw() on
// compareNoCase are copied verbatim from the twin TU so the tooltip temporary
// needs no EH state, matching retail. Caller at 0x0038BAB9 etc. Neighbours
// setLANIPAddress 0x002E50BB and setOnlineIPAddress.
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

	UnsignedInt rva002E514A(void);
};

class MultiplayerColorDefinition
{
public:
	AsciiString getTooltipName() const throw();
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

extern GlobalData *TheWritableGlobalData;

// ?rva002E514A@OptionPreferences@@QAEIXZ, retail 0x002E514A, 194 bytes.
UnsignedInt OptionPreferences::rva002E514A(void)
{
	AsciiString wanted = (*this)["GameSpyIPAddress"];
	IPEnumeration IPs;
	EnumeratedIP *IPlist = IPs.getAddresses();
	while (IPlist)
	{
		Bool match = (wanted.compareNoCase(((MultiplayerColorDefinition *)IPlist)->getTooltipName()) == 0);
		if (match)
			return IPlist->getIP();
		IPlist = IPlist->getNext();
	}
	return TheWritableGlobalData->m_defaultIP;
}
