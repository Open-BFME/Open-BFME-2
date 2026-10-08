// cl: /MD
// ?rva006FB910@Rva006FB860@@QAEAAXXZ @0x006FB910 70B.
//
// A member of the Apt object reached through the global at VA 0x00E176D0, the
// same pool pointer Rva006CC950Mouse.cpp and Rva006CD2A0Cluster.cpp establish.
// It is vtable-referenced: no direct caller in .text reaches 0x006FB910, the
// sibling 0x006FB860 or the callee 0x006F9EF0.
//
// Retail body, decoded from game.dat:
//   esi = this;
//   if (!((AptValue *)this + 0x44)->isUndefined())   // 0x006DC010, rowed
//       Rva006F9EF0(this);                           // 0x006F9EF0, unnamed
//   for (i = 0; i < this->mListCount; ++i)            // +0x3C
//       Rva006FB860(this, this->aList[i], i == 0);   // +0x40, dword elements
//   this->mListCount = 0;
//
// The +0x3C count / +0x40 element-list / +0x44 AptValue triple is read here
// directly and is a different block from the BIL count/list pair at
// +0x10/+0x14 modelled in AptAnimationPoolDataBIL.cpp, although both sit in
// the object behind the one global.
//
// 0x006FB860 is a `ret 8` thiscall taking (this, int value, int isFirst), which
// fixes the two right-to-left pushes and the `sete al` predicate for i == 0.
// Its own body unpacks a packed coordinate pair into this+0x74/+0x78 through
// the same 0x00E176D0 global, tying both members to one object; it is declared
// here and not defined, so this TU reproduces the call only.

class BfmeAptValue006DCD20
{
public:
    virtual void vtableSlot0();
    virtual void vtableSlot1();
    bool isUndefined() const; // rowed, 0x006DC010
};

struct Rva006E3710Node;
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class Rva006E3710
{
public:
    bool rva006E3710(Rva006E3710Node *node); // rowed, 0x006E3710
};
class AptCIH : public BfmeAptValue006DCD20
{
public:
    bool rva006CFCD0() const; // rowed predicate, 0x006CFCD0
    void *rva006E1090() const; // rowed, 0x006E1090
    void rva006E1F00(int value); // address-derived, 0x006E1F00
};
extern AptCIH *__cdecl rva006F99D0(int eventCode, AptCIH *first,
                                   AptCIH *second);

// The object these members share. Only the fields the 0x006FB910 body reads
// are modelled; the full layout is not claimed.
class Rva006FB860
{
public:
    unsigned char _unread[0x3C];
    int mListCount;                   // +0x3C
    int *aList;                       // +0x40, dword elements
    BfmeAptValue006DCD20 *mValue;     // +0x44, a pointer the body calls through
    unsigned char _unread48[0x18];
    BfmeAptValue006DCD20 *m60;
    BfmeAptValue006DCD20 *m64;
    BfmeAptValue006DCD20 *m68;
    AptCIH *m6c;
    unsigned char m70;
    unsigned char _unread71[3];
    int m74;
    int m78;
    AptCIH *rva006FA420(int x, int y); // address-derived, 0x006FA420
    void rva006FA100(AptCIH *value, int mode); // address-derived, 0x006FA100
    void rva006FA340(); // address-derived call target from this object view
    void rva006FB860(int value, char isFirst);
    void rva006FB120(int x, int y, int packed, int field, char isFirst);
    void rva006FB5B0(int x, int y, int packed, int field);
    bool rva006FACA0(int x, int y, void **candidate);
    void Rva006F9EF0();
    void rva006FB910();
    void rva006FAA20();
    void rva006FAF80(AptCIH *candidate, int eventCode, int transition);
};

// 0x006F9EF0 is an unnamed sibling of the same class, called thiscall on
// `this` (retail moves ecx from esi and leaves no stack cleanup). It reads
// this+0x44..0x5C and this+0x74/+0x78 against the -9999.0f sentinel 0xC61C3C00;
// its own body is banked blocked in reverse/re_attempts.log on the unrowed
// 0x006DCF60 and 0x006E0930. Declared above as a member, not defined here.

void Rva006FB860::rva006FB910()
{
    if (!mValue->isUndefined())
        Rva006F9EF0();
    for (int i = 0; i < mListCount; ++i)
        rva006FB860(aList[i], i == 0);
    mListCount = 0;
}

