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
// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class AsciiString { public: int compare(const AsciiString &) const; private: void *data; };
struct Rva002BA8F1Input {
    char at00[8]; AsciiString at08, at0C, at10;
    int at14, at18; char at1C[8]; bool at24;
};
class Rva002E18C3Lookup {
public: AsciiString *find(const AsciiString &);
private: char at00[0xc]; _STL::vector<AsciiString *> entries;
};
extern Rva002E18C3Lookup *Va00DFF0B0Lookup, *Va00E03140Lookup;
struct Rva002000D7Config { char at00[0x34]; int at34; };
class Rva002000D7Store { public: Rva002000D7Config *get(int); };
extern Rva002000D7Store *Va00DFE0ECStore;
struct Va00DFE78CState { char at00[0x114]; int at114; };
extern Va00DFE78CState *Va00DFE78CStatePointer;
struct Rva002BA8F1Slot { char at00[0x4c]; int at4C; };
struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); char opaque[12]; };
class Rva002E2903Player {
public:
    Rva002E2903Player(Rva002BA8F1Input *, void *);
    void setAt1C4(int);
    void setColor(int);
    void state0(); void state1(); void state2();
    void attach(void *);
    void initialize();
    char at00[4]; Rva005A0B4CList listeners; char at10[4]; int at14;
    char at18[8]; AsciiString name; char remaining[0x3c8-0x24];
};
typedef _STL::vector<Rva002E2903Player *> Rva002BA8F1PlayerList;
struct Rva002BA8F1Primary { char opaque[0x18]; };
class Rva002BA8F1Logic : public Rva002BA8F1Primary, public Rva002BA8F1Listener {
public:
    Rva002E2903Player *find(const AsciiString &, unsigned int *);
    void setLocal(Rva002E2903Player *);
    void addPlayer(Rva002BA8F1Input *, bool, int, Rva002BA8F1Slot *);
    char gap[0x8c-0x1c]; Rva002BA8F1PlayerList players;
};
void Rva002BA8F1Logic::addPlayer(Rva002BA8F1Input *input, bool local, int kind, Rva002BA8F1Slot *slot)
{
    if (find(input->at08, 0)) return;
    void *first = Va00DFF0B0Lookup->find(input->at0C);
    if (!first) return;
    void *second = 0;
    if (!input->at24) {
        second = Va00E03140Lookup->find(input->at10);
        if (!second) return;
    }
    Rva002E2903Player *player = new Rva002E2903Player(input, first);
    if (slot) slot->at4C = player->at14;
    Rva002000D7Config *config = Va00DFE0ECStore->get(1);
    if (config) player->setAt1C4(config->at34);
    player->setColor(input->at18);
    players.push_back(player);
    if (local) setLocal(player);
    if (input->at24) player->state2();
    else if (kind == 0) player->state0();
    else player->state1();
    if (second) player->attach(second);
    if (Va00DFE78CStatePointer->at114 != 3) player->initialize();
    player->listeners.append(this);
}

// Va00E03140Lookup: matched references place it at VA 0xe03140 (zero-filled .bss).
Rva002E18C3Lookup *Va00DFF0B0Lookup, * Va00E03140Lookup;
// ?Va00DFE0ECStore@@3PAVRva002000D7Store@@A: the global at VA 0xdfe0ec is ?TheRankInfoStore@@3PAVRankInfoStore@@A.
#pragma comment(linker, "/alternatename:?Va00DFE0ECStore@@3PAVRva002000D7Store@@A=?TheRankInfoStore@@3PAVRankInfoStore@@A")
// ?Va00DFE78CStatePointer@@3PAUVa00DFE78CState@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?Va00DFE78CStatePointer@@3PAUVa00DFE78CState@@A=?TheGameLogic@@3PAVGameLogic@@A")
