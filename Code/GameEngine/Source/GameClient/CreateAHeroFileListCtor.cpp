// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0021DB35@@QAE@XZ
// retail 0x0021F19B..0x0021F403 (617 bytes) thiscall RET 0.
//
// The create-a-hero file list's constructor (callers 0x0021F4F0 and
// 0x0021F60D). Its vector of (file name, system flag) pairs is filled from
// "Data\SystemHeroes\" + "MyHero*.cah" through
// FileSystem::getFileListInDirectory (pinned 0x00600FC9), each entry the
// file name after its last '\' and flagged as a system hero, then sorted
// with the rowed comparator sort 0x0021F13C. Unless the flag byte
// 0x009FE34C is set it appends the user's heroes: L"MyHero*.cah" in
// TheGameState's save directory (0x002DC267) through the wide listing
// (pinned 0x006007DA, its set rowed as Rva0021C459), each name narrowed
// through AsciiString(const UnicodeString&). The class takes the name of
// its destructor 0x0021DB35 (CreateAHeroManager::LoadMyHeroList constructs
// and destroys the same local); the owner identity stays address-derived.
#include <set>
#include <vector>
#include <algorithm>
#include "ascii_string.h"
#include "unicode_string.h"

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};
typedef _STL::set<AsciiString, BfmeStringNoCaseLess> FilenameList;
// Declaration-only: the set's tree teardown is the rowed 0x0002CC38 copy.
namespace _STL {
template <> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, BfmeStringNoCaseLess, allocator<AsciiString> >::~_Rb_tree();
}

// The wide file list (a set of UnicodeString) under its rowed spelling: its
// constructor is the folded set constructor 0x000D3A71, its destructor
// 0x0021D5D5.
class Rva0021C459 : public FilenameList
{
public:
	~Rva0021C459();
};

// The file-list object is Rva0021DA13 (as AptSaveLoadRva0043684C.cpp spells
// it): its destructor is the 5-byte thunk 0x0021DA13 the unwind funclet
// jumps to; the normal path expands it into ~Rva0021C459 (0x0021D5D5).
class Rva0021DA13 : public Rva0021C459
{
};

class FileSystem
{
public:
	void getFileListInDirectory(const AsciiString &directory, const AsciiString &searchName, FilenameList &filenameList, bool searchSubdirectories) const;	// 0x00600FC9
};

class Rva006007DAFileSystem
{
public:
	void rva006007DA(const UnicodeString *directory, const UnicodeString *searchName, Rva0021C459 *filenameList, bool searchSubdirectories);	// 0x006007DA
};
// The listing is rowed as the free Rva006007DAOpen: the 81-byte provider ignores
// ECX and takes four stack words, so call that owner with the receiver this
// caller loads (the AptSaveLoadRva0043684C.cpp idiom).
void __stdcall Rva006007DAOpen(void *, void *, void *, void *);
union Rva006007DACall
{
	void (__stdcall *target)(void *, void *, void *, void *);
	void (Rva006007DAFileSystem::*member)(const UnicodeString *, const UnicodeString *, Rva0021C459 *, bool);
};
extern FileSystem *TheFileSystem;

class GameState;
extern GameState *TheGameState;

// The game state's save directory (0x002DC267), rowed under its own spelling.
class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

// The wide listing takes its strings by address; retail passes temporaries.
static __forceinline const UnicodeString *byAddress(const UnicodeString &text)
{
	return &text;
}

extern unsigned char g_rva005B5C02Flag;

typedef _STL::pair<const AsciiString, char> HeroFileEntry;

// The sorted element and comparator under their rowed spellings.
class Rva0021915B;
struct Rva0021B753
{
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};

namespace _STL {
template <> void vector<HeroFileEntry, allocator<HeroFileEntry> >::push_back(const HeroFileEntry &value);
template <> void sort<Rva0021915B *, Rva0021B753>(Rva0021915B *first, Rva0021915B *last, Rva0021B753 comp);
}

class Rva0021DB35
{
public:
	Rva0021DB35();

private:
	_STL::vector<int> m_files;	// the (file name, system flag) pairs
};

Rva0021DB35::Rva0021DB35()
{
	_STL::vector<HeroFileEntry> &files = *reinterpret_cast<_STL::vector<HeroFileEntry> *>(&m_files);
	{
		FilenameList filenameList;
		TheFileSystem->getFileListInDirectory(AsciiString("Data\\SystemHeroes\\"), AsciiString("MyHero*.cah"), filenameList, false);
		for (FilenameList::iterator it = filenameList.begin(); it != filenameList.end(); ++it)
		{
			AsciiString path = *it;
			const char *slash = ((const StringBase<char> &)(path)).reverseFind('\\');
			HeroFileEntry entry(AsciiString(slash ? slash + 1 : path.str()), false);
			entry.second = true;
			files.push_back(entry);
		}
	}
	_STL::sort(reinterpret_cast<Rva0021915B *>(&*files.begin()), reinterpret_cast<Rva0021915B *>(&*files.end()), Rva0021B753());

	if (!g_rva005B5C02Flag)
	{
		Rva0021DA13 filenameList;
		Rva006007DACall listing = {&Rva006007DAOpen};
		(((Rva006007DAFileSystem *)TheFileSystem)->*listing.member)(byAddress(((const Rva002DC267 *)TheGameState)->rva002DC267()),
			byAddress(UnicodeString(L"MyHero*.cah")), &filenameList, false);
		for (FilenameList::iterator it = filenameList.begin(); it != filenameList.end(); ++it)
		{
			AsciiString path(*(const UnicodeString *)&*it);
			const char *slash = ((const StringBase<char> &)(path)).reverseFind('\\');
			HeroFileEntry entry(AsciiString(slash ? slash + 1 : path.str()), false);
			files.push_back(entry);
		}
	}
}
