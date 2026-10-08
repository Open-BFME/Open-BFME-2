// cl: /O1 /DNDEBUG /MD /EHsc
// Native 21427A..2142EA RET0: same receiver forwarded through five
// independently identified cleanup calls, followed by two singleton calls.
// WB callgraph supplies LivingWorldManager; sibling CreateSound independently
// establishes the receiver's +204 table. Method semantics retain address name.
// Target fields: optional cleanup objects264/268 and cleared byte2C0.
class Rva002141D1 { public: void rva002141D1(); };
class Rva002126BB { public: void rva002126BB(); };
class Rva00211589 { public: void rva002129B4(); };
class Rva00213A85 { public: void rva00213A0E(); };
class Rva0021237E { public: void rva0021237E(); };
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva002D3627Host {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
};
extern Rva002D3627Host *g_00DFEF18;
class Rva003EF14A { public: void rva003EF1B8(); };
class Rva003FA5B9 { public: void clear(); };
class LivingWorldManager {
public:
    void rva0021427A();
private:
    char unknown00[0x264];
    Rva003FA5B9 *m_cleanup264;
    Rva003EF14A *m_cleanup268;
    char unknown26C[0x2C0-0x26C];
    bool m_active2C0;
};
void LivingWorldManager::rva0021427A()
{
    ((Rva002141D1 *)this)->rva002141D1();
    ((Rva002126BB *)this)->rva002126BB();
    ((Rva00211589 *)this)->rva002129B4();
    ((Rva00213A85 *)this)->rva00213A0E();
    ((Rva0021237E *)this)->rva0021237E();
    if (TheGameLogic) TheGameLogic->rva0023D033();
    if (g_00DFEF18) g_00DFEF18->slot6();
    if (m_cleanup268) {
        m_cleanup268->rva003EF1B8();
        m_cleanup268=0;
    }
    m_active2C0=false;
    if (m_cleanup264) m_cleanup264->clear();
}
