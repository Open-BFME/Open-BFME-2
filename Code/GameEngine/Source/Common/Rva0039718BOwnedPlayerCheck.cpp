// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva0039718B@Rva0039718B@@QAE_NPAVPlayer@@@Z @0x0039718B 52B: true when the
// given player is our controlling player and its +0x94 field is at least our
// pinned 0x003970E7 lookup on it (unsigned: retail booleanizes the compare
// with cmp/sbb/inc, which is >=, not ==). Evidence: m08 feeds the rowed
// Object::getControllingPlayer at 0x0028AFA9, twin early-false guards share
// one xor-al block ahead of the check, f94 hoisted into edi across the call,
// sbb/inc booleanize; decls follow neighbouring Rva00396B25Receiver.cpp /
// Rva00396B0DForward.cpp. /O1 and two separate early-false guards give
// retail's layout.

#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	char m_pad00[0x58];
	AsciiString m_name58; // target reads the player's name at +0x58
	char m_pad5C[0x38];
	int m_field94;
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class Rva0039718B
{
public:
	bool rva0039718B(Player *player);
	int rva003970E7(Player *player);

private:
	char m_vtable00[4];
	struct Rva0039718BInner *m_inner04;
	Object *m_object08;
};

namespace _STL
{
template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
	pair(const pair &);
};

template <class P>
struct _Select1st
{
};

template <class T>
struct less
{
};

template <class T>
class allocator
{
};

struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V _M_value_field;
};

template <class K, class V, class KoV, class Cmp, class Al>
class _Rb_tree
{
public:
	_Rb_tree_node_base *m_header;
	unsigned int m_count;

private:
	template <class Q>
	_Rb_tree_node<V> *_M_find(const Q &) const;
	friend class ::Rva0039718B;
};
}

typedef _STL::pair<const int, int> Rva0039718BPair;
typedef _STL::_Rb_tree<int, Rva0039718BPair, _STL::_Select1st<Rva0039718BPair>,
	_STL::less<int>, _STL::allocator<Rva0039718BPair> > Rva0039718BTree;
typedef _STL::_Rb_tree_node<Rva0039718BPair> Rva0039718BNode;

struct Rva0039718BInner
{
	char m_pad00[0x68];
	Rva0039718BTree m_tree68;
};

class Rva002A7461
{
public:
	int rva002A7548(int unused);
};

// Target evidence: the 164-byte entry at 0x003970E7 copies Player+0x58,
// returns zero for a null or empty name and for a tree miss, then reads the
// found node at +0x18/+0x1c. The tree is reached through this+0x04 at inner
// +0x68; its int-key NameKey lookup and header layout follow the independently
// matched Rva003973EB name-tree reader. The compared Player+0x60 query and its
// callee are pinned at 0x002A7548.
int Rva0039718B::rva003970E7(Player *player)
{
	if (player == 0)
		return 0;

	AsciiString name(player->m_name58);
	if (name.isEmpty())
		return 0;

	int key = TheNameKeyGenerator->nameToKey(name);
	Rva0039718BInner *inner = m_inner04;
	Rva0039718BNode *found = inner->m_tree68._M_find(key);
	if (found != (Rva0039718BNode *)inner->m_tree68.m_header)
	{
		int *entry = (int *)found;
		int limit = entry[7];
		if (limit > 0 && ((Rva002A7461 *)((char *)player + 0x60))->rva002A7548(0) < limit)
			return 0x05f5e0ff;
		return entry[6];
	}
	return 0;
}

bool Rva0039718B::rva0039718B(Player *player)
{
	Player *ours = m_object08->getControllingPlayer();
	if (player == 0)
		return false;
	if (ours != player)
		return false;
	unsigned int f94 = player->m_field94;
	return f94 >= (unsigned int)rva003970E7(player);
}
