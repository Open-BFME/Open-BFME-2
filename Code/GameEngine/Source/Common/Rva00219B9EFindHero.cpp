// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// CreateAHeroManager::GetDefaultHero, retail 0x0021A6C8 (96B; WorldBuilder
// name, callgraph lead). Scans the hero list at +0x174 via rowed rva0040A32F
// for a flagged (+0x48) hero whose class/subclass prefer the faction
// (CreateAHeroManager::GetPreferedFaction 0x00219FE3).
// Evidence: pin ?rva0021A6C8; callers AptMpGameSetup 0x0044158C plus 2 unclaimed;
// neighbours rva0021A1B6 and BfmeStringRecord dtor prove TU and flags;
// +0x174 hero-list count via (finish-start)/4 plus ret-4 int param.

class CreateAHeroData
{
public:
	char m_pad00[0x0C];
	unsigned int m_o0C;
	unsigned int m_i10;
	char m_pad14[0x48 - 0x14];
	unsigned char m_flag48;
};

class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A32F(int index);

public:
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
};

class CreateAHeroManager
{
public:
	CreateAHeroData *GetDefaultHero(int v);
	int GetPreferedFaction(unsigned int classIndex, unsigned int subClassIndex);

private:
	char m_pad00[0x174];
	Rva0040A3F9 m_heroes174;
};

CreateAHeroData *CreateAHeroManager::GetDefaultHero(int v)
{
	Rva0040A3F9 *heroes = &m_heroes174;
	unsigned int count = (unsigned int)(heroes->m_end - heroes->m_begin);
	for (unsigned int i = 0; i < count; ++i) {
		CreateAHeroData *data = heroes->rva0040A32F((int)i);
		if (data != 0 && data->m_flag48 != 0 && GetPreferedFaction(data->m_o0C, data->m_i10) == v)
			return data;
	}
	return 0;
}
