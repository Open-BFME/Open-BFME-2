// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?Rva005200C5Add@@YAXPAXW4ScienceType@@@Z @0x005200C5 47B
// Evidence: caller 0x00407FA0 pushes (esi=this, ebx=key); pod lookup 0x0040AAD5 row; isEmpty 0x00001E2F row; push_back 0x002E01C6 row; globals g_00E02F74 (ptr) g_00E04920 (vector)
#include "ascii_string.h"
#include <vector>

enum ScienceType { SCIENCE_FIRST = 0 };

struct BfmePod40;
class Rva0040AAD5 {
public:
    struct BfmePod40 *rva0040AAD5(int key);
};

extern class Rva0040AAD5 *g_00E02F74;
extern _STL::vector<ScienceType> g_00E04920;

void __cdecl Rva005200C5Add(void *unused, ScienceType s)
{
    struct BfmePod40 *e = g_00E02F74->rva0040AAD5((int)s);
    if (!e)
        return;
    const StringBase<char> *str = (const StringBase<char> *)((const char *)e + 0x10);
    if (str->isEmpty())
        return;
    g_00E04920.push_back(s);
}
