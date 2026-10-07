// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Ghidra's 48-byte body walks the 4-byte start/finish range at this+0x158,
// erasing entries equal to the argument through the call at 0x0025BF5D.
// The pointer-vector instantiation and owner type remain structural inferences.
#include <vector>
#include <algorithm>

class CreateAHeroData;

class Rva003F15A1
{
public:
	void rva003F15A1(void *object);

private:
	char m_pad[0x158];
	_STL::vector<CreateAHeroData *> m_items;
};

void Rva003F15A1::rva003F15A1(void *object)
{
	CreateAHeroData *candidate = (CreateAHeroData *)object;
	_STL::vector<CreateAHeroData *>::iterator it = m_items.begin();
	while (it != m_items.end()) {
		if (*it == candidate)
			it = m_items.erase(it);
		else
			++it;
	}
}
