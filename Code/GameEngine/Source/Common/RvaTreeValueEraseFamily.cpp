// cl: /EHs /MD
//
// STLport red-black tree node erases that destroy each node's value, with the
// shape of the rowed BfmeSubEBD::bfmeEraseSubtree (53 bytes: erase the right
// subtree, destroy the value at node+0x10, free the node, walk left), plus each
// tree's 41-byte clear. Found by searching .text for those shapes with call
// displacements masked. Each erase calls only itself, one rowed value
// destructor and free (0x00030830). The value destructor gives the node's value
// type; the tree itself is not recovered, so owners are named after their erase.

extern "C" void __cdecl free(void *block);

class AsciiString;
class AudioEventRTS;
class LocomotorTemplate;
class TextureClass;
struct TreeHintRef00217D4C;
enum LocomotorSetType { RvaTreeValueEraseLocomotorSetTypeUnused };
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector;
template <class T1, class T2> struct pair { ~pair(); };
}
template <class T> class RefCountPtr { public: ~RefCountPtr(); };
class Rva00217A37;
class Rva0022115A;
class Rva003ED68D;
class Rva0041090E;
class Rva005B3751;
template <class T> class StringBase
{
	friend class Rva00217A37;
	friend class Rva0022115A;
	friend class Rva003ED68D;
	friend class Rva0041090E;
	friend class Rva005B3751;
	~StringBase();
};

struct RvaTreeValueNode
{
	unsigned int color;
	RvaTreeValueNode *parent, *left, *right;
};

struct RvaTreeValueHead
{
	char m_pad00[4]; // +0x00
	RvaTreeValueNode *m_first; // +0x04
	RvaTreeValueHead *m_next; // +0x08
	RvaTreeValueHead *m_child; // +0x0C
};

