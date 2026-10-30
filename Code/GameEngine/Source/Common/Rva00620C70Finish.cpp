// cl: /O2 /Oy /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// The unsigned key is passed by address to the signed-key STL tree lookup.
#include <map>

typedef _STL::pair<const int, void *> BfmeUnsignedKeyTree620C70Value;

class BfmeUnsignedKeyTree620C70
{
public:
	bool contains(unsigned int key);

private:
	typedef _STL::_Rb_tree<int, BfmeUnsignedKeyTree620C70Value, _STL::_Select1st<BfmeUnsignedKeyTree620C70Value>,
		_STL::less<int>, _STL::allocator<BfmeUnsignedKeyTree620C70Value> > Tree;
	Tree m_tree;
};

bool BfmeUnsignedKeyTree620C70::contains(unsigned int key)
{
	Tree::iterator it = m_tree.find(*(const int *)&key);
	return it != m_tree.end();
}
