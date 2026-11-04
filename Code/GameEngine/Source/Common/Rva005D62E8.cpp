// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva005D62E8@Rva005D62E8@@QAEPAV1@PAVPlayerInfo@@@Z, retail 0x005D62E8, 178 bytes.
// Evidence: __thiscall, ret 4 single PlayerInfo arg; calls g_00E05FB4 vf10,
// TheGameSpyInfo vf24/vf31 rows, _M_find map<int,int> row, PlayerInfo::isIgnored row.
// Vtable slots 0x28/0x60/0x7c read off retail; PlayerInfo +0x14 profileID +0x18 flags.
// Returns this (retail mov eax,esi).
// Link: minimal _STL view (no <map>) emits only the row; the full header also
// emitted find/end/operator!=/less COMDATs that lost (first copy is the
// speed-built stlport_map_int_int.obj). Direct _M_find plus header compare
// reproduces retail's inlined find (!= end) shape (Rva002B6498Find precedent).
class Rva005D62E8;
namespace _STL {
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class P> struct _Select1st
{
};
template <class T> struct less
{
};
template <class T> class allocator
{
};
template <class V> struct _Rb_tree_node;
template <class K, class V, class KOV, class Cmp, class Alloc> class _Rb_tree
{
	friend class ::Rva005D62E8;
	typedef _Rb_tree_node<V> *_Link_type;
private:
	template <class KT> _Link_type _M_find(const KT &) const;
};
template <class K, class T, class C = less<K>, class A = allocator<pair<const K, T> > > class map;
}
typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > MapIntIntTree;

class Rva00E05FB4
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8();
	virtual void vf9();
	virtual bool vf10(int v);
};
extern class GameSpyConfigInterface *TheGameSpyConfig;

#include "../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;

#include "../../Include/GameNetwork/PlayerInfo.h"

class Rva005D62E8
{
public:
	Rva005D62E8 *rva005D62E8(PlayerInfo *p);
private:
	PlayerInfo *m_player; // +0x0
	int m_state; // +0x4
	int m_sub; // +0x8
};

Rva005D62E8 *Rva005D62E8::rva005D62E8(PlayerInfo *playerInfo)
{
	m_state = 0;
	m_player = playerInfo;
	m_sub = 11;
	if ((playerInfo->m_at18 & 0x20) == 0 && !(*(Rva00E05FB4 **)&TheGameSpyConfig)->vf10(playerInfo->m_at14))
	{
		MapIntIntTree *mapIntIntTree = (MapIntIntTree *)TheGameSpyInfo->getBuddyMap();
		_STL::_Rb_tree_node<IntIntPair> *node = mapIntIntTree->_M_find(m_player->m_at14);
		if ((void *)node != *(void * *)mapIntIntTree)
		{
			m_state = 1;
			m_sub = 8;
		}
		else if (m_player->m_at14 == TheGameSpyInfo->getLocalProfileID())
		{
			m_state = 3;
			m_sub = 10;
		}
		else
		{
			m_state = 0;
			m_sub = 6;
		}
	}
	else
	{
		m_state = 2;
		m_sub = 7;
	}
	if (m_player->isIgnored())
	{
		m_state += -4;
		m_sub = 11;
	}
	return this;
}
