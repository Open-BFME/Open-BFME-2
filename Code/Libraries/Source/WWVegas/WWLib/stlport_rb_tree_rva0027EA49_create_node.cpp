// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_create_node@?$_Rb_tree@URva0027EA49@@U1@U?$_Identity@URva0027EA49@@@_STL@@U?$less@URva0027EA49@@@3@V?$allocator@URva0027EA49@@@3@@_STL@@IAEPAU?$_Rb_tree_node@URva0027EA49@@@2@ABURva0027EA49@@@Z, retail 0x005C6728, 34 bytes.
// _M_create_node for Rva0027EA49 set (8B value: int at +0 plus TargetRef at
// +4). Allocates 0x18 node via rowed byte allocator 0x000307F0 then copies
// the value at +0x10 via rowed ?Rva0030CA53Set@@YAXPAVRva004733E0@@PBV1@@Z
// (0x0030CA53 wrapping Rva004733E0::set 0x0030BF66 with matching 8B layout
// and +4 refcount). Shape matches _M_create_node precedent 0x002D464E (34B,
// same flags without /I shim so allocator<char> specialization compiles).
// Callers at 0x005C6A9D/0x005C6AB6 in _M_insert 0x005C6A75 pass this in ecx
// (IAE protected thiscall) with the value ref; this is unused (static
// allocate plus free wrapper) so the body is identical to a free stdcall.
#include <map>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva0027EA49 {
	~Rva0027EA49();
	int m_00;
	TargetRef00217D4C *m_04;
};
bool operator<(const Rva0027EA49 &a, const Rva0027EA49 &b);
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > Rva0027EA49Tree;
namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
}
struct Rva004733E0Obj
{
	int m_00;
	int m_04;
};
class Rva004733E0
{
	int m_00;
	Rva004733E0Obj *m_04;
public:
	Rva004733E0 *set(const Rva004733E0 *src);
};
void Rva0030CA53Set(Rva004733E0 *dst, const Rva004733E0 *src);
// ?_M_create_node@?$_Rb_tree@URva0027EA49@@U1@U?$_Identity@URva0027EA49@@@_STL@@U?$less@URva0027EA49@@@3@V?$allocator@URva0027EA49@@@3@@_STL@@IAEPAU?$_Rb_tree_node@URva0027EA49@@@2@ABURva0027EA49@@@Z
template <>
Rva0027EA49Tree::_Link_type Rva0027EA49Tree::_M_create_node(const Rva0027EA49Tree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<Rva0027EA49Tree::value_type>), 0);
	Rva0030CA53Set((Rva004733E0 *)&node->_M_value_field, (const Rva004733E0 *)&value);
	return node;
}
template Rva0027EA49Tree::_Link_type Rva0027EA49Tree::_M_create_node(const Rva0027EA49Tree::value_type &);
