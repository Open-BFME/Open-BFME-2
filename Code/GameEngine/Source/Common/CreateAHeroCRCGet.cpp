// cl: /O1 /MD
// CreateAHeroCRC::getCRC, native 0x0021F5E3..0x0021F5F8 (21B).
// Identity: GameEngine::init 0x0022E2E4 calls it on TheCreateAHeroManager
// (0x00DFE344); the pin is that recovered caller's REL32.
// Target shape: the cached CRC lives at +0x1F0; when it is still zero the body
// runs 0x0021F47E on the same object, which rebuilds the hero list at +0x174
// and stores the folded CRC of the loaded heroes at +0x1F0, then returns the
// cached value. The rebuild's name is address-derived: it is not recovered.

class CreateAHeroCRC
{
public:
	unsigned int getCRC();

private:
	char m_unknown000[0x1F0];
	unsigned int m_crc;
};

// 0x0021F47E is rowed as CreateAHeroManager::LoadMyHeroList (357B; WB
// B7EE40) - same-this no-arg call, so this resolves to the rowed body
// instead of the unrowed spelling (sole U on this unit).
#include "../../Include/GameLogic/CreateAHeroManager.h"

unsigned int CreateAHeroCRC::getCRC()
{
	if (m_crc == 0)
		((CreateAHeroManager *)this)->LoadMyHeroList();
	return m_crc;
}
