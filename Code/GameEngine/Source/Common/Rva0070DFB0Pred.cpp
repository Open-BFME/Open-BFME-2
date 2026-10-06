// cl: /MD
// ?rva0070DFB0@Rva006D6470Owner@@UAEHPAXPAURva008A4570Owner@@@Z @0x0070DFB0 29B
// Evidence: vslot slot 7 (0x1C) of 0x008EA264 and others; calls rowed nameEquals
// with "registerClass"; global at 0x00E18064 masked via neg/sbb/and; ret 8
// (this dead + 2 stack args, uses arg2); caller 0x006FE41F passes same ebx/edi.
extern "C" int __cdecl strcmp(const char *, const char *);
struct Rva008A4570Owner {
    void *m_data;
    bool nameEquals(const char *text);
};

extern int g_00E18064;
// g_00E18064: matched references place it at VA 0xe18064 (zero-filled .bss).
int g_00E18064;

class Rva006D6470Owner {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
public:
    virtual int rva0070DFB0(void *a1, Rva008A4570Owner *a2);
};

int Rva006D6470Owner::rva0070DFB0(void *a1, Rva008A4570Owner *a2)
{
    (void)a1;
    return a2->nameEquals("registerClass") ? g_00E18064 : 0;
}
