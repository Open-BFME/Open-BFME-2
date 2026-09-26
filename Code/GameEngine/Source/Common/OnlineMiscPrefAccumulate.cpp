// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Online-Files MiscPref stat accumulator (retail 0x00384A62, 887B).
// Loads "Online Files\MiscPref%d.ini" for a profile slot into a scratch
// UserPreferences, then accumulates abs(atoi()) of the six digit keys
// "0".."5" into two per-profile counters (keys "0".."2" feed +0x140,
// keys "3".."5" feed +0x13C). Missing keys contribute nothing: each key
// is presence-checked with a short-lived lookup before its value is
// re-looked-up and added. Twin of the rowed sumOnlineMiscPrefs at
// 0x0038470E (which sums the same six keys) and resetOnlineMiscPref at
// 0x0055478A (which formats the same path); the two enclosing callers
// live in the unclaimed 0x00384A62 cluster. Class and function names are
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
extern "C" int __cdecl abs(int value) throw();

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

// The GameSpy session info singleton (0x00E02320), as far as this body
// reaches it: slot 0x178 gates the whole accumulation (a count that must
// be positive) and slot 0x17c refreshes something when the MiscPref digit
// sum for the slot is zero. Placeholder slots keep the vtable layout; the
// two used slots return Int.
class GameSpyInfoInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8c();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9c();
	virtual void slota0();
	virtual void slota4();
	virtual void slota8();
	virtual void slotac();
	virtual void slotb0();
	virtual void slotb4();
	virtual void slotb8();
	virtual void slotbc();
	virtual void slotc0();
	virtual void slotc4();
	virtual void slotc8();
	virtual void slotcc();
	virtual void slotd0();
	virtual void slotd4();
	virtual void slotd8();
	virtual void slotdc();
	virtual void slote0();
	virtual void slote4();
	virtual void slote8();
	virtual void slotec();
	virtual void slotf0();
	virtual void slotf4();
	virtual void slotf8();
	virtual void slotfc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13c();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14c();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15c();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16c();
	virtual void slot170();
	virtual void slot174();
	virtual Int slot178();
	virtual Int slot17c();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

Int sumOnlineMiscPrefs(Int profileIndex);

// Per-profile MiscPref counters. Only the two accumulators and the
// profile slot are observed; the rest of the layout is unreconstructed.
struct OnlineMiscProfileStats
{
	unsigned char m_pad[0x13C];
	Int m_highDigitStats;
	Int m_lowDigitStats;
	unsigned char m_mid[0xC];
	Int m_profileSlot;
};

// ?accumulateOnlineMiscPrefs@@YAXPAUOnlineMiscProfileStats@@@Z @0x384A62
void accumulateOnlineMiscPrefs(OnlineMiscProfileStats *stats)
{
	OnlineMiscProfileStats *s = stats;
	if (!s)
		return;
	if (s->m_profileSlot == 0)
		return;

	if (TheGameSpyInfo->slot178() > 0)
	{
		if (sumOnlineMiscPrefs(s->m_profileSlot) == 0)
			TheGameSpyInfo->slot17c();
	}
	if (TheGameSpyInfo->slot178() < 1)
		return;

	UserPreferences prefs;
	AsciiString path;
	path.format("%s\\MiscPref%d.ini", "Online Files", s->m_profileSlot);
	prefs.load(path);

	{
		Bool found;
		{
			AsciiString key("0");
			SkirmishFindNode *last = FINDER->end();
			found = FINDER->find(key) != last;
		}
		if (found)
		{
			AsciiString valueKey("0");
			const char *text = foundDigitText(FINDER->find(valueKey));
			s->m_lowDigitStats += abs(atoi(text));
		}
	}
	{
		Bool found;
		{
			AsciiString key("1");
			SkirmishFindNode *last = FINDER->end();
			found = FINDER->find(key) != last;
		}
		if (found)
		{
			AsciiString valueKey("1");
			const char *text = foundDigitText(FINDER->find(valueKey));
			s->m_lowDigitStats += abs(atoi(text));
		}
	}
	{
		Bool found;
		{
			AsciiString key("2");
			SkirmishFindNode *last = FINDER->end();
			found = FINDER->find(key) != last;
		}
		if (found)
		{
			AsciiString valueKey("2");
			const char *text = foundDigitText(FINDER->find(valueKey));
			s->m_lowDigitStats += abs(atoi(text));
		}
	}
	{
		Bool found;
		{
			AsciiString key("3");
			SkirmishFindNode *last = FINDER->end();
			found = FINDER->find(key) != last;
		}
		if (found)
		{
			AsciiString valueKey("3");
			const char *text = foundDigitText(FINDER->find(valueKey));
			s->m_highDigitStats += abs(atoi(text));
		}
	}
	{
		Bool found;
		{
			AsciiString key("4");
			SkirmishFindNode *last = FINDER->end();
			found = FINDER->find(key) != last;
		}
		if (found)
		{
			AsciiString valueKey("4");
			const char *text = foundDigitText(FINDER->find(valueKey));
			s->m_highDigitStats += abs(atoi(text));
		}
	}
	{
		Bool found;
		{
			AsciiString key("5");
			SkirmishFindNode *last = FINDER->end();
			found = FINDER->find(key) != last;
		}
		if (found)
		{
			AsciiString valueKey("5");
			const char *text = foundDigitText(FINDER->find(valueKey));
			s->m_highDigitStats += abs(atoi(text));
		}
	}
}
