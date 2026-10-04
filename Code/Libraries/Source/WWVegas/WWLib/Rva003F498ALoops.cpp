// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003F498A@Rva003F498A@@QAEXPAVRva003F498ACallback@@@Z, retail 0x003F498A, 188 bytes.
// Triple-nested vector scan calling a virtual predicate on each int and
// returning early on false. Outer vector<Rva003F498AOuter 28B> at +0x18,
// middle vector<Rva003F498AInner 48B> at +4 of each outer, inner
// vector<int> at +4 of each middle. Sizes divide by 0x1C and 0x30 with
// push-const idiv and by 4 with sar 2. Callers 0x002B25EF 0x002B37FF
// 0x002B323C 0x003F4AD8 0x003F6A91 build 8-byte visitor structs with
// vtables 0x007FE000 0x007FDFF0 0x007FDFEC 0x00C37080 0x00C37064 and call
// here; slot 0 takes one int and returns bool in al. Flags and layout from
// neighbours stlport_asciistring_record_bodies.cpp and
// stlport_pod_vector_bodies.cpp with the same // cl:.
#include <vector>

class Rva003F498ACallback {
public:
    virtual bool invoke(int v) = 0;
};

struct Rva003F498AInner {
    int unk0;
    _STL::vector<int> vals;
    char pad16[12];
    int tail[5];
};

struct Rva003F498AOuter {
    int unk0;
    _STL::vector<Rva003F498AInner> inners;
    _STL::vector<int> ints;
    bool rva003F4342(Rva003F498ACallback *cb);
};

class Rva003F498A {
    char m_pad0[0x18];
    _STL::vector<Rva003F498AOuter> m_outers;
public:
    void rva003F498A(Rva003F498ACallback* cb);
    int rva003F46A8(int idx);
    int rva003F46C1(int outerIdx, int innerIdx);
    int* rva003F46F2(int outerIdx, int innerIdx);
    void rva003F470E(int outerIdx, int innerIdx, void *p);
    int rva003F48FE(int outerIdx, int middleIdx, int innerIdx);
    int rva003F4921(int outerIdx, int middleIdx, int innerIdx);
    bool rva003F486C(int id);
    bool rva003F48EF(void *p);
    int rva003F4752(void *p);
    int rva003F4798(int outerIdx, int id);
    int rva003F4FAA(int outerIdx, void *p);
    int rva003F47E6(int outerIdx);
    int rva003F4831();
    int rva003F45DF();
    bool rva003F4538();
    int rva003F458A(int idx);
    Rva003F498AOuter *rva003F4634(void *p);
    void *rva003F4DEE(void *p);
    void *rva003F4FBD(void *p);
    void rva003F4944(Rva003F498ACallback *cb);
};

struct Rva003F4CC0Inner;
class Rva003F4CC0 {
public:
    Rva003F4CC0Inner *rva003F4CC0(int id);
};

class Rva003F44A9 {
public:
    void *rva003F44A9();
};

void Rva003F498A::rva003F498A(Rva003F498ACallback* cb)
{
    for (unsigned i = 0; i < m_outers.size(); ++i) {
        Rva003F498AOuter& o = m_outers[i];
        for (unsigned j = 0; j < o.inners.size(); ++j) {
            Rva003F498AInner& in = o.inners[j];
            for (unsigned k = 0; k < in.vals.size(); ++k) {
                if (!cb->invoke(in.vals[k]))
                    return;
            }
        }
    }
}

int Rva003F498A::rva003F46A8(int idx)
{
    Rva003F498AOuter& o = m_outers[idx];
    return (int)o.ints.size();
}

int Rva003F498A::rva003F46C1(int outerIdx, int innerIdx)
{
    if (innerIdx < 0 || innerIdx >= rva003F46A8(outerIdx))
        return -1;
    return m_outers[outerIdx].ints[innerIdx];
}

int* Rva003F498A::rva003F46F2(int outerIdx, int innerIdx)
{
    return m_outers[outerIdx].inners[innerIdx].tail;
}

int Rva003F498A::rva003F48FE(int outerIdx, int middleIdx, int innerIdx)
{
    return m_outers[outerIdx].inners[middleIdx].vals[innerIdx];
}

int Rva003F498A::rva003F4921(int outerIdx, int middleIdx, int innerIdx)
{
    Rva003F498AOuter &o = m_outers[outerIdx];
    Rva003F498AInner &in = o.inners[middleIdx];
    int base = *(int *)((char *)&in + 0x10);
    return base + innerIdx * 0x68;
}

