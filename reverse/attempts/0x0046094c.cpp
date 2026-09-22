// ?bfmeCallEBC@BfmeOwnerEBC@@QAEXXZ
// partial score=0.72 date=2026-09-22
// cl: /O1 /Oy- /EHsc /MD
// Retail EBC owner cleanup at 0x0046094C. Identity and member meanings are
// structural until call-site or data evidence names the application types.

class BfmeResourceEBC
{
public:
    virtual void *deleteInstance(int);
    bool bfmeIsRegistered();
};

class BfmeManagerEBC
{
public:
    void bfmeRemove(BfmeResourceEBC *);
    void bfmeFinish();
};

struct BfmeRegistryEBC
{
    char m_pad[0x10];
    BfmeManagerEBC *m_manager;
};

extern BfmeRegistryEBC *g_bfmeRegistryEBC;

class BfmeOwnerEBC
{
public:
    void bfmeCallEBC();

private:
    char m_pad[0x24];
    BfmeResourceEBC *m_resources[6];
    bool m_enabled;
};

void BfmeOwnerEBC::bfmeCallEBC()
{
    if (!m_enabled)
        return;
    for (int i = 0; i < 6; ++i) {
        BfmeResourceEBC **slot = &m_resources[i];
        if (*slot) {
            if ((*slot)->bfmeIsRegistered())
                g_bfmeRegistryEBC->m_manager->bfmeRemove(*slot);
            if (*slot)
                ::operator delete((*slot)->deleteInstance(0));
            else
                ::operator delete(0);
            *slot = 0;
        }
    }
    g_bfmeRegistryEBC->m_manager->bfmeFinish();
    m_enabled = false;
}
