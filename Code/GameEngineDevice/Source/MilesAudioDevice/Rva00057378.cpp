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
    void rva00057530(unsigned int key, float value, int mode);
    void rva0005634C(int key, float value, int mode);
    bool rva000613A9(unsigned int handle);
    bool rva000615DA(unsigned int handle);
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

// Native 00057530..000575CE, RET12. Each call forwards a four-byte key,
// x87-copied float, and integer mode. Ghidra's complete 178-byte provider
// at 0005634C independently reads those three slots and compares mode to 1.
void MilesAudioManager::rva00057530(unsigned int key, float value, int mode)
{
    MilesMutexGuard guard(&mutex, 0);
    MilesKeyAliases::iterator it = aliases.find(key);
    if (it == aliases.end()) {
        rva0005634C(key, value, mode);
    } else {
        do {
            rva0005634C(it->second, value, mode);
            ++it;
        } while (it != aliases.end() && it->first == key);
    }
}

// Native 000615DA..00061680, RET4. Handles below 5 are refused. Under the
// +9D4 mutex each equal-key alias of the handle is forwarded to the 561-byte
// 000613A9 helper (or the handle itself when it has no alias); the result is
// true when any forward returned true. WorldBuilder's unnamed twin at 795370
// logs "Processing kill immediately request"; the method name is unknown.
bool MilesAudioManager::rva000615DA(unsigned int handle)
{
    if (handle < 5)
        return false;
    MilesMutexGuard guard(&mutex, 0);
    MilesKeyAliases::iterator it = aliases.find(handle);
    if (it == aliases.end())
        return rva000613A9(handle);
    bool killed = false;
    do {
        if (rva000613A9(it->second))
            killed = true;
        ++it;
    } while (it != aliases.end() && it->first == handle);
    return killed;
}
