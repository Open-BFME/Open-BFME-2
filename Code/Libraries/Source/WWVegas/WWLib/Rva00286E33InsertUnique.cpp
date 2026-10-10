// cl: /O1 /Oy- /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native286E33..286EC8 is the149B unique-insert twin of39F692.
// Comparator285672 examines signed words at value+8/+C; creator286693
// independently establishes20B payload extent. Its16+4 template spelling is
// an existing callee ABI view, not proof that the target is that map type.
// The shared146B insert worker
// is a genuine fold of the existing synthetic provider, with zero new bytes.
struct Rva002CF120;
namespace _STL {
	
	
}
class Rva00285672 { public: bool rva00285672(const Rva00285672 &) const; char m_lead[8]; int m_first,m_second; };
#include <map>
struct TreeKey00286693 { int a[4]; bool operator<(const TreeKey00286693 &) const; };
struct TreeMapped00286693 { int a[1]; };
typedef _STL::pair<const TreeKey00286693,TreeMapped00286693> TreePair00286693;
typedef _STL::_Rb_tree<TreeKey00286693,TreePair00286693,_STL::_Select1st<TreePair00286693>,_STL::less<TreeKey00286693>,_STL::allocator<TreePair00286693> > Tree00286693;
namespace _STL { template<> Tree00286693::_Link_type Tree00286693::_M_create_node(const TreePair00286693 &); }
struct TreeCreateAccess : Tree00286693 { using Tree00286693::_M_create_node; };
struct Rva0028688AKey {
	char value[20];
};
struct Rva0028688ANode {
	int _c0;
	Rva0028688ANode *_parent;
	Rva0028688ANode *_left;
	Rva0028688ANode *_right;
	Rva0028688AKey _key;
};

struct Rva0028688AIter {
	Rva0028688ANode *node;
};
struct Rva00286E33Result { Rva0028688ANode *node; bool inserted; Rva00286E33Result(Rva0028688AIter it,bool b):node(it.node),inserted(b){} };
struct Rva0028688A {
	Rva0028688ANode *_head;
	int _size;
	__declspec(noinline) Rva0028688AIter rva0028688A(Rva0028688ANode *x, Rva0028688ANode *y, const Rva0028688AKey &v, Rva0028688ANode *w);
 Rva00286E33Result rva00286E33(const Rva0028688AKey &);
};
Rva0028688AIter Rva0028688A::rva0028688A(Rva0028688ANode *x, Rva0028688ANode *y, const Rva0028688AKey &v, Rva0028688ANode *w)
{
	Rva0028688ANode *z;
	if (y == _head || (w == 0 && (x != 0 || reinterpret_cast<const Rva00285672 &>(v).rva00285672(reinterpret_cast<const Rva00285672 &>(y->_key))))) {
		z = reinterpret_cast<Rva0028688ANode *>(reinterpret_cast<TreeCreateAccess *>(this)->_M_create_node(reinterpret_cast<const TreePair00286693 &>(v)));
		y->_left = z;
		if (y == _head) {
			_head->_parent = z;
			_head->_right = z;
		} else if (y == _head->_left) {
			_head->_left = z;
		}
	} else {
		z = reinterpret_cast<Rva0028688ANode *>(reinterpret_cast<TreeCreateAccess *>(this)->_M_create_node(reinterpret_cast<const TreePair00286693 &>(v)));
		y->_right = z;
		if (y == _head->_right) {
			_head->_right = z;
		}
	}
	z->_parent = y;
	z->_left = 0;
	z->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)z, (_STL::_Rb_tree_node_base *&)_head->_parent);
	++_size;
	Rva0028688AIter it;
	it.node = z;
	return it;
}

Rva00286E33Result Rva0028688A::rva00286E33(const Rva0028688AKey &value) {
 Rva0028688ANode *header=_head;
 Rva0028688ANode *y=header;
 Rva0028688ANode *x=header->_parent;
 bool comp=true;
 while(x!=0) {
  y=x;
  comp=reinterpret_cast<const Rva00285672 &>(value).rva00285672(reinterpret_cast<const Rva00285672 &>(x->_key));
  x=comp?x->_left:x->_right;
 }
 Rva0028688AIter j={y};
 if(comp && j.node==header->_left) return Rva00286E33Result(rva0028688A(y,y,value,x),true);
 if(comp) j.node=reinterpret_cast<Rva0028688ANode *>(_STL::_Rb_global<bool>::_M_decrement(reinterpret_cast<_STL::_Rb_tree_node_base *>(j.node)));
 if(reinterpret_cast<const Rva00285672 &>(j.node->_key).rva00285672(reinterpret_cast<const Rva00285672 &>(value))) return Rva00286E33Result(rva0028688A(x,y,value,0),true);
 return Rva00286E33Result(j,false);
}
