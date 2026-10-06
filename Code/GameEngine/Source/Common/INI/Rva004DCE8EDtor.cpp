// cl: /MD /EHsc /DNDEBUG
// stlport
// ??1Rva004DCE8E@@QAE@XZ @0x004DCE8E 54B: dtor destroying two Rb_tree maps at +0x14 and +0x20.
// Evidence: retail lea ecx [esi+0x20] calls rowed 0x004DCE51 then lea ecx [esi+0x14] calls rowed 0x004636FE with EH prolog table 0x00B916EC; pin ??1Rva004DCE8E@@QAE@XZ; caller deleting dtor in FamilyDeletingDtors11.cpp.
#include <map>

struct Rva00462D35Mapped
{
	unsigned int m_bits;
};

typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, int>, _STL::_Select1st<_STL::pair<const unsigned short, int> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, int> > > Rva004DCE8ETree20;
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00462D35Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00462D35Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00462D35Mapped> > > Rva004DCE8ETree14;

class Rva004DCE8E
{
public:
	~Rva004DCE8E();
private:
	char m_pad00[0x14];
	Rva004DCE8ETree14 m_tree14;
	Rva004DCE8ETree20 m_tree20;
};

Rva004DCE8E::~Rva004DCE8E()
{
}