// owner Rva00079A0C: erase 0x00079A0C (value ??1?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@QAE@XZ), clear 0x00079C8D
typedef _STL::pair<const LocomotorSetType, _STL::vector<const LocomotorTemplate *, _STL::allocator<const LocomotorTemplate *> > > Rva00079A0CValue;
class Rva00079A0C
{
public:
	void rva00079A0C(void *node);
	void rva00079C8D();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00079A0C::rva00079A0C(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00079A0C(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00079A0CValue *>(node + 1)->~Rva00079A0CValue();
		free(node);
		node = left;
	}
}

void Rva00079A0C::rva00079C8D()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00079A0C(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

class CameraMarker { public: ~CameraMarker(); };

// owner Rva001363CC: erase 0x001363CC (value ??1CameraMarker@@QAE@XZ), clear 0x001364CE
typedef CameraMarker Rva001363CCValue;
class Rva001363CC
{
public:
	void rva001363CC(void *node);
	void rva001364CE();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva001363CC::rva001363CC(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva001363CC(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva001363CCValue *>(node + 1)->~Rva001363CCValue();
		free(node);
		node = left;
	}
}

void Rva001363CC::rva001364CE()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva001363CC(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00170AE4: erase 0x00170AE4 (value ??1?$RefCountPtr@VTextureClass@@@@QAE@XZ), clear 0x00170BAD
typedef RefCountPtr<TextureClass> Rva00170AE4Value;
class Rva00170AE4
{
public:
	void rva00170AE4(void *node);
	void rva00170BAD();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00170AE4::rva00170AE4(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00170AE4(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00170AE4Value *>(node + 1)->~Rva00170AE4Value();
		free(node);
		node = left;
	}
}

void Rva00170AE4::rva00170BAD()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00170AE4(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

class Rva00170EBC
{
public:
	void rva00170EBC(bool b);
private:
	char _pad00[8]; // +0x00
	Rva00170AE4 _tree; // +0x08
	char _pad10[12]; // +0x10
	bool _1c; // +0x1C
	bool _1d; // +0x1D
};

void Rva00170EBC::rva00170EBC(bool b)
{
	_tree.rva00170BAD();
	_1c = true;
	_1d = b;
}

class Rva00151DAB
{
public:
	~Rva00151DAB();
	unsigned int _key;
	unsigned int _pad;
};

class Rva00170999;

namespace _STL
{
template <> class allocator<char>
{
public:
	static char *allocate(unsigned int n, const void *hint);
};
template <class _T1, class _T2> void _Construct(_T1 *__p, const _T2 &__val);
struct _Rb_tree_node_base {};
template <class _D> class _Rb_global
{
public:
	static void _Rebalance(_Rb_tree_node_base *__x, _Rb_tree_node_base *&__root);
};
}

struct Rva00170B19Node
{
	unsigned int _color;
	Rva00170B19Node *_parent;
	Rva00170B19Node *_left;
	Rva00170B19Node *_right;
	Rva00151DAB _val;
};

// owner Rva00170B19: erase 0x00170B19 (value ??1Rva00151DAB@@QAE@XZ), clear 0x00170BD6
typedef Rva00151DAB Rva00170B19Value;
class Rva00170B19
{
public:
	void rva00170B19(void *node);
	void rva00170BD6();
	void *rva00170B70(const Rva00151DAB &x);
	void rva00170C87(void **out, Rva00170B19Node *x, Rva00170B19Node *y, const Rva00151DAB &v, Rva00170B19Node *w);
private:
	Rva00170B19Node *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00170B19::rva00170B19(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00170B19(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00170B19Value *>(node + 1)->~Rva00170B19Value();
		free(node);
		node = left;
	}
}

void Rva00170B19::rva00170BD6()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00170B19(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

void *Rva00170B19::rva00170B70(const Rva00151DAB &x)
{
	char *block = _STL::allocator<char>::allocate(0x18, 0);
	_STL::_Construct((Rva00151DAB *)(block + 0x10), x);
	return block;
}

void Rva00170B19::rva00170C87(void **out, Rva00170B19Node *x, Rva00170B19Node *y, const Rva00151DAB &v, Rva00170B19Node *w)
{
	Rva00170B19Node *z;
	if (y == m_00Head || (w == 0 && (x != 0 || v._key < ((Rva00151DAB *)((char *)y + 0x10))->_key))) {
		z = (Rva00170B19Node *)rva00170B70(v);
		y->_left = z;
		if (y == m_00Head) {
			m_00Head->_parent = z;
			m_00Head->_right = z;
		} else if (y == m_00Head->_left) {
			m_00Head->_left = z;
		}
	} else {
		z = (Rva00170B19Node *)rva00170B70(v);
		y->_right = z;
		if (y == m_00Head->_right) {
			m_00Head->_right = z;
		}
	}
	z->_parent = y;
	z->_left = 0;
	z->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)z, (_STL::_Rb_tree_node_base *&)m_00Head->_parent);
	++m_04Flag;
	*out = z;
}

// ?Rva00170B4EBuynode@@YGPAXABVRva00170999@@@Z 34B @0x00170B4E: tree node buy allocating 0x24 via rowed stlport byte allocator plus rowed _Construct of Rva00170999 at +0x10. Same shape as sibling rva00170B70 (0x18 for Rva00151DAB). Evidence: callers at 0x00170C27 0x00170C40 in 0x00170BFF plus rowed callees.
void *__stdcall Rva00170B4EBuynode(const Rva00170999 &x)
{
	char *block = _STL::allocator<char>::allocate(0x24, 0);
	_STL::_Construct((Rva00170999 *)(block + 0x10), x);
	return block;
}

class Rva0027EA49 { public: ~Rva0027EA49(); };

// owner Rva002177CD: erase 0x002177CD (value ??1Rva0027EA49@@QAE@XZ), clear 0x002179D9
typedef Rva0027EA49 Rva002177CDValue;
class Rva002177CD
{
public:
	void rva002177CD(void *node);
	void rva002179D9();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva002177CD::rva002177CD(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva002177CD(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva002177CDValue *>(node + 1)->~Rva002177CDValue();
		free(node);
		node = left;
	}
}

void Rva002177CD::rva002179D9()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva002177CD(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00217A02: erase 0x00217A02 (value ??1?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@_STL@@QAE@XZ), clear 0x00217C66
typedef _STL::pair<const AsciiString, TreeHintRef00217D4C> Rva00217A02Value;
class Rva00217A02
{
public:
	void rva00217A02(void *node);
	void rva00217C66();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00217A02::rva00217A02(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00217A02(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00217A02Value *>(node + 1)->~Rva00217A02Value();
		free(node);
		node = left;
	}
}

void Rva00217A02::rva00217C66()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00217A02(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00217A37: erase 0x00217A37 (value ??1?$StringBase@D@@AAE@XZ), clear 0x00217C8F
typedef StringBase<char> Rva00217A37Value;
class Rva00217A37
{
public:
	void rva00217A37(void *node);
	void rva00217C8F();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00217A37::rva00217A37(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00217A37(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00217A37Value *>(node + 1)->~Rva00217A37Value();
		free(node);
		node = left;
	}
}

void Rva00217A37::rva00217C8F()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00217A37(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0022115A: erase 0x0022115A (value ??1?$StringBase@D@@AAE@XZ), clear 0x00221234
typedef StringBase<char> Rva0022115AValue;
class Rva0022115A
{
public:
	void rva0022115A(void *node);
	void rva00221234();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0022115A::rva0022115A(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva0022115A(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva0022115AValue *>(node + 1)->~Rva0022115AValue();
		free(node);
		node = left;
	}
}

void Rva0022115A::rva00221234()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva0022115A(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

class Rva0022DDF4 { public: ~Rva0022DDF4(); };

// owner Rva0022E121: erase 0x0022E121 (value ??1Rva0022DDF4@@QAE@XZ), clear 0x0022E177
typedef Rva0022DDF4 Rva0022E121Value;
class Rva0022E121
{
public:
	void rva0022E121(void *node);
	void rva0022E177();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0022E121::rva0022E121(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva0022E121(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva0022E121Value *>(node + 1)->~Rva0022E121Value();
		free(node);
		node = left;
	}
}

void Rva0022E121::rva0022E177()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva0022E121(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00240CAB: erase 0x00240CAB (value ??1CameraMarker@@QAE@XZ), clear 0x0024191A
typedef CameraMarker Rva00240CABValue;
class Rva00240CAB
{
public:
	void rva00240CAB(void *node);
	void rva0024191A();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00240CAB::rva00240CAB(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00240CAB(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00240CABValue *>(node + 1)->~Rva00240CABValue();
		free(node);
		node = left;
	}
}

void Rva00240CAB::rva0024191A()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00240CAB(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva002A4281: erase 0x002A4281 (value ??1?$pair@VAsciiString@@VAudioEventRTS@@@_STL@@QAE@XZ), clear 0x002A47E1
typedef _STL::pair<AsciiString, AudioEventRTS> Rva002A4281Value;
class Rva002A4281
{
public:
	void rva002A4281(void *node);
	void rva002A47E1();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva002A4281::rva002A4281(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva002A4281(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva002A4281Value *>(node + 1)->~Rva002A4281Value();
		free(node);
		node = left;
	}
}

void Rva002A4281::rva002A47E1()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva002A4281(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva003ED68D: erase 0x003ED68D (value ??1?$StringBase@D@@AAE@XZ), clear 0x003ED6E4
typedef StringBase<char> Rva003ED68DValue;
class Rva003ED68D
{
public:
	void rva003ED68D(void *node);
	void rva003ED6E4();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva003ED68D::rva003ED68D(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva003ED68D(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva003ED68DValue *>(node + 1)->~Rva003ED68DValue();
		free(node);
		node = left;
	}
}

void Rva003ED68D::rva003ED6E4()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva003ED68D(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva0041090E: erase 0x0041090E (value ??1?$StringBase@D@@AAE@XZ), clear 0x00410A14
typedef StringBase<char> Rva0041090EValue;
class Rva0041090E
{
public:
	void rva0041090E(void *node);
	void rva00410A14();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0041090E::rva0041090E(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva0041090E(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva0041090EValue *>(node + 1)->~Rva0041090EValue();
		free(node);
		node = left;
	}
}

void Rva0041090E::rva00410A14()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva0041090E(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00463782: erase 0x00463782 (value ??1CameraMarker@@QAE@XZ), clear 0x00463D72
typedef CameraMarker Rva00463782Value;
class Rva00463782
{
public:
	void rva00463782(void *node);
	void rva00463D72();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00463782::rva00463782(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00463782(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00463782Value *>(node + 1)->~Rva00463782Value();
		free(node);
		node = left;
	}
}

void Rva00463782::rva00463D72()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00463782(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva005B3751: erase 0x005B3751 (value ??1?$StringBase@D@@AAE@XZ), clear 0x005B3947
typedef StringBase<char> Rva005B3751Value;
class Rva005B3751
{
public:
	void rva005B3751(void *node);
	void rva005B3947();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva005B3751::rva005B3751(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva005B3751(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva005B3751Value *>(node + 1)->~Rva005B3751Value();
		free(node);
		node = left;
	}
}

void Rva005B3751::rva005B3947()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva005B3751(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// Trees whose node value is a pair with a container second member at +4: the
// value destructor is an 8-byte thunk (add ecx,4; jmp to the container's rowed
// destructor), landed here as a placeholder pair whose empty destructor
// tail-calls the member's. The key at +0 is not identified.

class Rva0032BE80 { public: ~Rva0032BE80(); };

// ??1Rva0032C2F7@@QAE@XZ @0x0032C2F7 8B: pair value, second member Rva0032BE80 at +4
struct Rva0032C2F7
{
	int m_first;
	Rva0032BE80 m_second;
	~Rva0032C2F7();
};

Rva0032C2F7::~Rva0032C2F7()
{
}

// owner Rva0032D3D3: erase 0x0032D3D3, clear 0x0032DCB7
class Rva0032D3D3
{
public:
	void rva0032D3D3(void *node);
	void rva0032DCB7();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0032D3D3::rva0032D3D3(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva0032D3D3(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva0032C2F7 *>(node + 1)->~Rva0032C2F7();
		free(node);
		node = left;
	}
}

void Rva0032D3D3::rva0032DCB7()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva0032D3D3(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

class Rva004FF582 { public: ~Rva004FF582(); };

// ??1Rva004FFE39@@QAE@XZ @0x004FFE39 8B: pair value, second member Rva004FF582 at +4
struct Rva004FFE39
{
	int m_first;
	Rva004FF582 m_second;
	~Rva004FFE39();
};

Rva004FFE39::~Rva004FFE39()
{
}

// owner Rva005007CF: erase 0x005007CF, clear 0x00500AA6
class Rva005007CF
{
public:
	void rva005007CF(void *node);
	void rva00500AA6();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva005007CF::rva005007CF(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva005007CF(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva004FFE39 *>(node + 1)->~Rva004FFE39();
		free(node);
		node = left;
	}
}

void Rva005007CF::rva00500AA6()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva005007CF(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

class Rva00053DC5 { public: ~Rva00053DC5(); };

// ??1Rva005344C0@@QAE@XZ @0x005344C0 8B: pair value, second member Rva00053DC5 at +4
struct Rva005344C0
{
	int m_first;
	Rva00053DC5 m_second;
	~Rva005344C0();
};

Rva005344C0::~Rva005344C0()
{
}

// owner Rva00534641: erase 0x00534641, clear 0x00534693
class Image;
class ImageSubscriptMap;

class Rva00534641
{
public:
	void rva00534641(void *node);
	void rva00534693();
	ImageSubscriptMap *rva00534A2A(const unsigned int &key);
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00534641::rva00534641(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00534641(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva005344C0 *>(node + 1)->~Rva005344C0();
		free(node);
		node = left;
	}
}

void Rva00534641::rva00534693()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00534641(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
};

struct Rva00534AAENode
{
	Rva00534AAENode *m_next;
	Rva00534AAENode *m_previous;
	unsigned int m_outerKey;
	unsigned int m_innerKey;
};

class Rva00534AAE
{
public:
	void rva00534AAE();

private:
	Rva00534AAENode *m_head;
	Rva00534641 m_map;
	unsigned int m_0C;
	bool m_needsRebuild;
};

void Rva00534AAE::rva00534AAE()
{
	if (!m_needsRebuild)
		return;

	m_map.rva00534693();
	unsigned int index = 0;
	for (Rva00534AAENode *node = m_head->m_next; node != m_head; node = node->m_next) {
		unsigned int innerKey = node->m_innerKey;
		unsigned int outerKey = node->m_outerKey;
		m_map.rva00534A2A(outerKey)->operator[](innerKey) = reinterpret_cast<Image *>(index++);
	}
	m_needsRebuild = false;
}

class Rva006007A5 { public: ~Rva006007A5(); };

// ??1Rva00600BBE@@QAE@XZ @0x00600BBE 8B: pair value, second member Rva006007A5 at +4
struct Rva00600BBE
{
	int m_first;
	Rva006007A5 m_second;
	~Rva00600BBE();
};

Rva00600BBE::~Rva00600BBE()
{
}

// owner Rva0060126D: erase 0x0060126D, clear 0x006012C4
class Rva0060126D
{
public:
	void rva0060126D(void *node);
	void rva006012C4();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva0060126D::rva0060126D(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva0060126D(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva00600BBE *>(node + 1)->~Rva00600BBE();
		free(node);
		node = left;
	}
}

void Rva0060126D::rva006012C4()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva0060126D(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

// owner Rva00500804: erase 0x00500804 (value ??1Rva004FFE89@@QAE@XZ), clear 0x00500ACF
struct Rva004FFE89
{
	~Rva004FFE89();
};
class Rva00500804
{
public:
	void rva00500804(void *node);
	void rva00500ACF();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00500804::rva00500804(void *p)
{
	RvaTreeValueNode *node = (RvaTreeValueNode *)p;
	while (node) {
		rva00500804(node->right);
		RvaTreeValueNode *left = node->left;
		reinterpret_cast<Rva004FFE89 *>(node + 1)->~Rva004FFE89();
		free(node);
		node = left;
	}
}

void Rva00500804::rva00500ACF()
{
	if (m_04Flag == 0)
		return;
	RvaTreeValueHead *h = (RvaTreeValueHead *)m_00Head;
	rva00500804(h->m_first);
	((RvaTreeValueHead *)m_00Head)->m_next = (RvaTreeValueHead *)m_00Head;
	((RvaTreeValueHead *)m_00Head)->m_first = 0;
	((RvaTreeValueHead *)m_00Head)->m_child = (RvaTreeValueHead *)m_00Head;
	m_04Flag = 0;
}

class Rva004FFE34
{
public:
	void rva004FFE34();
};

void Rva004FFE34::rva004FFE34()
{
	((Rva004FF582 *)this)->~Rva004FF582();
}

class Rva002A1D02
{
public:
	~Rva002A1D02();
};

class Rva002A4636
{
public:
	void rva002A4636();
};

void Rva002A4636::rva002A4636()
{
	((Rva002A1D02 *)this)->~Rva002A1D02();
}

struct Rva002A3F5BRecord;
namespace _STL
{
template <class T> struct _Select1st;
template <class T> struct less;
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree
{
public:
	~_Rb_tree();
};
typedef _Rb_tree<int, pair<const int, Rva002A3F5BRecord>, _Select1st<pair<const int, Rva002A3F5BRecord> >, less<int>, allocator<pair<const int, Rva002A3F5BRecord> > > Rva002A3F5BTree;
}

class Rva002A4631
{
public:
	void rva002A4631();
};

void Rva002A4631::rva002A4631()
{
	((_STL::Rva002A3F5BTree *)this)->~_Rb_tree();
}

class Rva00136605
{
public:
	void rva00136605();
};

void Rva00136605::rva00136605()
{
	((Rva001363CC *)this)->rva001364CE();
}

class Rva00170D42
{
public:
	void rva00170D42();
};

void Rva00170D42::rva00170D42()
{
	((Rva00170AE4 *)this)->rva00170BAD();
}

class Rva00242EAA
{
public:
	void rva00242EAA();
};

void Rva00242EAA::rva00242EAA()
{
	((Rva00240CAB *)this)->rva0024191A();
}

class Rva002A5839
{
public:
	void rva002A5839();
};

void Rva002A5839::rva002A5839()
{
	((Rva002A4281 *)this)->rva002A47E1();
}

class Rva0032E4DE
{
public:
	void rva0032E4DE();
};

void Rva0032E4DE::rva0032E4DE()
{
	((Rva0032D3D3 *)this)->rva0032DCB7();
}

class Rva00410CB4
{
public:
	void rva00410CB4();
};

void Rva00410CB4::rva00410CB4()
{
	((Rva0041090E *)this)->rva00410A14();
}

class Rva00500D2B
{
public:
	void rva00500D2B();
};

void Rva00500D2B::rva00500D2B()
{
	((Rva005007CF *)this)->rva00500AA6();
}

class Rva00500E00
{
public:
	void rva00500E00();
};

void Rva00500E00::rva00500E00()
{
	((Rva00500804 *)this)->rva00500ACF();
}

class Rva00534706
{
public:
	void rva00534706();
};

void Rva00534706::rva00534706()
{
	((Rva00534641 *)this)->rva00534693();
}

class Rva005B3C8C
{
public:
	void rva005B3C8C();
};

void Rva005B3C8C::rva005B3C8C()
{
	((Rva005B3751 *)this)->rva005B3947();
}