// ?rva003F486C@Rva003F498A@@QAE_NH@Z, retail 0x003F486C, 131 bytes.
// Unlock: scans outer/inner vectors for unk0-pointer object with ID at +0x14
// matching int arg via 0x1C/0x30 push-const idiv loops. Evidence: unlock lane,
// callers 0x00249BF3 0x003F354B 0x003F48F6 0x004EE0E5 0x004EE272 0x004FE057,
// wrapper 0x003F48EF pushes [arg+0x14], same file/sizes/flags as rva003F498A.
bool Rva003F498A::rva003F486C(int id)
{
    for (unsigned i = 0; i < m_outers.size(); ++i) {
        Rva003F498AOuter &o = m_outers[i];
        for (unsigned j = 0; j < o.inners.size(); ++j) {
            Rva003F498AInner &in = o.inners[j];
            void *obj = *(void **)&in;
            int cur = *(int *)((char *)obj + 0x14);
            if (cur == id)
                return true;
        }
    }
    return false;
}

// ?rva003F48EF@Rva003F498A@@QAE_NPAX@Z, retail 0x003F48EF, 15 bytes.
// Chain via 0x003F486C: pushes ID at arg+0x14 into rowed find. Evidence: chain
// lane, callers 0x0020E745 0x0020EC3E 0x0020FC8D 0x005766E8, same file/flags.
bool Rva003F498A::rva003F48EF(void *p)
{
    return rva003F486C(*(int *)((char *)p + 0x14));
}

// ?rva003F4752@Rva003F498A@@QAEHPAX@Z @0x003F4752 70B unlock linear search outers for unk0 matching arg+0x34 returning index else -1; callers 0x0023D996 0x0023D9E9 0x002BBD65 0x003F6D4B 0x0040CD64 0x0059809A 0x005E9A81; same file sizes flags as rva003F486C
int Rva003F498A::rva003F4752(void *p)
{
    for (unsigned i = 0; i < m_outers.size(); ++i) {
        if (m_outers[i].unk0 == *(int *)((char *)p + 0x34))
            return (int)i;
    }
    return -1;
}

// ?rva003F4798@Rva003F498A@@QAEHHH@Z @0x003F4798 78B unlock search one outer inners for unk0-obj id at +0x14 matching int arg returning index else -1; callers 0x003F4FB5 0x004EE0F6 0x004EE287; same file sizes flags as rva003F486C
int Rva003F498A::rva003F4798(int outerIdx, int id)
{
    Rva003F498AOuter &o = m_outers[outerIdx];
    for (unsigned i = 0; i < o.inners.size(); ++i) {
        Rva003F498AInner &in = o.inners[i];
        void *obj = *(void **)&in;
        if (*(int *)((char *)obj + 0x14) == id)
            return (int)i;
    }
    return -1;
}

// ?rva003F4FAA@Rva003F498A@@QAEHHPAX@Z @0x003F4FAA 19B chain wrapper pushing outerIdx and arg+0x14 into rowed 0x003F4798; callers 0x0023D9A6 0x002BBD74 0x003F6D9C 0x005980A5 0x005E9A8E; same file flags
int Rva003F498A::rva003F4FAA(int outerIdx, void *p)
{
    return rva003F4798(outerIdx, *(int *)((char *)p + 0x14));
}

// ?rva003F47E6@Rva003F498A@@QAEHH@Z @0x003F47E6 75B unlock count one outer inners where unk0-obj dword at +0x44 is zero; callers 0x002BB0E7 0x003F4859; same file sizes flags
int Rva003F498A::rva003F47E6(int outerIdx)
{
    Rva003F498AOuter &o = m_outers[outerIdx];
    int n = 0;
    for (unsigned i = 0; i < o.inners.size(); ++i) {
        Rva003F498AInner &in = o.inners[i];
        void *obj = *(void **)&in;
        if (*(int *)((char *)obj + 0x44) == 0)
            ++n;
    }
    return n;
}

// ?rva003F4831@Rva003F498A@@QAEHXZ @0x003F4831 59B chain sum over outers of rowed 0x003F47E6; callers 0x0020E4D9 0x0020E7A3 0x0020EC0D 0x003F517D; same file flags
int Rva003F498A::rva003F4831()
{
    int total = 0;
    int i = 0;
    if ((int)m_outers.size() > 0) {
        int n = (int)m_outers.size();
        do {
            total += rva003F47E6(i++);
        } while (i < n);
    }
    return total;
}

