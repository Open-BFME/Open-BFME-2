// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// AudioFileCacheThreadEntry @0x000A8525 12B: the Windows thread callback the AudioFileCache constructor (0x000A8531)
// hands to CreateThread. It loads the cache argument into ECX, runs the rowed worker 0x000A8437 (AudioFileCacheLoader.cpp)
// and returns its code with RET 4 (stdcall).
#include <hash_map>
#include <list>
#include <map>
#include <set>
#include "ascii_string.h"

// Base hash of open files; the key/value names of the rowed 0x000A7E7A
// constructor are address-derived (StlSweepW4Rva000A7E7A.cpp).
struct Rva000A7E7AElement { char bytes[1]; bool operator<(const Rva000A7E7AElement&)const; bool operator==(const Rva000A7E7AElement&)const; };

class Rva000A7E9E;
// The cached file (WorldBuilder: OpenAudioFile); 0x54-byte allocation and
// its 0x0010ED4C constructor (owner, name) are read from retail.
class Gen0002857E
{
public:
	Gen0002857E(Rva000A7E9E *owner, const AsciiString &name);
	char pad00[0x3C];
	int priority3C;
	char pad40[0x14];
};
class Rva0010ECB5 { public: bool rva0010ECB5(); };
class AudioFileContainer
{
public:
	AudioFileContainer(); AudioFileContainer(Gen0002857E *); ~AudioFileContainer();
private: Gen0002857E *m_target;
};
class Rva00691040Handle
{
public: Rva00691040Handle &operator=(const Rva00691040Handle &);
private: Gen0002857E *m_target;
};
class Rva000427195 { public: void *rva000A7B3C(const AsciiString *key); };

extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);

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
	void *m_thread;
	bool m_quit;
	void *m_mutex;
};
typedef char CacheSize[sizeof(AudioFileCache) == 0x54 ? 1 : -1];

unsigned long __stdcall AudioFileCacheThreadEntry(void *cache)
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
	Gen0002857E *bad = new Gen0002857E((Rva000A7E9E *)this, AsciiString(badName));
	((Rva0010ECB5 *)bad)->rva0010ECB5();
	(Rva00691040Handle &)m_bad = (const Rva00691040Handle &)AudioFileContainer(bad);
	{
		AsciiString key(badName);
		*(Gen0002857E **)((Rva000427195 *)this)->rva000A7B3C(&key) = bad;
	}
	bad->priority3C = 0;
	m_thread = CreateThread(0, 0, AudioFileCacheThreadEntry, this, 0, 0);
}
