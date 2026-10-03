// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004CA167@AnimationSoundTree@@QAEXPAX@Z, retail 0x004CA167, 53 bytes.
// AnimationSoundTree node free helper: if the node is null returns; otherwise
// recurses on the child at +0x0C with the same tree, saves the sibling at +8,
// runs the rowed ??1Rva002390CB at 0x004C9F38 on the payload at +0x10, frees
// the node through the rowed _free at 0x00030830, then advances to the saved
// sibling until null. The tree itself (header at +0 plus count at +4) is only
// threaded through for the recursion, matching retail's preserved ebx.
// Evidence: callees all rowed (plus self); callers at 0x004CA179 (self) and
// 0x004CA278 in FUN_008CA26A (tree clear checking count at +4); prev/next
// after ??0Rva004C9FBF / ??0Rva004CA125 with the same // cl: line.

class Rva002390CB
{
public:
	~Rva002390CB();
};

extern "C" void free(void *);

namespace _STL
{
extern "C" void __cdecl free(void *block) throw(...);
template <class _Tp> class allocator
{
public:
	static _Tp *allocate(unsigned int __n, void const *__hint);
};
template <class _P, class _T, class _A> class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const _A &__a, _P __p);
	_P _M_data;
};
}

inline void *__cdecl operator new(unsigned int, void *__p)
{
	return __p;
}

typedef unsigned int ProxyUInt;

class Rva004C9D93Cmp
{
public:
	bool rva004C9D93Compare(void *a, void *b) const;
};

namespace _STL
{
struct _Rb_tree_node_base
{
};
template <class _Dummy> class _Rb_global
{
public:
	static void _Rebalance(_Rb_tree_node_base *__x, _Rb_tree_node_base *&__root);
};
}

struct AnimationSoundTreeNode
{
	int m_color;
	AnimationSoundTreeNode *m_parent;
	AnimationSoundTreeNode *m_left;
	AnimationSoundTreeNode *m_right;
};

struct AnimationSoundTreeHead
{
	int m_color;
	AnimationSoundTreeNode *m_parent;
	AnimationSoundTreeHead *m_left;
	AnimationSoundTreeHead *m_right;
};

class AnimationSoundTreeHeaderHandle
{
public:
	~AnimationSoundTreeHeaderHandle()
	{
		if (m_header)
			_STL::free(m_header);
	}

	void *m_header;
};

class AnimationSoundTree
{
public:
	~AnimationSoundTree();
	void rva004CA167(void *node);
	void rva004CA26A();
	AnimationSoundTree *rva004CA018(void const *dummy);
	AnimationSoundTree *rva004CA13D(void const *d1, void const *d2);
	void *rva004CA19C(void const *v);
	void rva004CA293(
		AnimationSoundTreeNode *&out,
		AnimationSoundTreeNode *a,
		AnimationSoundTreeNode *b,
		void const *v,
		AnimationSoundTreeNode *c);
	AnimationSoundTreeNode **rva004CA68B(AnimationSoundTreeNode **out, void const *v);

private:
	AnimationSoundTreeHeaderHandle m_handle;
	unsigned int m_count;
	Rva004C9D93Cmp m_compare;
};

void AnimationSoundTree::rva004CA167(void *nodeIn)
{
	if (!nodeIn)
		return;
	char *cur = (char *)nodeIn;
	do
	{
		char *child = *(char **)(cur + 0x0C);
		rva004CA167(child);
		char *next = *(char **)(cur + 8);
		((Rva002390CB *)(cur + 0x10))->~Rva002390CB();
		free(cur);
		cur = next;
	} while (cur);
}

// ?rva004CA26A@AnimationSoundTree@@QAEXXZ, retail 0x004CA26A, 41 bytes.
// AnimationSoundTree clear: returns when the count at +4 is zero; otherwise
// frees the list at header+4 through the rowed rva004CA167 helper above,
// then repairs the 0xB8 header sentinel (self at +8 and +0x0C, zero at +4)
// and zeroes the count. Prev is the helper itself with the same // cl: line.
// Evidence: callees all rowed after 0x004CA167 landed; sole caller at
// 0x004CA668 in FUN_008CA653.

