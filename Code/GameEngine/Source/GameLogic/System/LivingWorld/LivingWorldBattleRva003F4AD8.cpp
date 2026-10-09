// cl: /O1  /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE
// stlport
// LivingWorldBattle traversal family. Existing battle rows establish vector
// sides18, 28B side records, 48B inner records, and the predicate ABI.
// The callback's native vtableC37064 independently points to3F5BBB at slot0
// and the already-rowed scalar deleting dtor3F4261 at slot1. Its existing
// address-derived destructor ownerRva005FED52 is retained and reconciled.
// Original method/callback names are unresolved; all offsets are target facts.
#include <vector>
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
class Rva003F498ACallback { public: virtual bool invoke(int) = 0; };
class LivingWorldBattle;
class Rva005FED52 : public Rva003F498ACallback {
public:
    explicit Rva005FED52(LivingWorldBattle *battle) : owner(battle) {}
    virtual bool invoke(int);
    virtual ~Rva005FED52();
private:
    LivingWorldBattle *owner;
};
bool Rva005FED52::invoke(int entry) {
    Rva002BA8F1Listener *listener = owner ? reinterpret_cast<Rva002BA8F1Listener *>(reinterpret_cast<char *>(owner)+4) : 0;
    reinterpret_cast<Rva005A0B4CList *>(entry+8)->append(listener);
    return true;
}
struct Rva003F42F7Element {
    virtual void slot0();
    virtual void slot1();
    char opaque04[100];
};
struct Rva003F498AInner {
    int opaque00;
    _STL::vector<int> values;
    _STL::vector<Rva003F42F7Element> units;
    char opaque1c[20];
    void rva003F42F7();
};
struct Rva003F498AOuter {
    int opaque00;
    _STL::vector<Rva003F498AInner> inner;
    _STL::vector<int> values;
    void rva003F4398();
};
class Rva003F43D3 { public: void rva003F43D3(); };
class LivingWorldBattle {
    char prefix[0x18];
    _STL::vector<Rva003F498AOuter> sides;
    char opaque24[0x14];
    int state38;
public:
    void rva003F498A(Rva003F498ACallback *);
};
void Rva003F498AOuter::rva003F4398() {
    for (unsigned i=0; i<inner.size(); ++i) { Rva003F498AInner *element=&inner[i]; element->rva003F42F7(); }
}

void Rva003F498AInner::rva003F42F7() {
    for (unsigned i=0; i<units.size(); ++i) { Rva003F42F7Element *e=&units[i]; e->slot1(); }
}
