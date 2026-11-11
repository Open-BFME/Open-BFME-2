// cl: /EHsc /MD
// ??1Rva0056B0BF@@UAE@XZ @0x0056B0BF 90B. Dtor with three vptrs unregistering
// via rowed erase 0x002B7250 then base dtor 0x0056AC26.
// Evidence: caller at 0x0056B359 is deleting dtor; sibling shape of 0x00575E4E
// with extra base; [edi] restore is 0x007ED658 same family as prior Base2.
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
struct Parent0056B0BF {
    char pad[8];
    Rva002B7250 holder;
};
#include "../../Include/Common/Rva0056AC26.h"
#include "../../Include/Common/LivingWorldBattleListener.h"
class Rva0056B0BF : public Rva0056AC26, public LivingWorldBattleListener {
public:
    virtual ~Rva0056B0BF();
private:
    Parent0056B0BF *m_parent18;
};
Rva0056B0BF::~Rva0056B0BF()
{
    m_parent18->holder.rva002B7250((CreateAHeroData *)(LivingWorldBattleListener *)this);
}
