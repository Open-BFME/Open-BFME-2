// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// ?rva005801F6@Rva005801F6@@QAEXPAVRva005801F6Probe@@0@Z retail 0x005801F6
// (109 bytes, RET 8). Fills a vector of ints (begin +4, end +8) with the
// three-way presence comparison of two objects: for each slot the index is
// rotated by a start offset read at owner(+0)+0x18, both objects are asked
// through virtual slot 6 (+0x18) whether they hold an entry for that index,
// and the result is 0 when both agree, otherwise 1 for the first holder and
// -1 for the second. Identity of the owner and probe types is unproven; the
// method name is a placeholder for the address. Codegen: the index and the
// first presence bit live in one 8-byte local (retail's [ebp-8]/[ebp-4]
// pair); separate scalars pack the bool at [ebp-1].
class Rva005801F6Probe
{
public:
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void *find(int index);
};

struct Rva005801F6Owner
{
    char m_pad[0x18];
    int m_start;
};

class Rva005801F6
{
public:
    void rva005801F6(Rva005801F6Probe *first, Rva005801F6Probe *second);
private:
    Rva005801F6Owner *m_owner;
    int *m_begin;
    int *m_end;
};

void Rva005801F6::rva005801F6(Rva005801F6Probe *first, Rva005801F6Probe *second)
{
    int count = m_end - m_begin;
    for (int i = 0; i < count; ++i)
    {
        struct { int index; bool hasSecond; } t;
        t.index = (m_owner->m_start + i) % count;
        t.hasSecond = second->find(t.index) != 0;
        bool hasFirst = first->find(t.index) != 0;
        m_begin[i] = hasFirst != t.hasSecond ? (hasFirst ? 1 : -1) : 0;
    }
}
