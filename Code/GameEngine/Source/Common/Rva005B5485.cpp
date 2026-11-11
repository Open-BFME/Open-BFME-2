// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?ExternFunc@Class@AptCreateAHero@@QAEXHPAD_N@Z @0x005B5485 104B
// Snprintf "%d" of outer/inner vector counts guarded by buf and flag.
// Retail: xor edx cmp buf je cmp flag jne then sel 0/1 via sub/dec,
// path1 via 0x5B045D plus rowed 0x00219D52, path0 manual sar5, both to
// rowed _snprintf 0xff. Callers none; chain via 0x00219D52.
// Honest-address method on AptCreateAHero::Class with +4 outer pointer.
#include <stdio.h>
#include "ascii_string.h"
#include "unicode_string.h"
struct OuterElem32 { char m_00[32]; };
struct Vec32 { OuterElem32 *m_start; OuterElem32 *m_finish; OuterElem32 *m_end; };
class CreateAHeroManager {
    char m_pad[0x14C];
public:
    Vec32 m_outer;
    int rva00219D52(unsigned int o);
    const AsciiString &GetButtonImageName(unsigned, unsigned);
    const AsciiString &GetClassDescTag(unsigned);
    const AsciiString &GetSubClassDescTag(unsigned, unsigned);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva005B045D {
public:
    void *rva005B045D();
};
#include "../../Include/Common/AptCreateAHero.h"

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
        int vec32 = ((CreateAHeroManager *)TheCreateAHeroManager)->rva00219D52(*(unsigned int *)((char *)p + 0xC));
        _snprintf(buf, 0xFF, "%d", vec32);
        break;
    }
    case 0: {
        CreateAHeroManager *createAHeroManager = TheCreateAHeroManager;
        Vec32 *vec32 = &createAHeroManager->m_outer;
        char *finish = (char *)vec32->m_finish;
        unsigned int count = (unsigned int)((finish - (char *)vec32->m_start) >> 5);
        _snprintf(buf, 0xFF, "%d", count);
        break;
    }
    default:
        break;
    }
}
// Views for Rva005B566B::rva005B54ED below (shapes from the banked standalone
// trial; all callees rowed, no pins).
class CreateAHeroData;
#include "../../Include/GameClient/AptMyHero.h"
struct ClassScreenPrefix { char prefix[0x27C]; AptMyHero hero; };
class ModuleData;
#include "../../Include/Common/Rva00423A68.h"
#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../Include/Common/Rva005B566B.h"
