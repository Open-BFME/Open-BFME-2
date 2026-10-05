// ?Rva006ED490Find@@YAPAXPAVBfmeAptValue006DCD20@@PAVEAStringC@@_N@Z
// partial score=0.99 date=2026-10-05
// ?Rva006ED490Find@@YAPAXPAVBfmeAptValue006DCD20@@PAVEAStringC@@_N@Z
// partial score=0.99 date=2026-09-30
// ?Rva006ED490Find@@YAPAXPAVBfmeAptValue006DCD20@@PAVEAStringC@@_N@Z
// partial score=0.99 date=2026-09-30
// cl: /O2 /DNDEBUG /MD /EHsc
// ?Rva006ED490Find@@YAPAXPAVBfmeAptValue006DCD20@@PAVEAStringC@@_N@Z @0x006ED490 231B. Apt CharacterInstance member lookup by EAStringC with parent walk.
// Evidence: calls rowed isCharacterInst, EAStringC::rva006D3510, BfmeAptValue::rva006DCF60; asserts "isCharacterInst()" with Apt file string; caller unclaimed.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class BfmeAptValue006DCD20;
class EAStringC;

class BfmeAptValue006DCD20 {
    char _0[0x48];
public:
    BfmeAptValue006DCD20 *m_parent; // +0x48
    void *m_outer; // +0x4C opaque, cast below
    int isCharacterInst() const;
    BfmeAptValue006DCD20 *rva006DCF60(bool bUndefOK);
};

class EAStringC {
public:
    bool rva006D3510(const char *text) const;
};

struct AptEntry8 {
    const char *name; // +0
    int index; // +4
};

struct AptEntry16 {
    int a; // +0
    const char *name; // +4
    int index; // +8
    int b; // +12
};

struct AptMid {
    char _0[4];
    void *m_tables; // +4, points to AptTablesBase
};

struct AptOuter {
    char _0[0xC];
    AptMid *m_mid; // +0xC
};

struct AptTables {
    char _0[0x18];
    void **m_lookup; // +0x18
    char _1c[0xC]; // +0x1C..0x27
    int m_count2; // +0x28
    AptEntry16 *m_arr2; // +0x2C
    int m_count1; // +0x30
    AptEntry8 *m_arr1; // +0x34
};

struct AptCharView {
    char _0[0x10];
    void **m_lookup; // +0x10
    char _14[0xC]; // +0x14..0x1F
    int m_count2; // +0x20
    AptEntry16 *m_arr2; // +0x24
    int m_count1; // +0x28
    AptEntry8 *m_arr1; // +0x2C
};

void *Rva006ED490Find(BfmeAptValue006DCD20 *v, EAStringC *s, bool flag)
{
    for (;;) {
        if (!static_cast<unsigned char>(v->isCharacterInst())) {
            g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0xA5);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __asm int 3
        }
        AptCharView *d = (AptCharView *)((char *)((AptOuter *)v->m_outer)->m_mid->m_tables + 8);
        for (int i = 0; i < d->m_count1; ++i) {
            if (s->rva006D3510(d->m_arr1[i].name)) {
                int idx = d->m_arr1[i].index;
                return d->m_lookup[idx];
            }
        }
        if (flag) {
            for (int i = 0; i < d->m_count2; ++i) {
                if (s->rva006D3510(d->m_arr2[i].name)) {
                    const int idx = d->m_arr2[i].index;
                    return d->m_lookup[idx];
                }
            }
        }
        BfmeAptValue006DCD20 *next = v->rva006DCF60(false)->m_parent;
        if (!next)
            return 0;
        flag = false;
        v = next;
    }
}