// ?rva003F4634@Rva003F498A@@QAEPAURva003F498AOuter@@PAX@Z @0x003F4634 84B unlock search outers for unk0 matching arg+0x34 returning element pointer else NULL; callers 0x003F4DF2 0x003F6740; same file sizes flags
Rva003F498AOuter *Rva003F498A::rva003F4634(void *p)
{
    for (unsigned i = 0; i < m_outers.size(); ++i) {
        if (m_outers[i].unk0 == *(int *)((char *)p + 0x34))
            return &m_outers[i];
    }
    return 0;
}

// ?rva003F4DEE@Rva003F498A@@QAEPAXPAX@Z @0x003F4DEE 25B chain find outer via rowed 0x003F4634 then tail-jmp to rowed 0x003F4CC0; callers 0x003F4FC1 0x003F5082 0x003F5BF6; same file flags
void *Rva003F498A::rva003F4DEE(void *p)
{
    Rva003F498AOuter *o = rva003F4634(p);
    return o ? ((Rva003F4CC0 *)o)->rva003F4CC0((int)p) : 0;
}

// ?rva003F4FBD@Rva003F498A@@QAEPAXPAX@Z @0x003F4FBD 23B chain via rowed 0x003F4DEE then rowed 0x003F44A9; callers 0x0020FC99 0x002410B5; same file flags
void *Rva003F498A::rva003F4FBD(void *p)
{
    void *q = rva003F4DEE(p);
    if (q)
        q = ((Rva003F44A9 *)q)->rva003F44A9();
    return q;
}

// ?rva003F4342@Rva003F498AOuter@@QAE_NPAVRva003F498ACallback@@@Z @0x003F4342 86B unlock scan inners invoking virtual predicate on unk0 returning false on first false else true; caller 0x003F4967; same file family flags
bool Rva003F498AOuter::rva003F4342(Rva003F498ACallback *cb)
{
    for (unsigned i = 0; i < inners.size(); ++i) {
        int v = inners[i].unk0;
        if (!cb->invoke(v))
            return false;
    }
    return true;
}

// ?rva003F4944@Rva003F498A@@QAEXPAVRva003F498ACallback@@@Z @0x003F4944 70B chain scan outers via rowed 0x003F4342 returning early on false; same file flags
void Rva003F498A::rva003F4944(Rva003F498ACallback *cb)
{
    for (unsigned i = 0; i < m_outers.size(); ++i) {
        if (!m_outers[i].rva003F4342(cb))
            return;
    }
}

class ScoreKeeper
{
public:
    int getTotalUnitsDestroyed();
private:
    char m_pad00[0x74];
    int m_74; // +0x74
    char m_pad78[0x5C];
    int m_D4; // +0xD4
};

// ?rva003F470E@Rva003F498A@@QAEXHHPAX@Z @0x003F470E 68B gap fill tail stats from ScoreKeeper total plus +0x74 +0xD4 plus 12345; callers 0x0023D9B7; same file sizes flags as rva003F46F2
void Rva003F498A::rva003F470E(int outerIdx, int innerIdx, void *p)
{
    ScoreKeeper *sk = (ScoreKeeper *)p;
    int *tail = m_outers[outerIdx].inners[innerIdx].tail;
    tail[3] = sk->getTotalUnitsDestroyed();
    tail[2] = *(int *)((char *)sk + 0x74);
    tail[1] = *(int *)((char *)sk + 0xD4);
    tail[4] = 12345;
}

// ?rva003F4538@Rva003F498A@@QAE_NXZ @0x003F4538 82B leaf true if two outers have non-empty inners via 0x1C/0x30 size loops same TU flags caller 0x002BDFB5
bool Rva003F498A::rva003F4538()
{
    bool found = false;
    for (unsigned i = 0; i < m_outers.size(); ++i) {
        if (m_outers[i].inners.size() > 0) {
            if (found)
                return true;
            found = true;
        }
    }
    return false;
}

// ?rva003F458A@Rva003F498A@@QAEHH@Z @0x003F458A 16B unlock outer unk0 getter via 0x1C imul same TU flags callers 0x002BAFDB 0x002BC222 gap between 0x003F4538 and 0x003F45DF
int Rva003F498A::rva003F458A(int idx)
{
    return m_outers[idx].unk0;
}

int Rva003F498A::rva003F45DF()
{
    for (unsigned i = 0; i < m_outers.size(); ++i) {
        if (m_outers[i].inners.size() > 0)
            return (int)i;
    }
    return 0;
}
