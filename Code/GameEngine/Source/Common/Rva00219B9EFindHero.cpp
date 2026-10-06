// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// ?rva0021A6C8@Rva00219B9E@@QAEPAVCreateAHeroData@@H@Z @0x0021A6C8 (96B).
// Find hero by id: scan hero list at +0x174 via rowed rva0040A32F plus
// rowed rva00219FE3 compare plus +0x48 flag check.
// Evidence: pin ?rva0021A6C8; callers MpGameSetup 0x0044158C plus 2 unclaimed;
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

class Rva00219B9E
{
public:
	CreateAHeroData *rva0021A6C8(int v);
	int rva00219FE3(unsigned int o, unsigned int i);

private:
	char m_pad00[0x174];
	Rva0040A3F9 m_heroes174;
};

CreateAHeroData *Rva00219B9E::rva0021A6C8(int v)
{
	Rva0040A3F9 *heroes = &m_heroes174;
	unsigned int count = (unsigned int)(heroes->m_end - heroes->m_begin);
	for (unsigned int i = 0; i < count; ++i) {
		CreateAHeroData *data = heroes->rva0040A32F((int)i);
		if (data != 0 && data->m_flag48 != 0 && rva00219FE3(data->m_o0C, data->m_i10) == v)
			return data;
	}
	return 0;
}
