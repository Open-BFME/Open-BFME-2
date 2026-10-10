// cl: /O1 /MD
// AudioFileCacheThreadEntry @0x000A8525 12B: the Windows thread callback the AudioFileCache constructor (0x000A8531)
// hands to CreateThread. It loads the cache argument into ECX, runs the rowed worker 0x000A8437 (AudioFileCacheLoader.cpp)
// and returns its code with RET 4 (stdcall).
class AudioFileCache
{
public:
	unsigned long rva000A8437();
};

unsigned long __stdcall AudioFileCacheThreadEntry(void *cache)
{
	return ((AudioFileCache *)cache)->rva000A8437();
}
