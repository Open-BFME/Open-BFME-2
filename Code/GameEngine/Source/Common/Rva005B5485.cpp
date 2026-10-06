// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?ExternFunc@Class@AptCreateAHero@@QAEXHPAD_N@Z @0x005B5485 104B
// Snprintf "%d" of outer/inner vector counts guarded by buf and flag.
// Retail: xor edx cmp buf je cmp flag jne then sel 0/1 via sub/dec,
// path1 via 0x5B045D plus rowed 0x00219D52, path0 manual sar5, both to
// rowed _snprintf 0xff. Callers none; chain via 0x00219D52.
// Honest-address method on AptCreateAHero::Class with +4 outer pointer.
#include "ascii_string.h"
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *fmt, ...);
struct OuterElem32 { char m_00[32]; };
struct Vec32 { OuterElem32 *m_start; OuterElem32 *m_finish; OuterElem32 *m_end; };
class CreateAHeroManager {
    char m_pad[0x14C];
public:
    Vec32 m_outer;
    int rva00219D52(unsigned int o);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva005B045D {
public:
    void *rva005B045D();
};
class AptCreateAHero
{
public:
	class Class;
};

class AptCreateAHero::Class {
    char m_pad0[4];
    char *m_outer04;
public:
    void ExternFunc(int sel, char *buf, bool flag);
};

void AptCreateAHero::Class::ExternFunc(int sel, char *buf, bool flag)
{
    if (!buf)
        return;
    if (flag)
        return;
    switch (sel) {
    case 1: {
        Rva005B045D *inner = (Rva005B045D *)(m_outer04 + 0x27C);
        void *p = inner->rva005B045D();
        int v = ((CreateAHeroManager *)TheCreateAHeroManager)->rva00219D52(*(unsigned int *)((char *)p + 0xC));
        _snprintf(buf, 0xFF, "%d", v);
        break;
    }
    case 0: {
        CreateAHeroManager *g = TheCreateAHeroManager;
        Vec32 *v = &g->m_outer;
        char *finish = (char *)v->m_finish;
        unsigned int count = (unsigned int)((finish - (char *)v->m_start) >> 5);
        _snprintf(buf, 0xFF, "%d", count);
        break;
    }
    default:
        break;
    }
}
