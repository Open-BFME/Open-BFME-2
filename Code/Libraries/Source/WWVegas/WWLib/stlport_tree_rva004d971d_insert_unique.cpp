// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert_unique@?$_Rb_tree@IVRva004D971D@@URva004DA0B7OrderKey@@U?$less@I@_STL@@V?$allocator@VRva004D971D@@@4@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@VRva004D971D@@U?$_Nonconst_traits@VRva004D971D@@@_STL@@@_STL@@_N@2@ABVRva004D971D@@@Z @0x004DA264 134B: insert_unique for unsigned-key Rva004D971D tree via rowed _M_insert 0x004DA0B7 plus _M_decrement 0x000242C0. Evidence: same 134B leaf shape as PodMap insert_unique 0x00422918 same calls; unsigned first-dword compare; callers at 0x004DA34A and 0x004DBC6F.
#include <map>
class Rva004D971D
{
	char m_opaque[40];
public:
	__declspec(nothrow) Rva004D971D(const Rva004D971D &);
	~Rva004D971D();
};
struct Rva004DA0B7OrderKey
{
	const unsigned &operator()(const Rva004D971D &v) const
	{
		return *reinterpret_cast<const unsigned *>(&v);
	}
};
typedef _STL::_Rb_tree<unsigned, Rva004D971D, Rva004DA0B7OrderKey, _STL::less<unsigned>, _STL::allocator<Rva004D971D> > Rva004DA0B7Tree;
template _STL::pair<Rva004DA0B7Tree::iterator, bool> Rva004DA0B7Tree::insert_unique(const Rva004D971D &);
