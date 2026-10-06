// cl: /MD
// ?rva00222BCD@Rva00222A8BTarget@@QAEHPAXPBDH10000@Z @0x00222BCD 69B
// Forward 8 args to invoke then fire slot 0x28 once when +0x312 is 0.
// Evidence: invoke pin 0x00222A8B plus +0x312 +0x328 in Rva00222A53 TU range plus caller 0x00528C25; same class as prev Rva00222A53.
class Rva00222A8BTarget
{
public:
    int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    int rva00222BCD(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
    int rva00222C12(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
private:
    char m_pad00[0x312 - 4];
    unsigned char m_312;
    char m_pad01[0x328 - 0x313];
    unsigned char m_328;
};
int Rva00222A8BTarget::rva00222BCD(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7)
{
    int r = invoke(owner, name, flag, value, a4, a5, a6, a7);
    if (!m_312) {
        m_328 = 1;
        v10();
    }
    return r;
}
// ?rva00222C12@Rva00222A8BTarget@@QAEHPAXPBD1H10000@Z @0x00222C12 72B
// Forward 9 args to Rva00222B19AptCall then fire slot 0x28 once when +0x312 is 0.
// Evidence: calls rowed 0x00222B19, same +0x312 +0x328 and v10 as rva00222BCD above.
int __stdcall Rva00222B19AptCall(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
int Rva00222A8BTarget::rva00222C12(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4)
{
    int r = Rva00222B19AptCall(level, prefix, function, argc, a0, a1, a2, a3, a4);
    if (!m_312) {
        m_328 = 1;
        v10();
    }
    return r;
}
