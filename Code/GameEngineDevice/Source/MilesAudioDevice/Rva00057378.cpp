// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 00057378..00057408, RET8. The manager receiver and mutex at
// +9D4 follow the rowed Miles siblings. Target bytes find a 32-bit key in
// the hash table at +104, forward each equal-key mapped value to the
// rowed 000562A2 helper, and forward the original key when absent.
// The original method name and the meaning of the mapped keys are unknown.
#include <hash_map>

class MilesMutexGuard
{
public:
    MilesMutexGuard(void *, int);
    ~MilesMutexGuard();
private:
    void *mutex;
    bool held;
};

typedef _STL::hash_multimap<unsigned int, int> MilesKeyAliases;

class MilesAudioManager
{
public:
    void rva00057378(unsigned int key, const void *value);
    void rva000562A2(int key, const void *value);
private:
    char at00[0x104];
    MilesKeyAliases aliases;
    char atAfterAliases[0x9d4 - 0x104 - sizeof(MilesKeyAliases)];
    void *mutex;
};

void MilesAudioManager::rva00057378(unsigned int key, const void *value)
{
    MilesMutexGuard guard(&mutex, 0);
    MilesKeyAliases::iterator it = aliases.find(key);
    if (it == aliases.end()) {
        rva000562A2(key, value);
    } else {
        do {
            rva000562A2(it->second, value);
            ++it;
        } while (it != aliases.end() && it->first == key);
    }
}
