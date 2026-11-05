// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// CreateAHeroManager::GetDefaultHero, retail 0x0021A6C8 (96B; WorldBuilder
// name, callgraph lead). Scans the hero list at +0x174 via rowed rva0040A32F
// for a flagged (+0x48) hero whose class/subclass prefer the faction
// (CreateAHeroManager::GetPreferedFaction 0x00219FE3).
// Evidence: pin ?rva0021A6C8; callers AptMpGameSetup 0x0044158C plus 2 unclaimed;
// neighbours rva0021A1B6 and BfmeStringRecord dtor prove TU and flags;
// +0x174 hero-list count via (finish-start)/4 plus ret-4 int param.

#include "../../Include/GameLogic/CreateAHeroData.h"

#include "../../Include/Common/Rva0040A3F9.h"

#include "../../Include/GameLogic/CreateAHeroManager.h"

CreateAHeroData *CreateAHeroManager::GetDefaultHero(int v)
{
	Rva0040A3F9 *heroes = (Rva0040A3F9 *)field174;
	unsigned int count = (unsigned int)(heroes->m_field04 - heroes->m_field00);
	for (unsigned int i = 0; i < count; ++i) {
		CreateAHeroData *data = heroes->rva0040A32F((int)i);
		if (data != 0 && data->m_48 != 0 && GetPreferedFaction(data->m_0c, data->m_10) == v)
			return data;
	}
	return 0;
}
