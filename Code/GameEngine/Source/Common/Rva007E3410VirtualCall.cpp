// cl: /O1
// Open-BFME: mode-gated virtual call reconstructed from retail RVA 0x007E3410.

class Rva007E3410Target
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void invoke(int first, int second);
};

class Rva007E3410Object
{
public:
    void invokeForMode(void);

private:
    char m_pad0[4];
    Rva007E3410Target *m_target;
    int m_mode;
};

void Rva007E3410Object::invokeForMode(void)
{
    if (m_mode == 6)
    {
        m_target->invoke(0, 0);
    }
}

// Whole one-body BFME1 Rva00971BA0GuardedHelper.cpp at revision
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 supplies this control-flow
// lead. Complete native Ghidra180AD6/35 independently proves receiver
// virtual slots +28/+2C, a pointer at +14, and the null-zero/otherwise
// tail call at 180AF4 to rowed1A3140/80. That provider independently
// byte-verifies and links in BfmeHelper71BA0.cpp. This narrow external
// ABI view declares no new layout or original identity for its receiver.
// The caller's owner, original names and full layout are unknown; unused
// virtual declarations preserve slot spacing only, not original signatures.
class Rva00180AD6HelperABI
{
public:
    int invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva00180AD6HelperABI@@QAEHXZ=?bfmeCall71BA0@BfmeHelper71BA0@@QAEHXZ")

class Rva00180AD6HelperOwner
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual bool ready();
    virtual void prepare();

    int guardedHelper();
private:
    unsigned char reserved04[0x14 - 4];
    Rva00180AD6HelperABI *helper;
};

int Rva00180AD6HelperOwner::guardedHelper()
{
    if (!ready())
        prepare();
    if (!helper)
        return 0;
    return helper->invoke();
}
