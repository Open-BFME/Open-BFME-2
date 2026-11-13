// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native5EB955..5EB9D6, RET12: initialize the output, look up an int-keyed
// participant identifier, split it into side/player indices, and format the
// participant's opaque RGB colour. WB ExternPlayerColor supplies a name lead;
// the receiver's complete identity/layout remains unresolved.
// Target accesses prove battle+C, map+38, identifier divisor10000 and RGB+184.
// Existing matched providers supply all three non-library call identities.
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

extern "C" char *__cdecl _mbscpy(char *, const char *);

#include "../../../../Libraries/Include/Lib/RGBColor.h"
#include "../../../Include/GameLogic/LivingWorldBattle.h"
#include "../../../Include/Common/Rva003F468D.h"

class Rva005EB955 {
public:
    void rva005EB955(int index, char *result, bool disabled);
private:
    char unknown00[0xC];
    LivingWorldBattle *battle;
    char unknown10[0x28];
    _STL::map<int, int> participants;
};

void Rva005EB955::rva005EB955(int index, char *result, bool disabled)
{
    _mbscpy(result, "0");
    if (!disabled && battle && index < battle->rva003F459A()) {
        _STL::map<int, int>::iterator found = participants.find(index);
        if (found != participants.end()) {
            int id = found->second;
            int player = reinterpret_cast<Rva003F468D *>(battle)->rva003F468D(id / 10000, id % 10000);
            int color = reinterpret_cast<RGBColor *>(player + 0x184)->getAsInt() | 0xFF000000;
            _snprintf(result, 0xFF, "%d", color);
        }
    }
}

// Native5EC017..5EC09B (132B RET4), WB15E9430 Show. Preserve the
// established owning-wrapper names from its recovered constructor/caller.
// The worker's input is an opaque battle pointer: target5EBDBF stores it
// at+0C and dereferences it. The accessed implementation prefix is owned
// by Rva005EB8D6 (constructor5EB9F2 and destructor5EB8D6).
#include "../../../Include/Common/Rva002B254F.h"
#include "../../../../Libraries/Source/Apt/AptPlayerClass.h"
class Rva00222A8BTarget;
void Rva00516F21Invoke(Rva00222A8BTarget *, void *, const char *, const char *);
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005EB8D6
{
public:
    bool SetCurrentBattle(void *battle);
    void *owner;
    int level;
    int state;
};
#include "../../../Include/Common/Rva005EBC74.h"

bool Rva005EBC74::rva005EC017(void *battle)
{
    if (!g_bfmeAptWindowManager)
        return false;
    if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
        return false;
    if (!m_ptr->SetCurrentBattle(battle))
        return false;
    switch (m_ptr->state) {
    case 0:
        ((AptPlayer *)g_bfmeAptWindowManager)->ShowLevel(m_ptr->level);
        m_ptr->state = 1;
        break;
    case 3:
    case 4:
        Rva00516F21Invoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,
            (void *)m_ptr->level, "SetState", "_fadeIn");
        m_ptr->state = 2;
        break;
    }
    return true;
}
