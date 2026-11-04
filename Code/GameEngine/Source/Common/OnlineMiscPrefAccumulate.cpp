// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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
#include <stdlib.h>

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


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

#include "../../Include/Common/UserPreferences.h"

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

// The GameSpy session info singleton (0x00E02320): slot 94
// getAdditionalDisconnects gates the whole accumulation and slot 95
// clearAdditionalDisconnects runs when the MiscPref digit sum for the
// slot is zero.
#include "../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;
// TheGameSpyInfo: matched references place it at VA 0xe02320 (zero-filled .bss).
GameSpyInfoInterface * TheGameSpyInfo;

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
	OnlineMiscProfileStats *onlineMiscProfileStats = stats;
	if (!onlineMiscProfileStats)
		return;
	if (onlineMiscProfileStats->m_profileSlot == 0)
		return;

	if (TheGameSpyInfo->getAdditionalDisconnects() > 0)
	{
		if (sumOnlineMiscPrefs(onlineMiscProfileStats->m_profileSlot) == 0)
			TheGameSpyInfo->clearAdditionalDisconnects();
	}
	if (TheGameSpyInfo->getAdditionalDisconnects() < 1)
		return;

	UserPreferences prefs;
	AsciiString path;
	path.format("%s\\MiscPref%d.ini", "Online Files", onlineMiscProfileStats->m_profileSlot);
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
			onlineMiscProfileStats->m_lowDigitStats += abs(atoi(text));
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
			onlineMiscProfileStats->m_lowDigitStats += abs(atoi(text));
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
			onlineMiscProfileStats->m_lowDigitStats += abs(atoi(text));
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
			onlineMiscProfileStats->m_highDigitStats += abs(atoi(text));
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
			onlineMiscProfileStats->m_highDigitStats += abs(atoi(text));
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
			onlineMiscProfileStats->m_highDigitStats += abs(atoi(text));
		}
	}
}
