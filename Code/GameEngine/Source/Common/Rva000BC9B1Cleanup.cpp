// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva000BC9B1@Rva000BC9B1@@QAEX_N@Z retail 0x000BC9B1 164B
// Evidence: list at +0x64 of B757D records via rowed erase 0xBC133, copy 0xB757D,
// releaseBuffer 0x36410, manager find 0x1F5B0A via TheParticleSystemManager,
// destroy 0x1F462C, handle dtor 0x4CBC0; callers 0x7A8A3 0xBFA5B 0xC4ED2 0xC79FA.
#include "ascii_string.h"
#include <list>

struct BfmeStringRecord000B757D {
    unsigned int word0;
    unsigned int word1;
    AsciiString text;
    unsigned int word2;
    unsigned char tail0;
    BfmeStringRecord000B757D(const BfmeStringRecord000B757D &o);
};

enum ParticleSystemID {
    INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystem {
public:
    void destroy();
};

struct BfmeParticleSystemHandle {
    ~BfmeParticleSystemHandle();
    ParticleSystem *m_system;
    void *m_previous;
    void *m_next;
};

struct BfmeW3DParticleHandle {
    ParticleSystem *system;
    void *previous;
    void *next;
    __forceinline ~BfmeW3DParticleHandle() { if (system) ((BfmeParticleSystemHandle *)this)->~BfmeParticleSystemHandle(); }
};

struct Rva000BC9B1;

class ParticleSystemManager {
    BfmeW3DParticleHandle findParticleSystemByID(ParticleSystemID id);
    friend struct Rva000BC9B1;
};
#pragma comment(linker, "/alternatename:?findParticleSystemByID@ParticleSystemManager@@AAE?AUBfmeW3DParticleHandle@@W4ParticleSystemID@@@Z=?findParticleSystemByID@ParticleSystemManager@@AAE?AVBfmeParticleSystemHandle@@W4ParticleSystemID@@@Z")

extern ParticleSystemManager *TheParticleSystemManager;

struct Rva000BC9B1 {
    unsigned char _pad[0x64];
    _STL::list<BfmeStringRecord000B757D, _STL::allocator<BfmeStringRecord000B757D> > m_list;
    void rva000BC9B1(bool flag);
};

void Rva000BC9B1::rva000BC9B1(bool flag)
{
    for (_STL::list<BfmeStringRecord000B757D, _STL::allocator<BfmeStringRecord000B757D> >::iterator it = m_list.begin(); it._M_node != m_list.end()._M_node;) {
        bool skip = false;
        if (flag) {
            BfmeStringRecord000B757D tmp = *it;
            if (tmp.word2 != 0)
                skip++;
        }
        BfmeW3DParticleHandle h = TheParticleSystemManager->findParticleSystemByID((ParticleSystemID)(*it).word0);
        if (!skip && h.system) {
            h.system->destroy();
            it = m_list.erase(it);
        } else {
            ++it;
        }
    }
}
