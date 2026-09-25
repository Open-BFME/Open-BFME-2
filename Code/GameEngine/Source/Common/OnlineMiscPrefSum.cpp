// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Scratch Online-Files MiscPref reader (retail 0x0038470E, 754B).
// Loads "Online Files\MiscPref%d.ini" for a profile slot into a scratch
// UserPreferences, then sums atoi() of the six digit keys "0".."5"
// (missing keys and empty values contribute through the str() empty
// fallback). Twin of the rowed resetOnlineMiscPref at 0x0055478A, which
// formats the same path and runs the same load; the digit-key loop is the
// read direction of that write path. The two enclosing callers live in
// the unclaimed 0x00384A62 cluster. Class and function names are
// descriptive; no retail spellings are known.

#include <map>

typedef bool Bool;
typedef int Int;
typedef float Real;

// No EH state around a retail key temporary, so the lookup and the
// conversion below are declared throw(). The find spelling reuses the
// SkirmishFindMap throw() shim (and its existing 0x001F8437 pin): the
// node layout retails here reads the value at +0x14, exactly the shim's
// m_value.
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s) throw();

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

protected:
	BfmeStringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	void __cdecl format(const char *format, ...);

	const char *str() const { return m_data ? &m_data->text[0] : ""; }
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
	virtual Bool write(void);

protected:
	// Wide filename member keeps the layout of the rowed class; this body
	// never touches it.
	void *m_filename;
};

// Layout-compatible throw() view of the preference-map tree, shared with
// the SkirmishPreferences TU: the lookup resolves to the rowed _M_find
// worker through that TU's pin. The value slot exposes the value string's
// data pointer directly: reading it with the empty fallback below is the
// inlined AsciiString::str() (m_data ? m_data->text : ""), spelled this
// way because a method call on the member would materialize its address
// while retail folds the read into a single [node+0x14] load.
struct SkirmishFindNode
{
	unsigned char m_pad[0x14];
	BfmeStringData<char> *m_stringData;
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

#define FINDER ((const SkirmishFindMap *)(const PreferenceMap *)&prefs)

// Value text of a found digit entry: the empty fallback is the inlined
// AsciiString::str(). A helper (rather than a named local) so the loaded
// data pointer stays in eax the way retail keeps it.
__forceinline const char *foundDigitText(const SkirmishFindNode *hit)
{
	const BfmeStringData<char> *strData = hit->m_stringData;
	return strData ? (const char *)strData->text : "";
}

// ?sumOnlineMiscPrefs@@YAHH@Z @0x38470E
Int sumOnlineMiscPrefs(Int profileIndex)
{
	Int total = 0;
	if (profileIndex == 0)
		return 0;

	UserPreferences prefs;
	AsciiString path;
	path.format("%s\\MiscPref%d.ini", "Online Files", profileIndex);
	prefs.load(path);

	if (FINDER->find("0") != FINDER->end())
		total = atoi(foundDigitText(FINDER->find("0")));
	if (FINDER->find("1") != FINDER->end())
		total += atoi(foundDigitText(FINDER->find("1")));
	if (FINDER->find("2") != FINDER->end())
		total += atoi(foundDigitText(FINDER->find("2")));
	if (FINDER->find("3") != FINDER->end())
		total += atoi(foundDigitText(FINDER->find("3")));
	if (FINDER->find("4") != FINDER->end())
		total += atoi(foundDigitText(FINDER->find("4")));
	if (FINDER->find("5") != FINDER->end())
		total += atoi(foundDigitText(FINDER->find("5")));

	return total;
}
