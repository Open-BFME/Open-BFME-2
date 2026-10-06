// cl: /O2 /MD
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
struct Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class Rva006E3710
{
public:
    bool rva006E3710(Rva006E3710Node *node); // rowed, 0x006E3710
};
class AptCIH : public BfmeAptValue006DCD20
{
public:
    void *rva006E1090() const; // rowed, 0x006E1090
    void rva006E1F00(int value); // address-derived, 0x006E1F00
};

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
    void rva006FB860(int value, char isFirst);
    void Rva006F9EF0();
    void rva006FB910();
    void rva006FAA20();
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

typedef char PoolCountOffset[(sizeof(Rva006FB860) >= 0x44 + sizeof(BfmeAptValue006DCD20)) ? 1 : -1];
