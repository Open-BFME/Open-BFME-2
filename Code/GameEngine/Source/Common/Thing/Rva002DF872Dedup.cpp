// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva002DF872@Rva002DF872@@QAEXXZ @0x002DF872 41B: dedup adjacent 12-byte recs by first dword via BfmePod12 erase 0x0034C117; caller 0x002DF985.
// Evidence: retail calls rowed erase vector<BfmePod12> 0x0034C117; begin/end from [esi]/[esi+4]; called from 0x002DF93D.
#include <vector>

struct BfmePod12 { int a[3]; };

class Rva002DF872 : public _STL::vector<BfmePod12, _STL::allocator<BfmePod12> >
{
public:
	void rva002DF872();
};

void Rva002DF872::rva002DF872()
{
	iterator it = begin();
	while (it != end()) {
		iterator next = it + 1;
		if (next == end())
			break;
		if (it->a[0] == next->a[0])
			it = erase(it);
		else
			it = next;
	}
}
