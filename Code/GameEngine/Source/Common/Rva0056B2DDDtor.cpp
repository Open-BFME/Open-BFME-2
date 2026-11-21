// cl: /EHsc /MD
// ??1Rva0056B2DD@@UAE@XZ @0x0056B2DD 113B. Dtor unregistering via rowed erase
// 0x002B7250, conditional rowed call 0x003EE966 through TheLivingWorldManager+0x268,
// then base dtor 0x0056AC26. Evidence: deleting-dtor caller at 0x0056B49B;
// extends sibling 0x0056B0BF with the TheLivingWorldManager guard and int member +0x1C.
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
struct Parent0056B2DD {
    char pad[8];
    Rva002B7250 holder;
};
#include "../../Include/Common/Rva0056AC26.h"
#include "../../Include/Common/LivingWorldBattleListener.h"

class Rva0056B2DDB2 : public LivingWorldBattleListener {
public:
    Rva0056B2DDB2() {}
};
#include "../../Include/Common/Rva003EE966.h"
class Rva0021294A {
public:
    char m_pad[0x268];
    Rva003EE966 *m_268;
};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Rva0056B2DD : public Rva0056AC26, public Rva0056B2DDB2 {
public:
    virtual ~Rva0056B2DD();
    virtual bool ac26Slot1();
    virtual void slot4(int army);
    virtual bool slot1(Rva002B4BC9Arg *candidate);
    virtual bool slot4(LivingWorldArmy *army, Rva00318C32Ret *value);
    virtual bool slot5(int);
private:
    Parent0056B2DD *m_parent18;
    int m_x1C;
};
Rva0056B2DD::~Rva0056B2DD()
{
    m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B2DDB2 *)this);
    Rva003EE966 *p = ((Rva0021294A *)TheLivingWorldManager)->m_268;
    if (p != 0)
        p->rva003EE966(m_x1C);
}
