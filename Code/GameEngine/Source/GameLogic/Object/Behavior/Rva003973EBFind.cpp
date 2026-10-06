// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// ?rva003973EB@Rva003973EB@@QAE_NPAVPlayer@@H@Z @0x003973EB 62B: true when
// the player's name keys into the +0x68 int tree, range-17 dump lane.
// Evidence: direct member read of the tree count at +0x6C (unsigned compare),
// TheNameKeyGenerator nameToKey on Player+0x58 through rowed 0x0009FA65
// into the dead arg slot, then the rowed map<int,int> _M_find 0x00388F63
// compared against the tree header for the booleanize. Second arg dead.
// Tree and find idiom follow Rva0028951FFind.cpp; the key temp is int so the
// member-template deduces the rowed H instantiation.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	char m_pad00[0x58];
	AsciiString m_name58; // +0x58
};

class Rva003973EB;

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
	friend class ::Rva003973EB;
};

}

typedef _STL::pair<const int, int> Rva003973EBPair;
typedef _STL::_Rb_tree<int, Rva003973EBPair, _STL::_Select1st<Rva003973EBPair>, _STL::less<int>, _STL::allocator<Rva003973EBPair> > Rva003973EBTree;
typedef _STL::_Rb_tree_node<Rva003973EBPair> Rva003973EBNode;

struct Rva003973EBInner
{
	char m_pad00[0x68];
	Rva003973EBTree m_tree68; // +0x68
};

class Rva003973EB
{
public:
	bool rva003973EB(Player *p, int /*unused*/);

private:
	char m_pad00[4];
	Rva003973EBInner *m_inner04; // +0x04
};

// ?rva003973EB@Rva003973EB@@QAE_NPAVPlayer@@H@Z
bool Rva003973EB::rva003973EB(Player *p, int /*unused*/)
{
	Rva003973EBInner *inner = m_inner04;
	if (inner->m_tree68.m_count <= 0)
		return false;
	int key = TheNameKeyGenerator->nameToKey(p->m_name58);
	Rva003973EBNode *found = inner->m_tree68._M_find(key);
	bool ok = (found != (Rva003973EBNode *)inner->m_tree68.m_header);
	return ok;
}
