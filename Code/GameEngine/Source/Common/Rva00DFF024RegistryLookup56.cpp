// cl: /MD
//
// ?lookup56@Rva00DFF024Registry@@QAEPAXHH@Z
// RVA 0x002D2371 size 48. Pinned fallback lookup; tries (a 5) then (a 6) when
// b is -1 else (a b). Evidence: pin name; callers at 0x22329A (unclaimed) and
// 0x3163DA in parseWinClass; callee lookup at 0x2D225F via pin; neighbours in
// GameEngineDeletingBaseDerived.cpp share /O1 /MD.

class Rva00DFF024Registry
{
public:
    void *lookup(int a, int b);
    void *lookup56(int a, int b);
    void *lookup34(int a, int b);
};

void *Rva00DFF024Registry::lookup56(int a, int b)
{
    if (b == -1) {
        void *r = lookup(a, 5);
        if (r)
            return r;
        return lookup(a, 6);
    }
    return lookup(a, b);
}

void *Rva00DFF024Registry::lookup34(int a, int b)
{
    if (b == -1) {
        void *r = lookup(a, 3);
        if (r)
            return r;
        return lookup(a, 4);
    }
    return lookup(a, b);
}
