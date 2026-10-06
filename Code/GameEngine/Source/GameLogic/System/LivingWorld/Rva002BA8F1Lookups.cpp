// Retail RVA 0x002B6AEC (96 bytes) and 0x002E18C3 (65 bytes), Ghidra boundaries.
// Both are direct callees of the AddPlayer candidate at RVA 0x002BA8F1.
// The former searches vector +8C for an entry string at +20 and optionally
// writes its index. The latter searches vector +C for an entry string at +0.
// String identity/ABI is supported by their calls to the byte-verified
// StringBase<char>::compare at RVA 0x000069D6 (existing AsciiString alias).
// The collections' original class/element identities remain unproven.
// Declaration views match Rva002BA8F1AddPlayer.cpp; definitions stay separate
// to preserve the retail translation-unit call boundary.
// TU-local layout views; unnamed fields and address-qualified types are intentional.
// The bytecode proves offsets/operations, not original EA type names or full layouts.
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
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
    char at18[8]; AsciiString name;
    char pad24_44[0x44-0x24]; int m_44; // +0x44 dword-checked count gate
    char pad48_3C4[0x3C4-0x48]; bool m_3C4; // +0x3C4 byte-checked with flag OR
    char pad3C5_3C8[0x3C8-0x3C5];
};
typedef _STL::vector<Rva002E2903Player *> Rva002BA8F1PlayerList;
struct Rva002BA8F1Primary { char opaque[0x18]; };
class Rva002BA8F1Logic : public Rva002BA8F1Primary, public Rva002BA8F1Listener {
public:
    Rva002E2903Player *find(const AsciiString &, unsigned int *);
    Rva002E2903Player *find(int, unsigned int *);
    Rva002E2903Player *rva002B52A8(int);
    int rva002B5256(bool flag);
    void setLocal(Rva002E2903Player *);
    void addPlayer(Rva002BA8F1Input *, bool, int, Rva002BA8F1Slot *);
    char gap[0x8c-0x1c]; Rva002BA8F1PlayerList players;
};

Rva002E2903Player *Rva002BA8F1Logic::find(const AsciiString &name, unsigned int *index)
{
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->name.compare(name) == 0) {
            if (index) *index = i;
            return players[i];
        }
    }
    return 0;
}

AsciiString *Rva002E18C3Lookup::find(const AsciiString &name)
{
    for (unsigned int i = 0; i < entries.size(); ++i) {
        if (entries[i]->compare(name) == 0) return entries[i];
    }
    return 0;
}

// ?find@Rva002BA8F1Logic@@QAEPAVRva002E2903Player@@HPAI@Z @0x002B51F8 94B.
// Id lookup over the same +0x8C player vector as the string find above.
// Compares entry +0x14 against the id with -1 early-out and optional index out.
// Callers use the 0x00DFEF10 singleton and unblock 67 functions.
Rva002E2903Player *Rva002BA8F1Logic::find(int id, unsigned int *index)
{
    if (id == -1)
        return 0;
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->at14 == id) {
            if (index)
                *index = i;
            return players[i];
        }
    }
    return 0;
}

// ?rva002B52A8@Rva002BA8F1Logic@@QAEPAVRva002E2903Player@@H@Z @0x002B52A8 38B.
// Bounds-checked index into the same +0x8C player vector. Returns 0 on negative or past-end.
Rva002E2903Player *Rva002BA8F1Logic::rva002B52A8(int index)
{
    if (index < 0 || (unsigned int)index >= players.size())
        return 0;
    return players[index];
}

// ?rva002B5256@Rva002BA8F1Logic@@QAEH_N@Z @0x002B5256 82B.
// Gap between find 0x002B51F8 and rva002B52A8 in same TU; counts +0x8C player
// vector entries with dword at +0x44 == 0 and (byte at +0x3C4 == 0 or flag).
// Evidence: (finish-start)>>2 count with je early-out plus esi/edi pointer-index
// loop matching find's id-vector shape; dword cmp at +0x44 then byte cmp at
// +0x3C4 then byte cmp of stack bool arg; ret 4 single bool arg returning int.
int Rva002BA8F1Logic::rva002B5256(bool flag)
{
    int count = 0;
    for (unsigned int i = 0; i < players.size(); ++i) {
        Rva002E2903Player *p = players[i];
        if (p->m_44 == 0 && (p->m_3C4 == 0 || flag))
            ++count;
    }
    return count;
}

// ?find@Rva002E1904Lookup@@QAEPAURva002E1904Entry@@ABVAsciiString@@@Z @0x002E1904 68B.
// Vector +0x0C lookup for an entry string at +4, same shape as Rva002E18C3Lookup
// find 0x002E18C3 (65B) plus the three-byte add ecx,4 for the +4 field.
// Evidence: unlock lane (unblocks 0x0052C45E); caller passes key by ref with
// ret 4; same sub-sar-2 count plus compare loop as sibling finds.
struct Rva002E1904Entry { int m_0; AsciiString m_4; };
class Rva002E1904Lookup {
public: Rva002E1904Entry *find(const AsciiString &);
private: char at00[0xc]; _STL::vector<Rva002E1904Entry *> entries;
};
Rva002E1904Entry *Rva002E1904Lookup::find(const AsciiString &name)
{
    for (unsigned int i = 0; i < entries.size(); ++i) {
        if (entries[i]->m_4.compare(name) == 0) return entries[i];
    }
    return 0;
}

// ?find@Rva002E1948Lookup@@QAEPAURva002E1948Entry@@ABVAsciiString@@@Z @0x002E1948 86B.
// Vector +0x1B8 lookup for an entry string at +0x1C, same sibling-find shape as
// 0x002E1904 (68B) with wider disp32 offsets. Evidence: unlock lane (unblocks
// 0x002B48E1); caller passes key by ref with ret 4; same file drains siblings.
struct Rva002E1948Entry { char m_0[0x1c]; AsciiString m_1c; };
class Rva002E1948Lookup {
public: Rva002E1948Entry *find(const AsciiString &);
private: char at00[0x1b8]; _STL::vector<Rva002E1948Entry *> entries;
};
Rva002E1948Entry *Rva002E1948Lookup::find(const AsciiString &name)
{
    for (unsigned int i = 0; i < entries.size(); ++i) {
        if (entries[i]->m_1c.compare(name) == 0) return entries[i];
    }
    return 0;
}
