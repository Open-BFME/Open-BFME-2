// Retail RVA 0x002BA8F1, 332 bytes; Ghidra FUN_006ba8f1.
// Lead: withmorten/bfme12x-dll d44d7fca7854a7c81c17f6d273c4d585ab929c50,
// src/bfme2.cpp calls this LivingWorldLogic::AddPlayer. Both recorded CALL sites
// (VA 0x0092C65D / 0x0092C6F5) independently target this body in BFME2 1.06.
// That community method name/signature is a candidate, not an EA symbol.
// Original reconstruction from target instructions; no patch-DLL code imported.
// Target: lookup input strings at +8/+C/+10; allocate 0x3C8 bytes; construct;
// copy player+14 to slot+4C; append to owner+8C; select state via input+24
// and argument 3; register owner+18 in the player's +4 listener list.
// Names such as player/local/color are interpretations of the call relationships.
// The exact target-owned flags at +24/+44 are retained without enum-name claims.
// TU-local layout views; unnamed fields and address-qualified types are intentional.
// The bytecode proves offsets/operations, not original EA type names or full layouts.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// Match the game allocator profile of stlport_moduledatavector_push.cpp;
// the CRT allocator profile emitted a different player-vector growth body.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct Rva002BA8F1Input {
    char at00[8]; AsciiString at08, at0C, at10;
    int at14, at18; char at1C[8]; bool at24;
};
class Rva002E18C3Lookup {
public: AsciiString *find(const AsciiString &);
private: char at00[0xc]; _STL::vector<AsciiString *> entries;
};
extern Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore, *TheLivingWorldAITemplateStore;
struct Rva002000D7Config { char at00[0x34]; int at34; };
class Rva002000D7Store { public: Rva002000D7Config *get(int); };
extern class RankInfoStore *TheRankInfoStore;
struct Va00DFE78CState { char at00[0x114]; int at114; };
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva002BA8F1Slot { char at00[0x4c]; int at4C; };
struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); char opaque[12]; };
class Rva002E2903Player {
public:
    void setAt1C4(int);
    void state0(); void state1(); void state2();
    char at00[4]; Rva005A0B4CList listeners; char at10[4]; int at14;
    char at18[8]; AsciiString name; char remaining[0x3c8-0x24];
};
// Existing physical owner from LivingWorldPlayerDtor.cpp: native constructor
// 0x002E2903 initializes the native 0x3C8 allocation. This exposes only
// allocation size; field accesses retain the target-derived view above.
class Rva002E2AAE {
public:
    Rva002E2AAE(Rva002BA8F1Input *, void *);
    char storage[0x3c8];
};
class LivingWorldPlayer {
public:
    void SetColorIndex(int);       // native 0x002E0F91
    void InitBuildableHeroes();    // native 0x002E3518
};
class Rva002E0648Owner { public: void rva002E0648(void *); };
typedef _STL::vector<Rva002E2903Player *> Rva002BA8F1PlayerList;
struct Rva002BA8F1Primary { char opaque[0x18]; };
class Rva002BA8F1Logic : public Rva002BA8F1Primary, public Rva002BA8F1Listener {
public:
    Rva002E2903Player *find(const AsciiString &, unsigned int *);
    void setLocal(Rva002E2903Player *);
    char gap[0x8c-0x1c]; Rva002BA8F1PlayerList players;
};
// Name: WorldBuilder twin 0x00D8BB70 is LivingWorldLogic::AddPlayer (LivingWorldLogic.cpp,
// asserts 6210..6266), matched by call graph; it agrees with the bfme12x-dll lead above.
class LivingWorldLogic : public Rva002BA8F1Logic {
public:
    void AddPlayer(Rva002BA8F1Input *, bool, int, Rva002BA8F1Slot *);
};
void LivingWorldLogic::AddPlayer(Rva002BA8F1Input *input, bool local, int kind, Rva002BA8F1Slot *slot)
{
    if (find(input->at08, 0)) return;
    void *first = TheLivingWorldPlayerTemplateStore->find(input->at0C);
    if (!first) return;
    void *second = 0;
    if (!input->at24) {
        second = TheLivingWorldAITemplateStore->find(input->at10);
        if (!second) return;
    }
    Rva002E2903Player *player = (Rva002E2903Player *)new Rva002E2AAE(input, first);
    if (slot) slot->at4C = player->at14;
    Rva002000D7Config *config = (*(Rva002000D7Store **)&TheRankInfoStore)->get(1);
    if (config) player->setAt1C4(config->at34);
    ((LivingWorldPlayer *)player)->SetColorIndex(input->at18);
    players.push_back(player);
    if (local) setLocal(player);
    if (input->at24) player->state2();
    else if (kind == 0) player->state0();
    else player->state1();
    if (second) ((Rva002E0648Owner *)player)->rva002E0648(second);
    if (((Va00DFE78CState *)TheGameLogic)->at114 != 3) ((LivingWorldPlayer *)player)->InitBuildableHeroes();
    player->listeners.append(this);
}

// TheLivingWorldAITemplateStore: matched references place it at VA 0xe03140 (zero-filled .bss).
Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore, * TheLivingWorldAITemplateStore;
// ?Va00DFE78CStatePointer@@3PAUVa00DFE78CState@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