void AnimationSoundTree::rva004CA26A()
{
	if (m_count == 0)
		return;
	void *first = *(void **)((char *)m_handle.m_header + 4);
	rva004CA167(first);
	*(void **)((char *)m_handle.m_header + 8) = m_handle.m_header;
	*(unsigned int *)((char *)m_handle.m_header + 4) = 0;
	*(void **)((char *)m_handle.m_header + 0x0C) = m_handle.m_header;
	m_count = 0;
}

// ??1AnimationSoundTree@@QAE@XZ, retail 0x004CA653, 56 bytes.
// AnimationSoundTree dtor: clears via rowed rva004CA26A then frees header.
// Evidence: caller at 0x004CA780 in pinned ??1AnimationSoundClientBehaviorModuleData 0x004CA768 with ECX=this+8; layout header+0 count+4 from ctor 0x004CA6DA.
AnimationSoundTree::~AnimationSoundTree()
{
	rva004CA26A();
}

// ?rva004CA018@AnimationSoundTree@@QAEPAV1@PBX@Z, retail 0x004CA018, 39 bytes.
// Header-handle alloc helper: proxy at this with a stack uint allocator temp
// and null, then the 0xB8 header via the rowed byte allocator stored at +0,
// returning this. Called once from 0x004CA13D. Evidence: callees rowed
// 0x0014F3C4 proxy and 0x000307F0 allocate; caller at 0x004CA144;
// prev/next with the same // cl: line.
AnimationSoundTree *AnimationSoundTree::rva004CA018(void const *dummy)
{
	(void)dummy;
	_STL::allocator<ProxyUInt> tmp;
	_STL::_STLP_alloc_proxy<ProxyUInt *, ProxyUInt, _STL::allocator<ProxyUInt> > *proxy =
		(_STL::_STLP_alloc_proxy<ProxyUInt *, ProxyUInt, _STL::allocator<ProxyUInt> > *)this;
	__assume(proxy != 0);
	new (proxy) _STL::_STLP_alloc_proxy<ProxyUInt *, ProxyUInt, _STL::allocator<ProxyUInt> >(tmp, (ProxyUInt *)0);
	*(char **)this = _STL::allocator<char>::allocate(0xb8, 0);
	return this;
}

// ?rva004CA13D@AnimationSoundTree@@QAEPAV1@PBX0@Z, retail 0x004CA13D, 42 bytes.
// Header init: runs the rowed rva004CA018 alloc with the second dummy, then
// zeroes count at +4 and repairs the 0xB8 header sentinel (zero at +0/+4,
// self at +8/+0xC), returning this. Called once from the pinned ctor 0x004CA6DA.
// Evidence: callee rowed 0x004CA018; caller at 0x004CA6E9; prev/next same // cl:.
AnimationSoundTree *AnimationSoundTree::rva004CA13D(void const *d1, void const *d2)
{
	(void)d1;
	rva004CA018(d2);
	m_count = 0;
	*(char *)m_handle.m_header = 0;
	*(unsigned int *)((char *)m_handle.m_header + 4) = 0;
	*(void **)((char *)m_handle.m_header + 8) = m_handle.m_header;
	*(void **)((char *)m_handle.m_header + 0x0C) = m_handle.m_header;
	return this;
}

// ?Rva004CA048Construct@@YAXPAXABVRva004C9E94@@@Z, retail 0x004CA048, 18 bytes.
// Value copy helper for the AnimationSoundTree RB nodes: null-checks dest,
// then placement-constructs a Rva004C9E94 via its rowed copy ctor 0x004C9F76.
// Called from the node factory 0x004CA19C with dest node+0x10 and the pair.
// Evidence: callee rowed 0x004C9F76; caller at 0x004CA1B3; prev 0x004CA018
// same // cl: line.
class Rva004C9E94
{
public:
	Rva004C9E94(const Rva004C9E94 &that);
};
void __cdecl Rva004CA048Construct(void *dest, const Rva004C9E94 &src)
{
	if (!dest)
		return;
	new (dest) Rva004C9E94(src);
}