// Retail 0x006FAA20 shares +0x74/+0x78 and this with 0x006FB860; its direct
// reads establish +0x6C as an AptCIH pointer and +0x70 as a byte selector.
// Calls to 0x006FA420, 0x006E1F00 and 0x006FA100 remain address-based because
// their target bodies are unlanded; their addresses and ABIs come from these
// retail call sites. The owning class name remains address-derived.
void Rva006FB860::rva006FAA20()
{
    AptCIH *value = rva006FA420(m74, m78);
    Rva006E3710 *pool = (Rva006E3710 *)g_bfmeAptPtrAtE176D0;
    if (pool->rva006E3710((Rva006E3710Node *)value))
        value = 0;
    else if (value)
        value->vtableSlot0();

    if (m70) {
        if (m6c && !m6c->isUndefined()) {
            if (value != m6c) {
                if (*(int *)((char *)m6c->rva006E1090() + 0x18) == 4) {
                    m6c->rva006E1F00(2);
                    rva006FA100(m6c, 0x10);
                }
            } else if (*(int *)((char *)m6c->rva006E1090() + 0x18) == 2) {
                m6c->rva006E1F00(4);
                rva006FA100(m6c, 0x20);
            }
        } else if (value && !value->isUndefined()) {
            rva006FA100(value, 0x20);
        }
    } else if (value != m6c) {
        if (m6c && !m6c->isUndefined()) {
            m6c->rva006E1F00(1);
            rva006FA100(m6c, 2);
        }
        if (m6c)
            m6c->vtableSlot1();
        m6c = value;
        if (value) {
            value->vtableSlot0();
            if (!value->isUndefined()) {
                m6c->rva006E1F00(2);
                rva006FA100(value, 1);
            }
        }
    }

    if (value)
        value->vtableSlot1();
}

// ?rva006FAF80@Rva006FB860@@QAEXPAVAptCIH@@HH@Z @0x006FAF80 386B.
// Retail bytes establish ECX=this, three 32-bit stack arguments (ret 0xC),
// a 0..15 state dispatch, and reads/writes of this+0x6C/+0x70. The candidate
// argument is tested by the rowed AptCIH predicate at 0x006CFCD0. Ownership by
// Rva006FB860 is inferred from the same fields and direct sibling calls; the
// original method name and caller-level semantic labels remain unknown.
void Rva006FB860::rva006FAF80(AptCIH *candidate, int eventCode,
                              int transition)
{
    switch (eventCode) {
    case 1:
    case 2:
    case 14:
    case 15:
        if (m70 || transition)
            return;
        rva006FA340();
        if (!m6c)
            return;
        if (!candidate) {
            candidate = rva006F99D0(
                eventCode, *(AptCIH **)((char *)m6c + 0x48), m6c);
        } else if (candidate->rva006CFCD0()) {
            candidate = rva006F99D0(eventCode, candidate, 0);
        }
        if (!candidate)
            return;

        m6c->rva006E1F00(1);
        candidate->rva006E1F00(2);
        rva006FA100(m6c, 2);
        rva006FA100(candidate, 1);
        if (m6c)
            m6c->vtableSlot1();
        m6c = candidate;
        candidate->vtableSlot0();
        return;

    case 0:
        if (!m6c) {
            m70 = transition != 1;
            return;
        }

        if (!m70 && !transition) {
            m70 = 1;
            m6c->rva006E1F00(4);
            rva006FA100(m6c, 4);
        }
        if (!m70 || transition != 1)
            return;

        m70 = 0;
        if (*(int *)((char *)m6c->rva006E1090() + 0x18) == 2) {
            m6c->rva006E1F00(1);
            rva006FA100(m6c, 0x40);
            if (!m6c)
                return;
            m6c->rva006E1F00(2);
            if ((void *)mValue == *(void **)((char *)m6c + 0x48))
                rva006FA100(m6c, 8);
            else
                rva006FA100(m6c, 1);
            return;
        }
        m6c->rva006E1F00(2);
        rva006FA100(m6c, 8);
        return;
    }
}

// ?rva006FB860@Rva006FB860@@QAEXHD@Z @0x006FB860 173B.
// The target uses thiscall with two stack arguments (ret 8). When the packed
// value is four-aligned it updates the global Apt coordinates at +0x74/+0x78;
// otherwise it extracts three bit fields. Both paths feed two direct helper
// calls, then a local AptCIH output slot passed to 0x006FACA0; a false result
// forwards that value and the extracted coordinates to 0x006FAF80.
void Rva006FB860::rva006FB860(int value, char isFirst)
{
    void *candidate = 0;
    unsigned int packed = (unsigned int)value;
    int x;
    int y;
    int field;
    if ((packed & 3) == 0) {
        *(int *)((char *)g_bfmeAptPtrAtE176D0 + 0x74) = packed >> 17;
        unsigned int yValue = (packed >> 2) & 0x7FFF;
        x = 0xC8;
        y = 5;
        field = 1;
        *(int *)((char *)g_bfmeAptPtrAtE176D0 + 0x78) = yValue;
    } else {
        x = packed >> 17;
        y = (packed >> 10) & 0x7F;
        field = (packed >> 2) & 0xFF;
    }

    rva006FB120(x, y, value, field, isFirst);
    rva006FB5B0(x, y, value, field);
    if (!rva006FACA0(x, y, &candidate))
        rva006FAF80((AptCIH *)candidate, x, y);
}

typedef char PoolCountOffset[(sizeof(Rva006FB860) >= 0x44 + sizeof(BfmeAptValue006DCD20)) ? 1 : -1];
