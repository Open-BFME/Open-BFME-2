// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0023C322@Rva0023C322@@QAEXXZ @0x0023C322 164B: clear flag at +0xCA then
// store current resolution as "%d %d" into OptionPreferences map slot
// "Resolution" and write it. Evidence: callee OptionPreferences ctor
// 0x002E434E plus UserPreferences write 0x003B1BF3 plus Rva002E4272 dtor
// 0x002E4272; map subscript 0x002031FB plus AsciiString assign pin 0x000366F0
// plus releaseBuffer 0x00036410 plus format 0x00038150; globals
// TheWritableGlobalData 0x009FE758 with xRes +0x30 yRes +0x34; strings
// "%d %d" 0x007E3878 and "Resolution" 0x007E386C; caller 0x00514DDA passes
// TheGameClient as this.
#include "unicode_string.h"
#include <map>

typedef bool Bool;
typedef int Int;

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other);
	void format(const char *fmt, ...);
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

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();
	virtual Bool write(void);
protected:
	UnicodeString m_filename;
};

class Rva002E4272 : public UserPreferences
{
public:
	virtual ~Rva002E4272();
};

class OptionPreferences : public Rva002E4272
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
};

class GlobalData
{
public:
	char m_pad[0x30];
	Int m_xResolution;
	Int m_yResolution;
};

extern GlobalData *TheWritableGlobalData;

class Rva0023C322
{
	char m_pad[0xCA];
	Bool m_flagCA;
public:
	void rva0023C322();
};

void Rva0023C322::rva0023C322()
{
	m_flagCA = 0;
	OptionPreferences prefs;
	AsciiString tmp;
	tmp.format("%d %d", TheWritableGlobalData->m_xResolution, TheWritableGlobalData->m_yResolution);
	{
		AsciiString key("Resolution");
		AsciiString &slot = prefs[key];
		((StringBase<char> &)slot).set(*(const StringBase<char> *)&tmp);
	}
	prefs.write();
}