// ?rva004CA19C@AnimationSoundTree@@QAEPAXPBX@Z, retail 0x004CA19C, 37 bytes.
// Node factory for the AnimationSoundTree RB: allocates the 0xB8 node via the
// rowed byte allocator 0x000307F0, then copy-constructs the Rva004C9E94 value
// at node+0x10 through the rowed 0x004CA048 helper above, returning the node.
// Called twice from the insert helper 0x004CA293. Evidence: callees rowed
// 0x000307F0 plus 0x004CA048; callers at 0x004CA2C6 and 0x004CA2E1; prev
// 0x004CA167 same // cl: line.
void *AnimationSoundTree::rva004CA19C(void const *v)
{
	char *node = _STL::allocator<char>::allocate(0xb8, 0);
	Rva004CA048Construct(node + 0x10, *(Rva004C9E94 const *)v);
	return node;
}

// ?rva004CA293@AnimationSoundTree@@QAEXAAPAUAnimationSoundTreeNode@@PAU2@1PBX1@Z, retail 0x004CA293, 149 bytes.
// RB insert worker for the AnimationSoundTree: picks right vs left child via
// the member twin compare at +8 (lea ecx) against node+0x10, creates the 0xB8
// node through the rowed rva004CA19C factory above, threads it (rightmost at
// header+0xC vs leftmost at +8, root at +4), rebalances via rowed 0x00025490,
// bumps the count and returns the node through out. Called from 0x004CA6C6.
// Evidence: callees rowed/twinned 0x004C9D93 plus 0x004CA19C plus 0x00025490;
// caller at 0x004CA6C6; prev/next same // cl: line.
void AnimationSoundTree::rva004CA293(
	AnimationSoundTreeNode *&out,
	AnimationSoundTreeNode *a,
	AnimationSoundTreeNode *b,
	void const *v,
	AnimationSoundTreeNode *c)
{
	AnimationSoundTreeNode *node;
	if (b != (AnimationSoundTreeNode *)m_handle.m_header
		&& (c != 0
			|| (a == 0
				&& !m_compare.rva004C9D93Compare((void *)v, (char *)b + 0x10))))
	{
		node = (AnimationSoundTreeNode *)rva004CA19C(v);
		b->m_right = node;
		AnimationSoundTreeHead *root = (AnimationSoundTreeHead *)m_handle.m_header;
		if (b == (AnimationSoundTreeNode *)root->m_right)
			root->m_right = (AnimationSoundTreeHead *)node;
	}
	else
	{
		node = (AnimationSoundTreeNode *)rva004CA19C(v);
		b->m_left = node;
		AnimationSoundTreeHead *root = (AnimationSoundTreeHead *)m_handle.m_header;
		if (b == (AnimationSoundTreeNode *)root)
		{
			root->m_parent = node;
			((AnimationSoundTreeHead *)m_handle.m_header)->m_right = (AnimationSoundTreeHead *)node;
		}
		else if (b == (AnimationSoundTreeNode *)root->m_left)
			root->m_left = (AnimationSoundTreeHead *)node;
	}
	node->m_left = 0;
	node->m_right = 0;
	node->m_parent = b;
	_STL::_Rb_global<bool>::_Rebalance(
		(_STL::_Rb_tree_node_base *)node,
		(_STL::_Rb_tree_node_base *&)((AnimationSoundTreeHead *)m_handle.m_header)->m_parent);
	++m_count;
	out = node;
}

// ?rva004CA68B@AnimationSoundTree@@QAEPAPAUAnimationSoundTreeNode@@PAPAU2@PBX@Z, retail 0x004CA68B, 74 bytes.
// RB find-or-insert for the AnimationSoundTree: walk from root via the member
// twin compare at +8 (v first, node+0x10 second), left on true (+8) else right
// (+0xC), then insert through rowed rva004CA293 with out, 0, parent, v, 0 and
// return out. Layout header+0 count+4 compare+8 from siblings.
// Evidence: callees rowed 0x004C9D93 plus 0x004CA293; callers at 0x004CA6FD etc.
AnimationSoundTreeNode **AnimationSoundTree::rva004CA68B(AnimationSoundTreeNode **out, void const *v)
{
	AnimationSoundTreeNode *parent = (AnimationSoundTreeNode *)m_handle.m_header;
	AnimationSoundTreeNode *cur = ((AnimationSoundTreeHead *)parent)->m_parent;
	while (cur) {
		parent = cur;
		if (m_compare.rva004C9D93Compare((void *)v, (char *)cur + 0x10))
			cur = cur->m_left;
		else
			cur = cur->m_right;
	}
	rva004CA293((AnimationSoundTreeNode *&)*out, 0, parent, v, 0);
	return out;
}
