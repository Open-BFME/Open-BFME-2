// cl: /MD
// ?rva00222A53@Rva00222A8BTarget@@QAEEXZ @0x00222A53 56B
// Window-modal check: +0x300 header -4 != -1 and +0x314 window !=0 then
// TheWindowManager slot 0xC0 current equals +0x314 returns true else +0x329.
// Evidence: callers 0x0043288D 31B test-al and 0x002A3303 1314B; TheWindowManager
// 103 TUs extern; virtual 0xC0 indirect no reloc; prev Rva002229E3 next stlport.
// TheRva00222A8BTarget global proves owner class Rva00222A8BTarget.
class GameWindowManager
{
public:
    virtual void *v00(); virtual void *v01(); virtual void *v02(); virtual void *v03();
    virtual void *v04(); virtual void *v05(); virtual void *v06(); virtual void *v07();
    virtual void *v08(); virtual void *v09(); virtual void *v10(); virtual void *v11();
    virtual void *v12(); virtual void *v13(); virtual void *v14(); virtual void *v15();
    virtual void *v16(); virtual void *v17(); virtual void *v18(); virtual void *v19();
    virtual void *v20(); virtual void *v21(); virtual void *v22(); virtual void *v23();
    virtual void *v24(); virtual void *v25(); virtual void *v26(); virtual void *v27();
    virtual void *v28(); virtual void *v29(); virtual void *v30(); virtual void *v31();
    virtual void *v32(); virtual void *v33(); virtual void *v34(); virtual void *v35();
    virtual void *v36(); virtual void *v37(); virtual void *v38(); virtual void *v39();
    virtual void *v40(); virtual void *v41(); virtual void *v42(); virtual void *v43();
    virtual void *v44(); virtual void *v45(); virtual void *v46(); virtual void *v47();
    virtual void *winGetFocus();
};
extern GameWindowManager *TheWindowManager;
class Rva00222A8BTarget
{
public:
    unsigned char rva00222A53();
private:
    char m_pad0[0x300];
    void *m_p300;
    char m_pad1[0x314 - 0x304];
    void *m_p314;
    char m_pad2[0x329 - 0x318];
    unsigned char m_b329;
};
unsigned char Rva00222A8BTarget::rva00222A53()
{
    void *p = m_p300;
    if (*(int *)((char *)p - 4) != -1) {
        void **pp = &m_p314;
        if (*pp != 0) {
            if (*pp == TheWindowManager->winGetFocus())
                return 1;
        }
    }
    return m_b329;
}
