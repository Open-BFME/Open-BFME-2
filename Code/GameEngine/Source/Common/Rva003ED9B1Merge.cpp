// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003ED9B1@Rva003ED9B1@@QAEXABV1@@Z @ 0x003ED9B1 126B
// Merge bitset from src vector into this vector over global RB-tree 0x00A02E50 via rowed resize 0x000E6D39.
// Resizes this to src size then for each node sets bit m_14 and incs m_18; callers 0x0020D8AB/0x003EDD99/0x004ABE12.
// Neighbour Rva003ED498Count.cpp shares /O1 /EHsc STLport flags and tree walk idioms.
#include <vector>

class Drawable;

_STLP_BEGIN_NAMESPACE
template <>
class vector<Drawable *, allocator<Drawable *> > : public _Vector_base<Drawable *, allocator<Drawable *> >
{
public:
	void resize(unsigned int n, Drawable *x);
};
_STLP_END_NAMESPACE

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

struct BitRange
{
	unsigned const *m_begin;
	unsigned const *m_end;
};
struct TreeNode
{
	_STL::_Rb_tree_node_base m_base;
	int m_10;
	unsigned m_14;
	unsigned m_18;
};
extern _STL::_Rb_tree_node_base *g_00A02E50;

class Rva003ED9B1
{
public:
	void rva003ED9B1(Rva003ED9B1 const &src);
private:
	_STL::vector<Drawable *, _STL::allocator<Drawable *> > m_vec;
};
void Rva003ED9B1::rva003ED9B1(Rva003ED9B1 const &src)
{
	BitRange const *srcRange = (BitRange const *)&src.m_vec;
	BitRange const *thisRange = (BitRange const *)&m_vec;
	int argCount = (int)(srcRange->m_end - srcRange->m_begin);
	unsigned thisCount = (unsigned)(thisRange->m_end - thisRange->m_begin);
	if (thisCount < (unsigned)argCount)
		m_vec.resize((unsigned)argCount, 0);
	_STL::_Rb_tree_node_base *header = g_00A02E50;
	_STL::_Rb_tree_node_base *n = header->_M_left;
	if (n == header)
		return;
	do
	{
		TreeNode *tn = (TreeNode *)n;
		unsigned bits = tn->m_14;
		int word = (int)(bits >> 5);
		unsigned mask = 1u << (bits & 31);
		if (argCount > word)
		{
			unsigned const *argBits = ((BitRange const *)&src.m_vec)->m_begin;
			if ((argBits[word] & mask) != 0)
			{
				unsigned const *thisBits = ((BitRange const *)&m_vec)->m_begin;
				if ((thisBits[word] & mask) == 0)
				{
					++tn->m_18;
					((unsigned *)((BitRange const *)&m_vec)->m_begin)[word] |= mask;
				}
			}
		}
		n = _STL::_Rb_global<bool>::_M_increment(n);
	} while (n != header);
}
