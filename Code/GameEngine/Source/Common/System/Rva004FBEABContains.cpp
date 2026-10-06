// cl: /Ireference/shims/bfme2_ascii /Oy-
// stlport
// ?rva004FBEAB@Rva004FBEAB@@QAE_NPAVCreateAHeroData@@@Z 0x004FBEAB 43: contains check
// over the CreateAHeroData* registry range [m_begin, m_end) via rowed _STL::find
// at 0x0020E873. Evidence: same +0x8/+0x0c begin/end layout as the 0x004FBE7A count
// body over the same registry; caller 0x002BAF01 tests al as a bool.
#include <algorithm>

class CreateAHeroData;

class Rva004FBEAB
{
private:
	int m_pad[2];
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
public:
	bool rva004FBEAB(CreateAHeroData *val);
};

bool Rva004FBEAB::rva004FBEAB(CreateAHeroData *val)
{
	CreateAHeroData *v = val;
	CreateAHeroData **b = m_begin;
	CreateAHeroData **e = m_end;
	CreateAHeroData **found = _STL::find(b, e, v);
	return found != e;
}
