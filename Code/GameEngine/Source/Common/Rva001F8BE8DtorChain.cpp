// cl: /O1 /MD /EHsc
// Nonvirtual destructor chain 001F8BE8 .. 001FBCDC (twelve 59B bodies).
// Every link has the BigChainBaseDtorsO1.cpp shape: the null-preserving
// this+4 conversion names a second base destroyed first then the first base
// pointer holder runs the verified 001F4206 cleanup. Second-base callees by
// REL32: 001F8BE8 -> pinned Rva005C67C0 dtor 001F8167; 001F9076 -> 001F8BE8;
// 001F9B69 -> 001F9076; 001FA5BB and 001FA5F6 -> 001F9B69; 001FAB1E ->
// 001FA5BB; 001FB829 -> 001FA5F6; 001FB98A -> 001FAB1E; 001FB9C5 -> 001FB829;
// 001FBB29 -> 001FB98A; 001FBB64 -> 001FB9C5; 001FBCDC -> 001FBB29; 001FBEB7 -> 001FBB64.
// Original game class names are unknown so address-derived Rva names are used.
class Rva001F4206
{
public:
    void rva001F4206();
};
class Rva001F8BE8Hold
{
public:
    void *m_pointer;
    ~Rva001F8BE8Hold();
};
// ??1Rva001F8BE8Hold@@QAE@XZ present-unmatched
inline Rva001F8BE8Hold::~Rva001F8BE8Hold()
{
    ((Rva001F4206 *)this)->rva001F4206();
}
class Rva005C67C0
{
public:
    ~Rva005C67C0();
};
class Rva001F8BE8 : public Rva001F8BE8Hold, public Rva005C67C0
{
public:
    ~Rva001F8BE8();
};
Rva001F8BE8::~Rva001F8BE8() {}
class Rva001F9076 : public Rva001F8BE8Hold, public Rva001F8BE8
{
public:
    ~Rva001F9076();
};
Rva001F9076::~Rva001F9076() {}
class Rva001F9B69 : public Rva001F8BE8Hold, public Rva001F9076
{
public:
    ~Rva001F9B69();
};
Rva001F9B69::~Rva001F9B69() {}
class Rva001FA5BB : public Rva001F8BE8Hold, public Rva001F9B69
{
public:
    ~Rva001FA5BB();
};
Rva001FA5BB::~Rva001FA5BB() {}
class Rva001FA5F6 : public Rva001F8BE8Hold, public Rva001F9B69
{
public:
    ~Rva001FA5F6();
};
Rva001FA5F6::~Rva001FA5F6() {}
class Rva001FAB1E : public Rva001F8BE8Hold, public Rva001FA5BB
{
public:
    ~Rva001FAB1E();
};
Rva001FAB1E::~Rva001FAB1E() {}
class Rva001FB829 : public Rva001F8BE8Hold, public Rva001FA5F6
{
public:
    ~Rva001FB829();
};
Rva001FB829::~Rva001FB829() {}
class Rva001FB98A : public Rva001F8BE8Hold, public Rva001FAB1E
{
public:
    ~Rva001FB98A();
};
Rva001FB98A::~Rva001FB98A() {}
class Rva001FB9C5 : public Rva001F8BE8Hold, public Rva001FB829
{
public:
    ~Rva001FB9C5();
};
Rva001FB9C5::~Rva001FB9C5() {}
class Rva001FBB29 : public Rva001F8BE8Hold, public Rva001FB98A
{
public:
    ~Rva001FBB29();
};
Rva001FBB29::~Rva001FBB29() {}
class Rva001FBB64 : public Rva001F8BE8Hold, public Rva001FB9C5
{
public:
    ~Rva001FBB64();
};
Rva001FBB64::~Rva001FBB64() {}
class Rva001FBCDC : public Rva001F8BE8Hold, public Rva001FBB29
{
public:
    ~Rva001FBCDC();
};
Rva001FBCDC::~Rva001FBCDC() {}
class Rva001FBEB7 : public Rva001F8BE8Hold, public Rva001FBB64
{
public:
    ~Rva001FBEB7();
};
Rva001FBEB7::~Rva001FBEB7() {}
