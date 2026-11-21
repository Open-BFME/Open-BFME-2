// cl: /O1 /EHsc /MD
// ??1Rva0056B218@@UAE@XZ @0x0056B218 118B. Dtor unregistering from two nullable
// parent holders via rowed erase 0x002B7250 then base dtor 0x0056AC26.
// Evidence: deleting-dtor caller at 0x0056B47F; extends sibling 0x0056B0BF
// with a second holder at +0x1C; both nulled after erase.
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
struct Parent0056B218 {
    char pad[8];
    Rva002B7250 holder;
};
#include "../../Include/Common/Rva0056AC26.h"
#include "../../Include/Common/LivingWorldBattleListener.h"

class Rva0056B218B2 : public LivingWorldBattleListener
{
public:
	Rva0056B218B2() {}
};
class Rva0056B218 : public Rva0056AC26, public Rva0056B218B2 {
public:
    virtual ~Rva0056B218();
    // Rva0056AC26 slot 1 (retail table 0x00C6D3A8 / 0x00C6D40C slot 1): 0x00232E8F,
    // `mov al,[ecx+20h]; ret`, the flag at +0x20 (a body retail folds).
    virtual bool ac26Slot1();
	// LivingWorldBattleListener at +0x14 (retail table 0x00C6D3BC) slots 0 and 1.
	virtual void onArmyRemoved(void *army);
	virtual void slot1(int a, int b);
	// Rva0056AC26Base2 at +8 (retail table 0x00C6D3D0) slots 1 and 3.
	virtual bool slot1(Rva002B4BC9Arg *candidate);
	virtual bool slot3(int first, int second);
private:
    Parent0056B218 *m_parent18;
    Parent0056B218 *m_parent1C;
};
Rva0056B218::~Rva0056B218()
{
    if (m_parent18 != 0) {
        m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B218B2 *)this);
        m_parent18 = 0;
    }
    if (m_parent1C != 0) {
        m_parent1C->holder.rva002B7250((CreateAHeroData *)(Rva0056B218B2 *)this);
        m_parent1C = 0;
    }
}

// Slot 0 of retail table 0x00C6D3BC: the parent that matches is released the
// way the destructor releases both, then nulled. Twin of 0x0056B1F2.
void Rva0056B218::onArmyRemoved(void *army)
{
    if (m_parent18 == army) {
        m_parent18->holder.rva002B7250((CreateAHeroData *)(Rva0056B218B2 *)this);
        m_parent18 = 0;
    }
    else if (m_parent1C == army) {
        m_parent1C->holder.rva002B7250((CreateAHeroData *)(Rva0056B218B2 *)this);
        m_parent1C = 0;
    }
}
