// cl: /MD
// ?Rva000E63DCDo@@YGXPAVRva000E63DCObj@@@Z retail 0x000E63DC 42B unlock lane.
// Evidence: vtable slot 3 of 0x007CEAB4 (class of ??0Rva000E6AC0@@QAE@XZ); two virtual calls
// on the single object arg (offsets 0x10 and 0x28); callers at 0x000E96CD and 0x000ED499.
// Shape: if (obj->check()) return; TwoBools t(1,1); obj->apply(&t). The two-argument
// constructor makes MSVC place the 2-byte temporary in the dead incoming arg slot at
// [ebp+8], which a plain member-by-member assignment does not (/O1 stack slot reuse).

struct TwoBools
{
    char a;
    char b;
    TwoBools(char x, char y) : a(x), b(y) {}
};

class Rva000E63DCObj
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual bool check();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void apply(TwoBools *p);
};

void __stdcall Rva000E63DCDo(Rva000E63DCObj *obj)
{
    if (obj->check())
        return;
    TwoBools t(1, 1);
    obj->apply(&t);
}
