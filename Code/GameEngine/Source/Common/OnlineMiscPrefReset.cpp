// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Scratch Online-Files MiscPref reset (retail 0x0055478A, 140B).
// The body formats "Online Files\MiscPref%d.ini" for a profile slot, loads
// a scratch UserPreferences from that file, clears it, writes it back, and
// releases the owner. Retail never references this copy: no E8 callers, no
// address-taken immediates, no vtable or data slots hold it. Twin logic with
// different enclosing signatures lives in 0x0038470E, 0x00384A62 and
// 0x005580FB, which is why the three unread stack slots below exist here.
// Class and member names are descriptive; no retail spellings are known.

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

// Owner released on every path except a null owner. Only the reference
// count at +0x54 is observed; the rest of the layout is unreconstructed.
struct MiscPrefOwner
{
	int m_unreconstructed_00[21];
	int m_refCount;
};

// resetOnlineMiscPref @0x55478A
void resetOnlineMiscPref(Int reserved1, Int profileIndex, Int reserved2, Int reserved3, Int saveFlag, Int reserved4, MiscPrefOwner *owner)
{
	MiscPrefOwner *o = owner;
	if (!o)
		return;

	if (saveFlag)
	{
		UserPreferences prefs;
		AsciiString path;
		path.format("%s\\MiscPref%d.ini", "Online Files", profileIndex);
		prefs.load(path);
		prefs.clear();
		prefs.write();
	}

	--o->m_refCount;
}
