// cl: /O1 /Oy- /DNDEBUG /MD
// Native0047BE4C..0047BEC9 RET12: contain-interface iteration of the
// rider list at receiver+FC. Mask4 selects riders and mask8 selects reverse;
// the established base provider004635EC iterates its own list at+34.
// Receiver is SiegeEngineContain full-object+20: primary interface vtable
// 00C46F80 slot68 at00C47090 is0047BE4C; second table00C47834 slot85
// also uses this body. The full-object rider list is at11C.
// Reverse traversal matches the measured sibling0047BEC9; forward traversal
// advances before callbacks so removing the visited rider remains safe.
// ZH OpenContain::iterateContained is the callback/list semantic guide;
// target flag dispatch and base-call placement are measured differences.
// Native0047CEBB..0047CF38 RET12 is the same body over a rider list at
// receiver+108 (vtable slot RVA 00847438, between the SiegeEngineContain
// table and TunnelContain's 008475B8, beside the HordeSiegeEngineContain
// bodies at0047D0A2: a naming lead only).
class Object;
typedef void (__cdecl *ContainIterateFunc)(Object *, void *);
class SlaughterHordeContain {
public:
    virtual void rva004635EC(ContainIterateFunc, void *, int);
};
struct Rva0047BE4CNode {
    Rva0047BE4CNode *next;
    Rva0047BE4CNode *previous;
    Object *object;
};
class Rva0047BE4C {
public:
    void rva0047BE4C(ContainIterateFunc, void *, int);
    char unknown00[0xFC];
    Rva0047BE4CNode *riders;
};
class Rva0047CEBB {
public:
    void rva0047CEBB(ContainIterateFunc, void *, int);
    char unknown00[0x108];
    Rva0047BE4CNode *riders;
};
void Rva0047BE4C::rva0047BE4C(ContainIterateFunc func, void *userData, volatile int flags)
{
    // Native saves the original mask then writes it back into its argument
    // slot before the memory AND. Volatile preserves those observed writes.
    int originalFlags = flags;
    flags = originalFlags;
    flags &= 4;
    if (flags && (originalFlags & 8)) {
        Rva0047BE4CNode *current = riders;
        if (current != current->next) {
            do {
                current = current->previous;
                func(current->object, userData);
            } while (current != riders->next);
        }
    }
    ((SlaughterHordeContain *)this)->SlaughterHordeContain::rva004635EC(func, userData, originalFlags);
    if (flags && !(originalFlags & 8)) {
        Rva0047BE4CNode *current = riders->next;
        if (current != riders) {
            do {
                Object *object = current->object;
                current = current->next;
                func(object, userData);
            } while (current != riders);
        }
    }
}
void Rva0047CEBB::rva0047CEBB(ContainIterateFunc func, void *userData, volatile int flags)
{
    // Native saves the original mask then writes it back into its argument
    // slot before the memory AND. Volatile preserves those observed writes.
    int originalFlags = flags;
    flags = originalFlags;
    flags &= 4;
    if (flags && (originalFlags & 8)) {
        Rva0047BE4CNode *current = riders;
        if (current != current->next) {
            do {
                current = current->previous;
                func(current->object, userData);
            } while (current != riders->next);
        }
    }
    ((SlaughterHordeContain *)this)->SlaughterHordeContain::rva004635EC(func, userData, originalFlags);
    if (flags && !(originalFlags & 8)) {
        Rva0047BE4CNode *current = riders->next;
        if (current != riders) {
            do {
                Object *object = current->object;
                current = current->next;
                func(object, userData);
            } while (current != riders);
        }
    }
}
