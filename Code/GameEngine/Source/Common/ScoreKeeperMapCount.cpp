// cl: /DNDEBUG /MD /EHsc
// ?Rva0039BEC3Count@@YGHABV?$BitFlags@$0HE@@@0PBUObjectCountMap@@@Z @0x0039BEC3 72B free helper summing ObjectCountMap.
// Donor: ZH ScoreKeeper::getTotalUnitsBuilt (same null-check plus testSetAndClear
// plus sum-second loop). Evidence: 4 callers 0x39BF0B/22/39/50 pass ecx+0x1C8/1D4/
// 1F0/2EC as map plus two KindOf masks; ThingTemplate KindOf at +0x108 (StatsCollector
// witness); callees rowed 0x30A146 testSetAndClear and 0x24250 _M_increment.

template <int N>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;
private:
	unsigned m_words[7];
};

class ThingTemplate
{
public:
	bool isKindOfMulti(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear) const
	{
		return m_kindOf.testSetAndClear(mustBeSet, mustBeClear);
	}
private:
	char m_pad[0x108];
	BitFlags<116> m_kindOf;
};

namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class D>
class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

struct ObjectCountMap
{
	_STL::_Rb_tree_node_base *m_header;
	int m_pad04;
	int m_pad08;
};

struct ObjectCountNode : public _STL::_Rb_tree_node_base
{
	const ThingTemplate *m_key;
	int m_value;
};

int __stdcall Rva0039BEC3Count(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear, const ObjectCountMap *map)
{
	int total = 0;
	_STL::_Rb_tree_node_base *node = map->m_header->_M_left;
	while (node != map->m_header)
	{
		const ThingTemplate *tmpl = (const ThingTemplate *)((ObjectCountNode *)node)->m_key;
		if (tmpl && tmpl->isKindOfMulti(mustBeSet, mustBeClear))
			total += ((ObjectCountNode *)node)->m_value;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return total;
}
