// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0043B35D@Rva0043B2E2@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@0@Z @0x0043B35D 68B via STLPort range erase plus rowed clear
// Evidence: vendor/stlport/stl/_tree.h erase(first last) calls clear on full range else loops via increment plus single erase
// Retail calls clear 0x0043B334 plus increment 0x00024250 plus single erase 0x005530A8 for map int to voidptr
// Same 68B shape as rowed range erase 0x0007300F in Rva0007300FErase.cpp and 0x004ABC85 modulo clear callee
// Owner Rva0043B2E2 header at +0x00 per RvaTreeEraseClearFamily.cpp; unblocks 0x0043B4EC
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct Rva0043B2E2Node {
  unsigned _M_color;
  Rva0043B2E2Node *parent04;
  Rva0043B2E2Node *left08;
  Rva0043B2E2Node *right0C;
  int m_key10;
};
struct Rva0043B2E2 {
  Rva0043B2E2Node *header00;
  unsigned count04;
  char unknown08[16];
  void rva0043B334();
  void clear();
  typedef _STL::pair<const int, void*> V;
  typedef _STL::_Rb_tree_iterator<V, _STL::_Nonconst_traits<V> > iterator;
  // ?begin@Rva0043B2E2@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@XZ present-unmatched
  iterator begin() {
    iterator it;
    it._M_node = (::_STL::_Rb_tree_node_base*)header00->left08;
    return it;
  }
  // ?end@Rva0043B2E2@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@XZ present-unmatched
  iterator end() {
    iterator it;
    it._M_node = (::_STL::_Rb_tree_node_base*)header00;
    return it;
  }
  void rva0043B35D(iterator first, iterator last);
  unsigned int rva0043B4EC(const int &key);
  void *rva0043B30F(const void *src);
  void rva0043B3A1(Rva0043B2E2Node *&out, Rva0043B2E2Node *a, Rva0043B2E2Node *b, const int *v, Rva0043B2E2Node *c);
  iterator rva0043B3A1Hidden(Rva0043B2E2Node *a, Rva0043B2E2Node *b, const int *v, Rva0043B2E2Node *c);
  _STL::pair<iterator, bool> rva0043B429(const V &v);
  iterator rva0043B535(iterator position, const V &v);
  iterator rva0043B6BA(iterator position, const V &v);
};
void Rva0043B2E2::rva0043B35D(iterator first, iterator last) {
  typedef V VV;
  typedef _STL::_Rb_tree<int, VV, _STL::_Select1st<VV>, _STL::less<int>, _STL::allocator<VV> > Tree;
  if (first == begin() && last == end())
    rva0043B334();
  else
    while (first != last)
      ((Tree*)this)->erase(first++);
}
unsigned int Rva0043B2E2::rva0043B4EC(const int &key) {
  typedef _STL::pair<const int, int> V2;
  typedef _STL::_Rb_tree<int, V2, _STL::_Select1st<V2>, _STL::less<int>, _STL::allocator<V2> > TreeIntInt;
  typedef _STL::_Rb_tree_iterator<V2, _STL::_Nonconst_traits<V2> > IterIntInt;
  _STL::pair<IterIntInt, IterIntInt> p = ((TreeIntInt*)this)->equal_range(key);
  unsigned int n = _STL::distance(*(iterator*)&p.first, *(iterator*)&p.second);
  rva0043B35D(*(iterator*)&p.first, *(iterator*)&p.second);
  return n;
}

// ?rva0043B3A1@Rva0043B2E2@@QAEXAAPAU... @0x0043B3A1 136B: rb-tree insert worker
// for the 0x9C-node tree (chain from 0x0043B30F): position it by header links,
// create the node through pinned member twin of free NewNode 0x0043B30F, link
// it left or right, repair header root/ends, zero links, set parent, rowed
// _Rebalance 0x00025490, bump count and store out. Callers at 0x0043B48B and
// 0x0043B59F. Retail sets ecx=this before the NewNode call so the factory is
// a thiscall member; the free 37B body ignores the dead this in ecx, hence
// the twin pin plus alternatename below per Rva004152E6NewNode precedent.
// Shape follows Rva0018C262::rva0018C33F (138B via rowed factory plus Rebalance).
// ?rva0043B3A1@Rva0043B2E2@@QAEXAAPAU... present-unmatched
void Rva0043B2E2::rva0043B3A1(Rva0043B2E2Node *&out, Rva0043B2E2Node *a, Rva0043B2E2Node *b, const int *v, Rva0043B2E2Node *c)
{
	Rva0043B2E2Node *node;
	if (b != header00 && (c != 0 || (a == 0 && *v >= b->m_key10))) {
		node = (Rva0043B2E2Node *)rva0043B30F(v);
		b->right0C = node;
		Rva0043B2E2Node *root = header00;
		if (b == root->right0C)
			root->right0C = node;
	} else {
		node = (Rva0043B2E2Node *)rva0043B30F(v);
		b->left08 = node;
		Rva0043B2E2Node *root = header00;
		if (b == root) {
			root->parent04 = node;
			header00->right0C = node;
		} else if (b == root->left08) {
			root->left08 = node;
		}
	}
	node->left08 = 0;
	node->right0C = 0;
	node->parent04 = b;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)node, (_STL::_Rb_tree_node_base *&)header00->parent04);
	++count04;
	out = node;
}

