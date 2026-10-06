// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?rva003F0DA5@Rva003F0DA5@@QAE_NPAVCreateAHeroData@@@Z, retail 0x003F0DA5, 33 bytes.
// __thiscall bool contains via rowed _STL::find at 0x0020E873 over CreateAHeroData*
// range at +0/+4, returns found != end. Evidence: find row, caller 0x003F11EC passes
// element at +0/+4 shape with this from vector element, unlocks 0x003F11EC.
#include <algorithm>

class CreateAHeroData;

class Rva003F0DA5
{
public:
	bool rva003F0DA5(CreateAHeroData *val);
private:
	CreateAHeroData **m_first;
	CreateAHeroData **m_last;
};

bool Rva003F0DA5::rva003F0DA5(CreateAHeroData *val)
{
	CreateAHeroData **found = _STL::find(m_first, m_last, val);
	return found != m_last;
}
