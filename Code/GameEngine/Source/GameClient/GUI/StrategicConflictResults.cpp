// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native5EB955..5EB9D6, RET12: initialize the output, look up an int-keyed
// participant identifier, split it into side/player indices, and format the
// participant's opaque RGB colour. WB ExternPlayerColor supplies a name lead;
// the receiver's complete identity/layout remains unresolved.
// Target accesses prove battle+C, map+38, identifier divisor10000 and RGB+184.
// Existing matched providers supply all three non-library call identities.
#include <map>

extern "C" char *__cdecl _mbscpy(char *, const char *);

struct RGBColor { int getAsInt() const; float red, green, blue; };
class LivingWorldBattle { public: int rva003F459A(); };
class Rva003F468D { public: int rva003F468D(int, int); };

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
class Rva002B254F { public: int rva002B254F(); };
class Rva002224FE { public: bool rva002224FE(int); };
class Rva00222A8BTarget;
void Rva00516F21Invoke(Rva00222A8BTarget *, void *, const char *, const char *);
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005EB8D6
{
public:
    bool rva005EBDBF(void *battle);
    void *owner;
    int level;
    int state;
};
class Rva005EBC74
{
public:
    bool rva005EC017(void *battle);
private:
    Rva005EB8D6 *m_impl;
};

bool Rva005EBC74::rva005EC017(void *battle)
{
    if (!g_bfmeAptWindowManager)
        return false;
    if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
        return false;
    if (!m_impl->rva005EBDBF(battle))
        return false;
    switch (m_impl->state) {
    case 0:
        ((Rva002224FE *)g_bfmeAptWindowManager)->rva002224FE(m_impl->level);
        m_impl->state = 1;
        break;
    case 3:
    case 4:
        Rva00516F21Invoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,
            (void *)m_impl->level, "SetState", "_fadeIn");
        m_impl->state = 2;
        break;
    }
    return true;
}
