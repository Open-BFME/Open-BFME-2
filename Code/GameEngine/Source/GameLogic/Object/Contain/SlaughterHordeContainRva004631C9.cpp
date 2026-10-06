// cl: /DNDEBUG /MD
// ?rva004631C9@SlaughterHordeContain@@UAEXXZ, retail 0x004631C9 49B.
// SlaughterHordeContain vtable 0x00848AA0 slot 105: fetch pair via slot 70
// (0x118) then walk list at +4 calling Object::rva0029A12B on node+8.
// Same pair/list pattern as sibling rva004631FA; slot identities from packet
// vtable line; callee pin rowed.
struct Rva0046247DPair { void *m00; void *m04; };
class Object { public: void rva0029A12B(); };
struct Rva004631C9Node { void *mNext; int mPad04; Object *mObj; };
class SlaughterHordeContain {
public:
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59();
    virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67();
    virtual void d68(); virtual void d69();
    virtual void d70(Rva0046247DPair &p);
    virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74();
    virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78();
    virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82();
    virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86();
    virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90();
    virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94();
    virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98();
    virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102();
    virtual void d103(); virtual void d104();
    virtual void rva004631C9();
};
void SlaughterHordeContain::rva004631C9()
{
    Rva0046247DPair p;
    d70(p);
    Rva004631C9Node *cur = *(Rva004631C9Node * *)*(void * *)p.m04;
    for (; cur != *(Rva004631C9Node * *)p.m04; cur = *(Rva004631C9Node * *)cur)
        cur->mObj->rva0029A12B();
}
