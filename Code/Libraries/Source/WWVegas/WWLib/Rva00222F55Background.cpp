// cl: /O1 /MD
// ?rva00222F55@Rva00222A8BTarget@@QAEX_N@Z @0x00222F55 186B
// Hide background dispatcher: switch on +0x31C (2=in-game 1=front-end 0=deferred), invoke Hide strings via 0x00222A8B pin with g_00BBFDE0/g_00BBFDDC value selected by bool flag, deferred path re-queues via self-call.
// Evidence: callers 0x00222FFF self plus 0x002233E8 0x002427E2 etc; callee pin 0x00222A8B void twin; strings HideInGameBackground HideFrontEndBackground at 0x007E6D80/0x007E6D68; offsets 0x31C/0x320/0x324 match Rva00222A8BTarget range.
class Rva00222A8BTarget
{
public:
    void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
    void rva00222F55(bool flag);
    void rva002233A6(int mode);
private:
    char m_pad00[0x31C];
    int m_31C;
    int m_320;
    void *m_324;
};


void Rva00222A8BTarget::rva00222F55(bool flag)
{
    if (!this)
        return;
    switch (m_31C) {
    case 2: {
        const char *val = flag ? "1" : "0";
        invoke(m_324, "HideInGameBackground", 1, val, 0, 0, 0, 0);
        m_320 = 2;
        break;
    }
    case 1: {
        const char *val = flag ? "1" : "0";
        invoke(m_324, "HideFrontEndBackground", 1, val, 0, 0, 0, 0);
        m_320 = 1;
        break;
    }
    case 0: {
        if (!flag)
            break;
        int v = m_320;
        if (!v)
            break;
        m_31C = v;
        m_320 = 0;
        rva00222F55(true);
        break;
    }
    default:
        break;
    }
    m_31C = 0;
}
// ?rva002233A6@Rva00222A8BTarget@@QAEXH@Z @0x002233A6 74B
// Show background dispatcher: switch on mode with same +0x31C/+0x320/+0x324 layout as Hide 0x00222F55; case 2 ShowInGameBackground case 1 ShowFrontEndBackground via 0x00222A8B pin case 0 deferred via rva00222F55(false).
// Evidence: strings ShowInGameBackground 0x007E6DBC ShowFrontEndBackground 0x007E6DA4; callees row 0x00222F55 plus pin 0x00222A8B; offsets 0x31C/0x320/0x324 match Rva00222A8BTarget; caller 0x002233E8 path plus 16 callers.
void Rva00222A8BTarget::rva002233A6(int mode)
{
    m_31C = mode;
    switch (mode) {
    case 1:
        m_320 = 0;
        invoke(m_324, "ShowFrontEndBackground", 0, 0, 0, 0, 0, 0);
        break;
    case 2:
        m_320 = 0;
        invoke(m_324, "ShowInGameBackground", 0, 0, 0, 0, 0, 0);
        break;
    case 0:
        rva00222F55(false);
        break;
    default:
        break;
    }
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BBFDDC@@3QBDB=??_C@_01GBGANLPD@0?$AA@")
#pragma comment(linker, "/alternatename:?g_00BBFDE0@@3QBDB=??_C@_01HIHLOKLC@1?$AA@")
