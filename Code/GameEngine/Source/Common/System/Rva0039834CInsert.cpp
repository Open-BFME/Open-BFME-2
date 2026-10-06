// cl: /DNDEBUG /MD /EHsc
// ?rva0039834C@Rva0039834C@@QAEXAAPAURvaNode0039834C@@PAU2@1PBURva0039627D@@1@Z @0x0039834C 136B evidence: chain lane calls rowed alloc 0x00397CC9 plus Rebalance 0x00025490 plus signed key at plus10; caller 0x00399312 unblocks 0x003992B0; sibling Rva001364F7Insert same 136B shape; factory called as thiscall member per two retail mov ecx edi so pinned twin member at same address ICF with free row.
// Proven blocker note: retail passes this in ecx to the node factory (push v then mov ecx edi then call) so the factory is __thiscall; the ledger rows it as free __stdcall with identical 34B body that ignores ecx. Calling the rowed free name omits both movs (132B vs 136B). Twin member pin at 0x00397CC9 keeps the bytes and the correct target address.
struct Rva0039627D {
	int m_key;
	unsigned char m_body[12];
};
struct RvaNode0039834C {
	int _c0;
	RvaNode0039834C *_parent;
	RvaNode0039834C *_left;
	RvaNode0039834C *_right;
	int _key10;
	unsigned char _pad14[12];
};
namespace _STL {
struct _Rb_tree_node_base {};
template <typename D> class _Rb_global {
public:
	static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
};
}
struct Rva0039834C {
	RvaNode0039834C *m_root;
	unsigned m_count;
	void *rva00397CC9(const Rva0039627D &src);
	void rva0039834C(RvaNode0039834C *&out, RvaNode0039834C *a, RvaNode0039834C *b, const Rva0039627D *v, RvaNode0039834C *c);
};
void Rva0039834C::rva0039834C(RvaNode0039834C *&out, RvaNode0039834C *a, RvaNode0039834C *b, const Rva0039627D *v, RvaNode0039834C *c)
{
	RvaNode0039834C *node;
	if (b != m_root && (c != 0 || (a == 0 && v->m_key >= b->_key10))) {
		node = (RvaNode0039834C *)rva00397CC9(*v);
		b->_right = node;
		RvaNode0039834C *root = m_root;
		if (b == root->_right)
			root->_right = node;
	} else {
		node = (RvaNode0039834C *)rva00397CC9(*v);
		b->_left = node;
		RvaNode0039834C *root = m_root;
		if (b == root) {
			root->_parent = node;
			m_root->_right = node;
		} else if (b == root->_left) {
			root->_left = node;
		}
	}
	node->_left = 0;
	node->_right = 0;
	node->_parent = b;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)node, (_STL::_Rb_tree_node_base *&)m_root->_parent);
	++m_count;
	out = node;
}
