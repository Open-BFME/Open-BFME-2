// ?get@Rva002000D7Store@@QAEPAURva002000D7Config@@H@Z
// partial score=0.95 date=2026-10-05
// cl: /Os /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// ?get@Rva002000D7Store@@QAEPAURva002000D7Config@@H@Z @0x002000D7 52B
// RankInfoStore indexed getter with +4-chain final override.
// Evidence: callers 0x002AE29C 0x002BA995 0x0038021F 0x00380254 0x003802C0
// 0x003803DF 0x00380473 0x00380657 0x0040CA7F; callee dup 0x001E35DF via
// Overridable::getFinalOverride pin (row types void but body uses eax
// result per Rva00358333 precedent); bounds via +0xC begin/+0x10 end
// pointer difference; index v-1; +4 next; LINK BONUS 3 files 216B.
struct Rva002000D7Config
{
    void *m_pad00;
    void *m_next;
};

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
};

class Rva002000D7Store
{
public:
    Rva002000D7Config *get(int v);

private:
    char m_pad00[0x0C];
    int m_begin;
    int m_end;
};

Rva002000D7Config *Rva002000D7Store::get(int v)
{
    if (v < 1)
        return 0;
    int count = m_end;
    count -= m_begin;
    count >>= 2;
    if (v > count)
        return 0;
    Rva002000D7Config *entry = ((Rva002000D7Config **)m_begin)[v - 1];
    if (entry != 0) {
        void *next = entry->m_next;
        if (next == 0)
            return entry;
        return (Rva002000D7Config *)((const Overridable *)next)->getFinalOverride();
    }
    return 0;
}
