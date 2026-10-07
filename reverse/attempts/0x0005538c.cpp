// ?rva0005538C@MilesAudioManager@@QAE_NXZ
// partial score=0.99 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /EHsc /MD
// stlport
// Ghidra 0x0005538C..0x00055426, 154B, manager thiscall RET.
// Target offsets and 40B music-stack stride agree with the rowed home unit.
// This query tests active streams and inactive stacks across three views
// and two systems. Its original name and the helper flag meaning are unknown.
#include <deque>

class OpaqueRefCounted;
struct OpaqueRefElement4 {
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4();
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
typedef _STL::deque<OpaqueRefElement4, _STL::allocator<OpaqueRefElement4> > MusicStack;
class MilesMutexGuard {
public:
    MilesMutexGuard(void *, int);
    ~MilesMutexGuard();
private:
    void *mutex;
    bool held;
};
class MilesAudioManager {
public:
    bool rva0005538C();
    // Native 32B forwarding body returns its output-slot address in EAX,
    // carries the receiver into 5442A and pops four dword arguments.
    void **rva000544CB(void **, int, int, int);
private:
    char at00[0x9d4];
    void *mutex;
    char at9D8[0xa48 - 0x9d8];
    void *playingStreams;
    MusicStack stacks[3][2];
    int activeSystems[3];
};

bool MilesAudioManager::rva0005538C()
{
    MilesMutexGuard guard(&mutex, 0);
    int *active = activeSystems;
    for (int view = 0; view < 3; ++view, ++active) {
        for (int system = 0; system < 2; ++system) {
            if (system == *active) {
                void *cursor;
                rva000544CB(&cursor, view, system, 1);
                if (playingStreams != cursor)
                    return true;
            } else if (!stacks[view][system].empty()) {
                return true;
            }
        }
    }
    return false;
}
