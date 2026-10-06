// cl: /EHs /MD
//
// ?rva00170BFF@Rva00170BFF@@QAEXPAPAXPAURva00170BFFNode@@1ABVRva00170999@@1@Z @0x00170BFF 136B.
//
// STLport red-black tree _M_insert of the Rva00170BFF tree (node 0x24: the
// 0x10-byte rb-tree header plus a 0x14-byte Rva00170999 value at +0x10). It is
// the sibling of the rowed Rva00170B19::rva00170C87 at 0x00170C87 (same 136-byte
// shape) and of the rowed node-buy body at 0x00170B4E, both in
// RvaTreeValueEraseFamily.cpp; this file carries only the insert so the tree's
// three bodies stay separable.
//
// Retail evidence:
//   0x00170C05 push ebx / mov ebx,[ebp+0x10] / push esi / push edi / mov edi,ecx
//   0x00170C0D cmp ebx,[edi]            head test, je to the right-side arm
//   0x00170C11 cmp [ebp+0x18],0         the w==0 test
//   0x00170C17 cmp [ebp+0xc],0          the x!=0 test
//   0x00170C1D mov ecx,[eax] / cmp ecx,[ebx+0x10] / jb   key compare, unsigned
//   0x00170C24 push eax / mov ecx,edi / call 0x00170B4E  the node buy, THISCALL
//   0x00170C3D push eax / mov ecx,edi / call 0x00170B4E  again on the right arm
//   then parent/left/right wiring, _Rb_global<bool>::_Rebalance, ++m_04Flag,
//   *out = z.
// Callers at 0x00170E6B pass mov ecx,edi into this insert, which is what fixes
// the tree as a member of thiscall shape rather than a free function.
//
// The buy at 0x00170B4E is reached through ecx here. Its own 34-byte body ends
// `ret 4`, so it cleans the one stack argument and takes no ECX parameter;
// the caller's `mov ecx,edi` is a this-save it does not consume. That is why
// the sibling row at 0x00170B4E is spelled as a free __stdcall
// (Rva00170B4EBuynode) while this file declares it as a member of this class:
// the member spelling is what reproduces retail's `push eax / mov ecx,edi /
// call` pair, and the byte-identical body is reached through the pin below.
//
// Key type: the compare reads the value's first dword only, so the node models
// the payload as bytes and casts explicitly rather than inventing a member.
// Rva00170999 and the tree owner are not established beyond that, so the
// honest address-derived names stand.
extern "C" void __cdecl free(void *block);

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
template <class T> class allocator;
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

struct Rva00170BFFNode
{
	unsigned int _color;
	Rva00170BFFNode *_parent;
	Rva00170BFFNode *_left;
	Rva00170BFFNode *_right;
	char _val10[0x14]; // Rva00170999 at +0x10 (AssetReference plus 16B data)
};

class Rva00170BFF
{
public:
	void *rva00170B4E(const Rva00170999 &x);
	void rva00170BFF(void **out, Rva00170BFFNode *x, Rva00170BFFNode *y, const Rva00170999 &v, Rva00170BFFNode *w);
private:
	Rva00170BFFNode *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

// Bind the member spelling to the address already rowed under the free
// __stdcall name. The body is byte-identical either way (its own `ret 4` shows
// it consumes no ECX parameter); only the caller's `mov ecx,edi` distinguishes
// them, and retail emits it at both buy call sites in this insert. The body
// itself stays in RvaTreeValueEraseFamily.cpp, which already rows that address.
#pragma comment(linker, "/alternatename:?rva00170B4E@Rva00170BFF@@QAEPAXABVRva00170999@@@Z=?Rva00170B4EBuynode@@YGPAXABVRva00170999@@@Z")

void Rva00170BFF::rva00170BFF(void **out, Rva00170BFFNode *x, Rva00170BFFNode *y, const Rva00170999 &v, Rva00170BFFNode *w)
{
	Rva00170BFFNode *z;
	if (y == m_00Head || (w == 0 && (x != 0 || *(const unsigned int *)&v < *(const unsigned int *)y->_val10))) {
		z = (Rva00170BFFNode *)rva00170B4E(v);
		y->_left = z;
		if (y == m_00Head) {
			m_00Head->_parent = z;
			m_00Head->_right = z;
		} else if (y == m_00Head->_left) {
			m_00Head->_left = z;
		}
	} else {
		z = (Rva00170BFFNode *)rva00170B4E(v);
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