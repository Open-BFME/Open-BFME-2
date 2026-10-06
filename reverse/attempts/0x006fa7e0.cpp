// ?rva006FA7E0@Rva006FB860@@QAEX_N0H@Z
// partial score=0.55 date=2026-10-06
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
    bool isUndefined() const; // rowed, 0x006DC010
    BfmeAptValue006DCD20 *rva006DCF60(bool bUndefOK); // rowed, checked CIH cast
};

class Rva006E1E30;
class Rva006F9FC0
{
public:
    bool rva006F9FC0(Rva006E1E30 *object, int unused);
};
class Rva006E2010Dispatcher
{
public:
    void dispatch(int eventMask, int value, int enabled);
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
    BfmeAptValue006DCD20 * volatile m64;
    BfmeAptValue006DCD20 *m68;
    BfmeAptValue006DCD20 *m6c;
    unsigned char m70;
    unsigned char _unread71[3];
    int m74;
    int m78;
    void rva006FB860(int value, char isFirst);
    void Rva006F9EF0();
    void rva006FB910();
    void rva006FA7E0(bool first, bool enabled, int value);
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

// Retail 0x006FA7E0 is a state transition on the same object view as
// 0x006FB860/0x006FB910. Its calls to 0x006F9FC0 use this object for the
// +0x74/+0x78 coordinate test; target 0x006FAA20 independently reads the
// adjacent +0x6C/+0x70 fields. The owner class is address-derived; the state
// fields and checked-cast/dispatch calls below are read from retail.
void Rva006FB860::rva006FA7E0(bool first, bool enabled, int value)
{
    if (enabled) {
        if (m60->isUndefined())
            return;
        if (!mValue->isUndefined()) {
            if (mValue == m60) {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x800, value, 1);
            } else {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x1000, value, 1);
            }
        } else {
            if (((Rva006F9FC0 *)this)->rva006F9FC0(
                    (Rva006E1E30 *)m60->rva006DCF60(false), value) && m68 == m60) {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x800, value, 1);
            } else {
                ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                    ->dispatch(0x1000, value, 1);
            }
        }
        m60 = *(BfmeAptValue006DCD20 **)0x00E18078;
        return;
    }

    if (first) {
        if (m68->isUndefined())
            return;
        ((Rva006E2010Dispatcher *)m68->rva006DCF60(false))
            ->dispatch(0x400, value, 1);
        m60 = m68;
        return;
    }

    if (!m60->isUndefined()) {
        bool inside = ((Rva006F9FC0 *)this)->rva006F9FC0(
            (Rva006E1E30 *)m60->rva006DCF60(false), value);
        if (!m64->isUndefined() && !inside) {
            ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                ->dispatch(0x10000, value, 1);
            m64 = *(BfmeAptValue006DCD20 **)0x00E18078;
            return;
        }
        if (m64->isUndefined() && inside) {
            ((Rva006E2010Dispatcher *)m60->rva006DCF60(false))
                ->dispatch(0x8000, value, 1);
            m64 = m60;
        }
    } else {
        if (!m68->isUndefined() && m68 != m64) {
            if (!m64->isUndefined() && m64 != m60) {
                ((Rva006E2010Dispatcher *)m64->rva006DCF60(false))
                    ->dispatch(0x4000, value, 1);
            }
            m64 = m68;
            ((Rva006E2010Dispatcher *)m68->rva006DCF60(false))
                ->dispatch(0x2000, value, 1);
        } else {
            if (m64->isUndefined() || m68 == m64 || !m60->isUndefined())
                return;
            if (((Rva006F9FC0 *)this)->rva006F9FC0(
                    (Rva006E1E30 *)m64->rva006DCF60(false), value))
                return;
            ((Rva006E2010Dispatcher *)m64->rva006DCF60(false))
                ->dispatch(0x4000, value, 1);
            m64 = *(BfmeAptValue006DCD20 **)0x00E18078;
            return;
        }
    }
}

typedef char PoolCountOffset[(sizeof(Rva006FB860) >= 0x44 + sizeof(BfmeAptValue006DCD20)) ? 1 : -1];
