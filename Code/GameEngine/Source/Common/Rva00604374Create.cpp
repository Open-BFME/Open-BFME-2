// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00604374@Rva00604374@@QAEPAXABVRva0060426C@@@Z @0x00604374 34B node alloc 0x20 via rowed 0x000307F0 then rowed Construct 0x00604289 at +0x10. Evidence: callers 0x00604400 0x00604419 in insert 0x006043CE same shape as Rva00397CC9Alloc.
#include <memory>
#include <set>

class Rva0060426C;
void Rva00604289Construct(Rva0060426C *dest, const Rva0060426C &src);

class Rva00604374
{
public:
	void *rva00604374(const Rva0060426C &src);
};

void *Rva00604374::rva00604374(const Rva0060426C &src)
{
	char *p = _STL::allocator<char>::allocate(0x20, 0);
	Rva00604289Construct((Rva0060426C *)(p + 0x10), src);
	return p;
}

struct Rva006038D4Less { bool operator()(const char *, const char *) const; };
// Native 6043CE/6044A0 use strcmp6038D4 on the first pointer-sized word.
// Node creator604374 allocates32B and copies the16B Rva0060426C value via
// matched Construct604289. Payload's remaining12B are preserved by that
// existing copy provider; no application type or no-case ordering is asserted.
// Algorithms follow matched6012ED/6013B7 and the new600854/600991 siblings;
// every layout access, branch, and call is checked against these native bodies.
class Rva0060426C;
struct Rva006044A0Node {
	unsigned color;
	Rva006044A0Node *parent;
	Rva006044A0Node *left;
	Rva006044A0Node *right;
};
struct Rva006044A0Pair {
	Rva006044A0Node *first;
	bool second;
	Rva006044A0Pair(Rva006044A0Node *f, bool s) : first(f), second(s) {}
};
struct Rva006044A0 {
	Rva006044A0Node *m_header;
	int m_count;
	Rva006038D4Less m_less;
	// Native helper returns the output pointer in EAX.
	void **rva006043CE(void **result, void *x, void *y, const void *value, void *known);
	Rva006044A0Pair rva006044A0(const Rva0060426C &v);
};
Rva006044A0Pair Rva006044A0::rva006044A0(const Rva0060426C &v)
{
	Rva006044A0Node *y = m_header;
	Rva006044A0Node *x = m_header->parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = m_less(*(const char **)&v, *(const char **)((char *)x + 0x10));
		x = comp ? x->left : x->right;
	}
	Rva006044A0Node *j = y;
	if (comp) {
		if (j == m_header->left)
		{
			Rva006044A0Node *tmp;
			void **pres = rva006043CE((void **)&tmp, y, y, &v, 0);
			tmp = (Rva006044A0Node *)*pres;
			return Rva006044A0Pair(tmp, true);
		}
		j = (Rva006044A0Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)y);
	}
	if (m_less(*(const char **)((char *)j + 0x10), *(const char **)&v))
	{
		Rva006044A0Node *tmp;
		void **pres = rva006043CE((void **)&tmp, x, y, &v, 0);
		tmp = (Rva006044A0Node *)*pres;
		return Rva006044A0Pair(tmp, true);
	}
	return Rva006044A0Pair(j, false);
}

void **Rva006044A0::rva006043CE(void **result, void *x, void *y, const void *value, void *known)
{
	Rva006044A0Node *yn = (Rva006044A0Node *)y;
	Rva006044A0Node *node;
	if (yn != m_header && (known != 0 || (x == 0 && !m_less(*(const char **)value, *(const char **)((char *)yn + 0x10))))) {
		node = (Rva006044A0Node *)((Rva00604374 *)this)->rva00604374(*(const Rva0060426C *)value);
		yn->right = node;
		Rva006044A0Node *header = m_header;
		if (yn == header->right)
			header->right = node;
	} else {
		node = (Rva006044A0Node *)((Rva00604374 *)this)->rva00604374(*(const Rva0060426C *)value);
		yn->left = node;
		Rva006044A0Node *header = m_header;
		if (yn == header) {
			header->parent = node;
			m_header->right = node;
		} else if (yn == header->left) {
			header->left = node;
		}
	}
	node->left = 0;
	node->right = 0;
	node->parent = yn;
	_STL::_Rb_global<bool>::_Rebalance(
		reinterpret_cast<_STL::_Rb_tree_node_base *>(node),
		reinterpret_cast<_STL::_Rb_tree_node_base *&>(m_header->parent));
	++m_count;
	*result = node;
	return result;
}
