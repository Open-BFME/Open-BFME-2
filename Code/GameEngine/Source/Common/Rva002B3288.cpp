// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B3288@Rva002B3288@@QAE_NXZ @0x002B3288 70B.
// All-of loop over pointer vector at +0x10C calling pinned byte predicate
// at 0x00318F42; empty returns true. Same family as landed 0x002B4B3D and
// 0x002E0AEA any-of vector loops, opposite polarity.
// Evidence: pin 0x00318F42 QAEEXZ pred, caller 0x002B53C0 tests al.
#include <vector>
class Mbr002E0B30
{
public:
	unsigned char pred();
};

class Rva002B3288
{
public:
	bool rva002B3288();
private:
	char m_pad[0x10C];
	_STL::vector<Mbr002E0B30 *> m_items;
};

bool Rva002B3288::rva002B3288()
{
	for (unsigned int i = 0; i < m_items.size(); ++i)
	{
		if (!m_items[i]->pred())
			return false;
	}
	return true;
}
