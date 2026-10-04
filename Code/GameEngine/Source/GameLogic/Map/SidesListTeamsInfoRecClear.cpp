// cl: /Ireference/shims/bfme2_ascii /O1
// ?clear@TeamsInfoRec@@QAEXXZ retail 0x0032C9C6 58 bytes, called and tail-jumped
// by SidesList::emptyTeams 0x0032D065 / 0x0032D071 on the two TeamsInfoRecs at
// SidesList +0xF44 / +0xF60.
//
// It empties the team vector at +0x0C by swapping it with a one-element
// temporary (vector(size_type) 0x0032BDE7, swap 0x00567ECD, the temporary's
// dtor 0x0032C3A3), clears the map at +0x00 (_Rb_tree::clear 0x0032BEBF) and
// zeroes the two shorts. Layout as SidesListTeamsInfoRecAddTeam.cpp: the vector
// holds the 16-byte BfmeThingUBB team slots (free-list links plus a Dict).
//
// The map's type, from target evidence: its _Rb_tree::clear erases through
// 0x0032B4ED, which destroys each node's value at +0x10 through 0x002046BB, a
// jump to the pair<AsciiString, AsciiString> destructor 0x0002C0C0, so the key
// is a pair of AsciiStrings and the mapped value is trivially destroyed. The
// sibling member 0x0032D103 (which fills the same map from a team's two Dict
// strings) builds its entries with make_pair<pair<AsciiString, AsciiString>,
// int> 0x002056A6 and inserts them through the pair-keyed tree whose compare
// is pair's operator< 0x00206BCF (_STL::less): map<pair<AsciiString,
// AsciiString>, int>. Only the name TeamsInfoRec carries over from Zero Hour,
// whose TeamsInfoRec is an array.
//
// The STLport containers are declared views (same decorated names as
// STLport's <map> and <vector>) so this unit calls the shared out-of-line
// bodies instead of emitting its own copies; map::clear is inline, as in
// STLport, and forwards to the tree's clear.

#include "ascii_string.h"

namespace _STL
{
template <class T> class allocator {};
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class P> struct _Select1st {};
template <class T> struct less {};

struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Value> struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value _M_value_field;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	void clear();

private:
	void _M_erase(_Rb_tree_node<Value> *x);	// 0x0032B4ED, shared

	_Rb_tree_node_base *_M_header;	// +0x00
	unsigned int _M_node_count;	// +0x04
	Compare _M_key_compare;		// +0x08
};

// STLport's _Rb_tree::clear, emitted here for its row (0x0032BEBF); defined
// out of the class body so cl /O1 keeps it a call, as retail does.
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::clear()
{
	if (_M_node_count != 0)
	{
		_M_erase((_Rb_tree_node<Value> *)_M_header->_M_parent);
		_M_header->_M_left = _M_header;
		_M_header->_M_parent = 0;
		_M_header->_M_right = _M_header;
		_M_node_count = 0;
	}
}

template <class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key, T> > >
class map
{
public:
	void clear() { m_tree.clear(); }

private:
	_Rb_tree<Key, pair<const Key, T>, _Select1st<pair<const Key, T> >, Compare, Alloc> m_tree;
};

template <class T, class Alloc = allocator<T> >
class vector
{
public:
	explicit vector(unsigned int n);
	~vector();
	void swap(vector &other) throw();	// only pointer swaps: no unwind for the temporary

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

class Dict
{
public:
	~Dict();
private:
	void *m_data;
};

class BfmeThingUBB
{
public:
	BfmeThingUBB();
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;
};

class TeamsInfoRec
{
public:
	void clear();

private:
	typedef _STL::pair<AsciiString, AsciiString> TeamKey;

	_STL::map<TeamKey, int> m_teamMap;		// +0x00
	_STL::vector<BfmeThingUBB> m_teams;		// +0x0C
	short m_numActive;				// +0x18
	short m_freeHead;				// +0x1A
};

void TeamsInfoRec::clear()
{
	_STL::vector<BfmeThingUBB>(1).swap(m_teams);
	m_teamMap.clear();
	m_numActive = 0;
	m_freeHead = 0;
}
