// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Ghidra 46E6EA..46E740 RET16. Original receiver and method identities
// remain unresolved. Target establishes embedded interface+11C/vslot238 and
// input definition+4/flags11F. Callee46B05B reads input position floats;
// fallback2EF3EE uses the third coordinate pointer and returns AL.
class AI;
extern AI *TheAI;
struct Rva0046E6EACoord { float x, y, z; };
struct Rva0046E6EADefinition { char unknown[0x11f]; unsigned char flags; };
struct Rva0046E6EAObject { void *unknown; Rva0046E6EADefinition *definition; };
class Rva002EF3EEView {
public:
    bool rva002EF3EE(Rva0046E6EAObject *, const Rva0046E6EACoord *, Rva0046E6EACoord *, bool);
};
class Rva0046E6EAAIView {
    char unknown[0x10];
    Rva002EF3EEView *finder;
public:
    Rva002EF3EEView *pathfinder() { return finder; }
};
#define SLOT(N) virtual void reserved##N();
#define SLOT8(A,B,C,D,E,F,G,H) SLOT(A) SLOT(B) SLOT(C) SLOT(D) SLOT(E) SLOT(F) SLOT(G) SLOT(H)
class Rva0046E6EAInterface {
public:
    SLOT8(0,1,2,3,4,5,6,7)
    SLOT8(8,9,10,11,12,13,14,15)
    SLOT8(16,17,18,19,20,21,22,23)
    SLOT8(24,25,26,27,28,29,30,31)
    SLOT8(32,33,34,35,36,37,38,39)
    SLOT8(40,41,42,43,44,45,46,47)
    SLOT8(48,49,50,51,52,53,54,55)
    SLOT8(56,57,58,59,60,61,62,63)
    SLOT8(64,65,66,67,68,69,70,71)
    SLOT8(72,73,74,75,76,77,78,79)
    SLOT8(80,81,82,83,84,85,86,87)
    SLOT8(88,89,90,91,92,93,94,95)
    SLOT8(96,97,98,99,100,101,102,103)
    SLOT8(104,105,106,107,108,109,110,111)
    SLOT8(112,113,114,115,116,117,118,119)
    SLOT8(120,121,122,123,124,125,126,127)
    SLOT8(128,129,130,131,132,133,134,135)
    SLOT(136) SLOT(137) SLOT(138) SLOT(139) SLOT(140) SLOT(141)
    virtual bool query238();
};
#undef SLOT8
#undef SLOT
class Rva0046E6EA {
public:
    bool rva0046E6EA(Rva0046E6EAObject *, const Rva0046E6EACoord *, Rva0046E6EACoord *, bool);
    void rva0046B05B(Rva0046E6EAObject *, const Rva0046E6EACoord *, Rva0046E6EACoord *);
private:
    char unknown[0x11c];
    Rva0046E6EAInterface interface;
};
bool Rva0046E6EA::rva0046E6EA(Rva0046E6EAObject *object,
    const Rva0046E6EACoord *position, Rva0046E6EACoord *out, bool flag)
{
    if (interface.query238() && (object->definition->flags & 1)) {
        rva0046B05B(object, position, out);
        return true;
    }
    return reinterpret_cast<Rva0046E6EAAIView *>(TheAI)->pathfinder()->rva002EF3EE(object, position, out, flag);
}
