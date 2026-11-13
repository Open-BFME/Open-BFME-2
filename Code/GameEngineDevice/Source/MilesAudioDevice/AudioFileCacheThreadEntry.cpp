// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// platformsdk
// stlport
// AudioFileCacheThreadEntry @0x000A8525 12B: the Windows thread callback the AudioFileCache constructor (0x000A8531)
// hands to CreateThread. It loads the cache argument into ECX, runs the rowed worker 0x000A8437 (AudioFileCacheLoader.cpp)
// and returns its code with RET 4 (stdcall).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <list>
#include <map>
#include <set>
#include "ascii_string.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<AsciiString>(AsciiString *p) { typedef AsciiString BfmeDestroyT; p->~BfmeDestroyT(); } }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> allocator<void *>::~allocator(); }
namespace _STL { template <> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::~_Rb_tree(); }
// bfme link decl-only end

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// Base hash of open files; the key/value names of the rowed 0x000A7E7A
// constructor are address-derived (StlSweepW4Rva000A7E7A.cpp).
struct Rva000A7E7AElement { char bytes[1]; bool operator<(const Rva000A7E7AElement&)const; bool operator==(const Rva000A7E7AElement&)const; };
// Use the existing retail base-hash constructor rather than emitting its dependencies here.
namespace _STL { template <> hash_map<int,Rva000A7E7AElement>::hash_map(); }

class AudioFileCache;
// The cached file (WorldBuilder: OpenAudioFile); 0x54-byte allocation and
// its 0x0010ED4C constructor (owner, name) are read from retail.
class Gen0002857E
{
public:
	Gen0002857E(AudioFileCache *owner, const AsciiString &name);
	char pad00[0x3C];
	int priority3C;
	char pad40[0x14];
};
class Rva0010ECB5 { public: bool rva0010ECB5(); };
#include "../../../GameEngine/Include/Common/AudioFileContainer.h"
#include "../../../GameEngine/Include/Common/Rva00691040Handle.h"
#include "../../../GameEngine/Include/GameLogic/Rva000427195.h"

class AudioFileCache : public _STL::hash_map<int, Rva000A7E7AElement>
{
public:
	AudioFileCache(void *mutex);
	unsigned long rva000A8437();
private:
	_STL::list<int> m_pending[3];
	_STL::map<int, void *> m_unused20;
	_STL::set<AsciiString> m_failed;
	unsigned int m_activeBytes, m_unusedBytes, m_budget;
	AudioFileContainer m_bad;
	HANDLE m_thread;
	bool m_quit;
	void *m_mutex;
};
typedef char CacheSize[sizeof(AudioFileCache) == 0x54 ? 1 : -1];

DWORD __stdcall AudioFileCacheThreadEntry(void *cache)
{
	return ((AudioFileCache *)cache)->rva000A8437();
}

// Retail 0x000A8531, 339B; WorldBuilder 0x008E4870 names
// AudioFileCache::AudioFileCache (MilesAudioCache.cpp). Member groups match the
// rowed destructor 0x000A7CF3: base hash, three pending lists (EH vector
// iterator over the list<int> closures 0x00320095/0x00200667), map20, failed
// set2C, three zeroed counters, bad-file container44, thread48, quit4C and the
// caller's mutex50. The body registers the "\nspecial bad\n" sentinel file:
// marks it read-failed (0x0010ECB5), keeps a container to it, enters it in the
// open-file hash and starts the loader thread. The retail release build drops
// WorldBuilder's CreateThread failure diagnostic.
AudioFileCache::AudioFileCache(void *mutex)
	: m_activeBytes(0), m_unusedBytes(0), m_budget(0), m_thread(0), m_quit(false), m_mutex(mutex)
{
	char badName[] = "\nspecial bad\n";
	Gen0002857E *bad = new Gen0002857E(this, AsciiString(badName));
	((Rva0010ECB5 *)bad)->rva0010ECB5();
	(Rva00691040Handle &)m_bad = (const Rva00691040Handle &)AudioFileContainer(bad);
	{
		AsciiString key(badName);
		*(Gen0002857E **)((Rva000427195 *)this)->rva000A7B3C(&key) = bad;
	}
	bad->priority3C = 0;
	m_thread = CreateThread(0, 0, AudioFileCacheThreadEntry, this, 0, 0);
}
