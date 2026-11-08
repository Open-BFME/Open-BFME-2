// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// Split from OnlinePreferences.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// stlport
//
// Per-profile online preference files: Zero Hour's QuickMatchPreferences,
// GameSpyMiscPreferences and LadderPreferences constructors, which BFME 2 roots under
// "Online Files" (Zero Hour used "GeneralsOnline"). Retail keeps them far
// from UserPreferences.cpp (0x005DF1A3 and 0x00559711), so they get their
// own unit. The UserPreferences model is the one in
// Code/GameEngine/Source/Common/UserPreferences.cpp.

// Retail's ladder map subscript (0x005E017A) builds the default LadderPref with
// T(), not through an out-of-line __default_constructed call.
#include <string.h>
#include <utility>
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <stdlib.h>
// Retail's tree node deallocators call the game's local free, not the import.
extern "C" void __cdecl free(void *);

struct _iobuf;
typedef struct _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *name, const unsigned short *mode);
extern "C" __declspec(dllimport) int __cdecl fprintf(FILE *fp, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *fp);
extern "C" __declspec(dllimport) char *__cdecl fgets(char *buf, int n, FILE *fp);

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"



#include "unicode_string.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

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

// Declaration-only: the rowed map<AsciiString,AsciiString>::operator[] is bound,
// this TU emits no per-flag copy of it or of the tree internals it pulls in.
namespace _STL {
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &);
}
typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

#include "../../../Include/Common/UserPreferences.h"

// The GameSpy session info singleton (0x00E02320), as far as the ignore
// list reaches it: getLocalProfileID sits in vtable slot 0x7C.
#include "../../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

#include "../../../Include/Common/QuickMatchPreferencesClass.h"

#include "../../../Include/Common/GameSpyMiscPreferencesClass.h"





















typedef long time_t;
typedef unsigned short UnsignedShort;

class LadderPref
{
public:
	LadderPref();
	LadderPref(const LadderPref &other);
	~LadderPref();
	LadderPref &operator=(const LadderPref &other);

	UnicodeString name;
	AsciiString address;
	UnsignedShort port;
	time_t lastPlayDate;
};

AsciiString AsciiStringToQuotedPrintable(AsciiString original);
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);
AsciiString QuotedPrintableToAsciiString(AsciiString original);
UnicodeString QuotedPrintableToUnicodeString(AsciiString original);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s) throw();

typedef _STL::map<time_t, LadderPref> LadderPrefMap;
// Retail's tree destructor (0x005DFE18) is the /EHs copy Rva00243177.cpp emits.
namespace _STL { template <> _Rb_tree<long, pair<long const, LadderPref>, _Select1st<pair<long const, LadderPref> >, less<long>, allocator<pair<long const, LadderPref> > >::~_Rb_tree(); }

// Zero Hour's recent-ladder preferences: a UserPreferences file plus the
// parsed LadderPrefMap at +0x14; write is overridden (vtable 0x00C77788
// slot 3 is 0x005E0026).
class LadderPreferences : public UserPreferences
{
public:
	LadderPreferences();
	virtual ~LadderPreferences();
	virtual Bool write(void);
	Bool loadProfile(Int profileID);

private:
	LadderPrefMap m_ladders;
};

// ??0LadderPreferences@@QAE@XZ @0x5DFFD3
LadderPreferences::LadderPreferences()
{
}

// ??1LadderPreferences@@UAE@XZ @0x5DFF7B
LadderPreferences::~LadderPreferences()
{
}

// ??1LadderPref@@QAE@XZ @0x5BA3C0
inline LadderPref::~LadderPref()
{
}

inline LadderPref::LadderPref()
{
}

// ?write@LadderPreferences@@UAE_NXZ @0x5E0026
Bool LadderPreferences::write(void)
{
	clear();

	static const Int MAX_LADDERS = 5;
	LadderPrefMap::iterator lpIt;
	Int count;
	for (lpIt = m_ladders.begin(), count = 0;
		lpIt != m_ladders.end() && count < MAX_LADDERS;
		++lpIt, ++count)
	{
		LadderPref p = lpIt->second;
		AsciiString ladName;
		AsciiString ladData;
		ladName.format("%s:%d", AsciiStringToQuotedPrintable(p.address).str(), p.port);
		ladData.format("%s:%d", UnicodeStringToQuotedPrintable(p.name).str(), p.lastPlayDate);
		AsciiString &slot = (*this)[ladName];
		slot = ladData;
	}

	return UserPreferences::write();
}

// ?loadProfile@LadderPreferences@@QAE_NH@Z @0x005E0201 501B
// BFME2 port of ZH LadderPreferences::loadProfile: Online Files root,
// parses base map entries into m_ladders via QP decoders. Evidence: rowed
// load slot 0x005E0026 neighbours, strings Online Files plus %s\Ladders%d.ini,
// rowed clear/format/atoi/QP/map ops, caller at 0x005BC3B1.
Bool LadderPreferences::loadProfile(Int profileID)
{
	clear();
	m_ladders.clear();
	AsciiString userPrefFilename;
	userPrefFilename.format("%s\\Ladders%d.ini", "Online Files", profileID);
	Bool success = load(userPrefFilename);
	if (!success)
		return success;

	for (LadderPreferences::iterator it = begin(); it != end(); ++it)
	{
		LadderPref p;
		AsciiString ladName = it->first;
		AsciiString ladData = it->second;

		const char *ptr = ((const StringBase<char> &)(ladName)).reverseFind(':');
		if (!ptr)
			continue;

		p.port = (UnsignedShort)atoi(ptr + 1);
		Int i;
		for (i = 0; i < strlen(ptr); ++i)
		{
			ladName.removeLastChar();
		}
		p.address = QuotedPrintableToAsciiString(ladName);

		ptr = ((const StringBase<char> &)(ladData)).reverseFind(':');
		if (!ptr)
			continue;

		p.lastPlayDate = atoi(ptr + 1);
		for (i = 0; i < strlen(ptr); ++i)
		{
			ladData.removeLastChar();
		}
		p.name = QuotedPrintableToUnicodeString(ladData);

		m_ladders[p.lastPlayDate] = p;
	}

	return true;
}
