// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva006012ED@Rva0060126D@@QAEPAPAXPAPAXPAX1PBX1@Z @0x006012ED 146B lane=chain
// Evidence: calls 0x006012A2 just landed plus rowed CStrLess 0x006038D4 Rebalance 0x00025490; prev 0x006012C4 next 0x0060137F same family; caller 0x0060142F in 0x006013B7; unblocks 0x006013B7.
#include <set>
struct Rva00600F9CElement
{
	Rva00600F9CElement(const Rva00600F9CElement &that);
};
struct Rva006038D4Less
{
	bool operator()(const char *a, const char *b) const;
};
#pragma comment(linker, "/alternatename:??RRva006038D4Less@@QBE_NPBD0@Z=?Rva0006038D4CStrLess@@YG_NPBD0@Z")
bool __stdcall Rva0006038D4CStrLess(const char *a, const char *b);
struct Rva0060126DNode
{
	unsigned color;
	Rva0060126DNode *parent;
	Rva0060126DNode *left;
	Rva0060126DNode *right;
};
class Rva0060126D
{
public:
	void *rva006012A2(const Rva00600F9CElement &val);
	void **rva006012ED(void **result, void *x, void *y, const void *value, void *known);
private:
	Rva0060126DNode *m_header;
	int m_count;
	Rva006038D4Less m_less;
};
void **Rva0060126D::rva006012ED(void **result, void *x, void *y, const void *value, void *known)
{
	Rva0060126DNode *yn = (Rva0060126DNode *)y;
	Rva0060126DNode *node;
	if (yn != m_header && (known != 0 || (x == 0 && !m_less(*(const char **)value, *(const char **)((char *)yn + 0x10))))) {
		node = (Rva0060126DNode *)rva006012A2(*(const Rva00600F9CElement *)value);
		yn->right = node;
		Rva0060126DNode *header = m_header;
		if (yn == header->right)
			header->right = node;
	} else {
		node = (Rva0060126DNode *)rva006012A2(*(const Rva00600F9CElement *)value);
		yn->left = node;
		Rva0060126DNode *header = m_header;
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

// Native EAX returns the result pointer, as 0x6013B7 immediately dereferences
// it. Reconcile the provider with that established caller ABI; bytes unchanged.
