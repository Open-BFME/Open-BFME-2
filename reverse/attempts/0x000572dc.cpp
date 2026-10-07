// ?rva000572DC@MilesAudioManager@@QAE_NI@Z
// partial score=0.8 date=2026-10-07
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
struct BfmeEventPositionView;

class MilesAudioManager
{
public:
    void rva00057378(unsigned int key, const void *value);
    void rva000562A2(int key, const void *value);
    bool rva000572DC(unsigned int key);
    bool rva00057492(unsigned int key, BfmeEventPositionView *output);
    bool rva0005623E(int key, void **output, int flags);
    bool rva000562FA(int key, BfmeEventPositionView *output);
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

// Native 000572DC..00057378, RET4. Same target-measured alias table and
// guard as 00057378; succeeds when the rowed lookup accepts any mapped key.
bool MilesAudioManager::rva000572DC(unsigned int key)
{
    bool found = false;
    MilesMutexGuard guard(&mutex, 0);
    MilesKeyAliases::iterator end = aliases.end();
    MilesKeyAliases::iterator it = aliases.find(key);
    if (it == end) {
        found = rva0005623E(key, 0, 0);
    } else {
        do {
            if (rva0005623E(it->second, 0, 0)) {
                found = true;
                break;
            }
            ++it;
        } while (it != end && it->first == key);
    }
    return found;
}

// Native 00057492..00057530, RET8. Independent call sites prove the
// position-query pointer ABI; stop on the first successful mapped query.
bool MilesAudioManager::rva00057492(unsigned int key, BfmeEventPositionView *output)
{
    bool found = false;
    MilesMutexGuard guard(&mutex, 0);
    MilesKeyAliases::iterator end = aliases.end();
    MilesKeyAliases::iterator it = aliases.find(key);
    if (it == end) {
        found = rva000562FA(key, output);
    } else {
        do {
            if (rva000562FA(it->second, output)) {
                found = true;
                break;
            }
            ++it;
        } while (it != end && it->first == key);
    }
    return found;
}
