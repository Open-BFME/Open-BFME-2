// cl: /DNDEBUG /MD /EHsc
// ?rva000551C2@MilesAudioManager@@QAEXH@Z @0x000551C2 106B
// Guarded removal of the vector<BfmePod8> entry at +0xB54 whose first word equals
// the argument: the mutex zone at +0x9D4 is held, the first match is erased through
// the rowed vector<BfmePod8>::erase 0x00054B3F and the flag at +0x6AA is raised.
// Layout is the one MilesAudioManagerRva0005710F.cpp proves for the same members.
// A minimal vector view: the rowed erase 0x00054B3F is the STLport vector<BfmePod8>::erase.
//
// Codegen: retail has the EH frame and the or [ebp-4],-1 before the guard's dtor but
// no state-0 store: every call in the guard's lifetime is nothrow (the rowed erase is
// declared throw()) while the scope still has two exits, so the found entry returns
// from inside the loop instead of breaking.
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
    T *begin() { return m_start; }
    T *end() { return m_finish; }
    T *erase(T *position) throw();
private:
    T *m_start;
    T *m_finish;
    T *m_end_of_storage;
};
}

struct BfmePod8 { int a[2]; };

#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"

class MilesAudioManager
{
public:
    virtual void rva000551C2(int key);
private:
    char m_pad0[0x6a6];
    bool m_flag6AA;
    char m_pad6AB[0x9D4 - 0x6AB];
    int m_mutex9D4;
    char m_pad9D8[0xB54 - 0x9D8];
    _STL::vector<BfmePod8> m_vecB54;
};

void MilesAudioManager::rva000551C2(int key)
{
    MilesMutexGuard guard(&m_mutex9D4, 0);
    for (BfmePod8 *it = m_vecB54.begin(); it != m_vecB54.end(); ++it) {
        if (it->a[0] == key) {
            m_vecB54.erase(it);
            m_flag6AA = true;
            return;
        }
    }
}
