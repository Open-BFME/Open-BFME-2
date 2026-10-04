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
    void rva006FB860(int value, char isFirst);
    void Rva006F9EF0();
    void rva006FB910();
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

typedef char PoolCountOffset[(sizeof(Rva006FB860) >= 0x44 + sizeof(BfmeAptValue006DCD20)) ? 1 : -1];