_STL::pair<Rva0043B2E2::iterator, bool> Rva0043B2E2::rva0043B429(const V &v)
{
	Rva0043B2E2Node *y = header00;
	Rva0043B2E2Node *x = header00->parent04;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = _STL::less<int>()(v.first, x->m_key10);
		x = comp ? x->left08 : x->right0C;
	}
	iterator j;
	j._M_node = (::_STL::_Rb_tree_node_base *)y;
	if (comp && y == header00->left08) {
		return _STL::pair<iterator, bool>(rva0043B3A1Hidden(y, y, (const int *)&v, 0), true);
	}
	if (comp)
		--j;
	if (_STL::less<int>()(((Rva0043B2E2Node *)j._M_node)->m_key10, v.first)) {
		return _STL::pair<iterator, bool>(rva0043B3A1Hidden(x, y, (const int *)&v, 0), true);
	}
	return _STL::pair<iterator, bool>(j, false);
}

// ?rva0043B535@Rva0043B2E2@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@U23@ABU?$pair@$$CBHPAX@3@@Z @0x0043B535 294B via STLPort hint insert_unique plus rowed insert and _M_insert
// Evidence: chain packet calls rowed 0x0043B3A1 plus rowed 0x0043B429 plus rowed increment 0x00024250 decrement 0x000242C0; ret 0xC hidden iterator; vendor/stlport/stl/_tree.c insert_unique(iterator position const V&)
Rva0043B2E2::iterator Rva0043B2E2::rva0043B535(iterator position, const V &v)
{
	if (position._M_node == (::_STL::_Rb_tree_node_base *)header00->left08) {
		if (count04 <= 0)
			return rva0043B429(v).first;
		if (_STL::less<int>()(v.first, ((Rva0043B2E2Node *)position._M_node)->m_key10))
			return rva0043B3A1Hidden((Rva0043B2E2Node *)position._M_node, (Rva0043B2E2Node *)position._M_node, (const int *)&v, 0);
		else {
			bool comp_pos_v = _STL::less<int>()(((Rva0043B2E2Node *)position._M_node)->m_key10, v.first);
			if (!comp_pos_v)
				return position;
			iterator after = position;
			++after;
			if (after._M_node == (::_STL::_Rb_tree_node_base *)header00)
				return rva0043B3A1Hidden(0, (Rva0043B2E2Node *)position._M_node, (const int *)&v, (Rva0043B2E2Node *)position._M_node);
			if (_STL::less<int>()(v.first, ((Rva0043B2E2Node *)after._M_node)->m_key10)) {
				if (((Rva0043B2E2Node *)position._M_node)->right0C == 0)
					return rva0043B3A1Hidden(0, (Rva0043B2E2Node *)position._M_node, (const int *)&v, (Rva0043B2E2Node *)position._M_node);
				else
					return rva0043B3A1Hidden((Rva0043B2E2Node *)after._M_node, (Rva0043B2E2Node *)after._M_node, (const int *)&v, 0);
			} else {
				return rva0043B429(v).first;
			}
		}
	} else if (position._M_node == (::_STL::_Rb_tree_node_base *)header00) {
		if (_STL::less<int>()(((Rva0043B2E2Node *)header00->right0C)->m_key10, v.first))
			return rva0043B3A1Hidden(0, header00->right0C, (const int *)&v, (Rva0043B2E2Node *)position._M_node);
		else
			return rva0043B429(v).first;
	} else {
		iterator before = position;
		--before;
		bool comp_v_pos = _STL::less<int>()(v.first, ((Rva0043B2E2Node *)position._M_node)->m_key10);
		if (comp_v_pos && _STL::less<int>()(((Rva0043B2E2Node *)before._M_node)->m_key10, v.first)) {
			if (((Rva0043B2E2Node *)before._M_node)->right0C == 0)
				return rva0043B3A1Hidden(0, (Rva0043B2E2Node *)before._M_node, (const int *)&v, (Rva0043B2E2Node *)before._M_node);
			else
				return rva0043B3A1Hidden((Rva0043B2E2Node *)position._M_node, (Rva0043B2E2Node *)position._M_node, (const int *)&v, 0);
		} else {
			iterator after = position;
			++after;
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = _STL::less<int>()(((Rva0043B2E2Node *)position._M_node)->m_key10, v.first);
			if ((!comp_v_pos) && comp_pos_v && (after._M_node == (::_STL::_Rb_tree_node_base *)header00 || _STL::less<int>()(v.first, ((Rva0043B2E2Node *)after._M_node)->m_key10))) {
				if (((Rva0043B2E2Node *)position._M_node)->right0C == 0)
					return rva0043B3A1Hidden(0, (Rva0043B2E2Node *)position._M_node, (const int *)&v, (Rva0043B2E2Node *)position._M_node);
				else
					return rva0043B3A1Hidden((Rva0043B2E2Node *)after._M_node, (Rva0043B2E2Node *)after._M_node, (const int *)&v, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else
					return rva0043B429(v).first;
			}
		}
	}
}

// Target 0x0043B6BA is a 29B iterator-returning forwarder to the rowed
// hint-insert worker at 0x0043B535. Its ret 0xC and unchanged ECX support the
// same tree receiver; the address-derived method name does not claim a source
// library symbol beyond that structural relationship.
Rva0043B2E2::iterator Rva0043B2E2::rva0043B6BA(iterator position, const V &v)
{
	return rva0043B535(position, v);
}

void Rva0043B2E2::clear()
{
	rva0043B334();
}




// Bind the member-twin call above to the rowed free body: same 0x9C node,
// free body ignores the dead this in ecx per Rva004152E6NewNode precedent.
#pragma comment(linker, "/alternatename:?rva0043B30F@Rva0043B2E2@@QAEPAXPBX@Z=?Rva0043B30FNewNode@@YGPAXPBX@Z")
#pragma comment(linker, "/alternatename:?rva0043B3A1Hidden@Rva0043B2E2@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHPAX@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@PAURva0043B2E2Node@@0PBH0@Z=?rva0043B3A1@Rva0043B2E2@@QAEXAAPAURva0043B2E2Node@@PAU2@1PBH1@Z")

