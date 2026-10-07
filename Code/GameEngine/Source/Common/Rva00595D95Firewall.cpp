// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00595D95@Rva00595D95@@QAE_NXZ @0x00595D95 177B evidence: FirewallNeedToRefresh TRUE strings plus TheWritableGlobalData firewallBehavior+0xA4C via OptionPreferences find; callers 0x005182DE 0x00519C83 0x00572506; private StringBase kept: shared header emits wrappers plus extra EH states; throw lever plus early-return spelling
#pragma optimize("t", on)
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#pragma optimize("", on)
#include <stdlib.h>

typedef bool Bool;
typedef int Int;

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
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
public:
	StringBase() : m_data(0) {}
	~StringBase();
	Int compareNoCase(const char *other) const throw();
protected:
	BfmeStringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
};

bool operator<(const AsciiString &left, const AsciiString &right) throw();

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const throw()
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
	virtual float getReal(const AsciiString &key, float defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
protected:
	UnicodeString m_filename;
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
};

class GlobalData
{
public:
	char m_pad[0xA4C];
	int m_firewallBehavior;
};

extern GlobalData *TheWritableGlobalData;

class Rva00595D95
{
public:
	bool rva00595D95();
private:
	char m_pad00[4];
	int m_04;
	char m_pad08[0x174];
	int m_17C;
};

bool Rva00595D95::rva00595D95()
{
	OptionPreferences prefs;
	OptionPreferences::const_iterator it = prefs.find("FirewallNeedToRefresh");
	if (it != prefs.end()) {
		AsciiString val = it->second;
		if (val.compareNoCase("TRUE") == 0)
			TheWritableGlobalData->m_firewallBehavior = false;
	}
	if (TheWritableGlobalData->m_firewallBehavior == 0) {
		m_04 = 1;
		m_17C = 1;
		return false;
	}
	return true;
}
