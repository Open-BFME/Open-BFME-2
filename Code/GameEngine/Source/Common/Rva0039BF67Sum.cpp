// cl: /DNDEBUG /MD /EHsc
// ?rva0039BF67@Rva0039BF67@@QAEHV?$BitFlags@$0HE@@@0@Z @0x0039BF67 94B sum over 20 ObjectCountMaps.
// Free-method sum matching ScoreKeeperMapCount shape: outer 20x12B array at +0x1FC,
// inner RB-tree walk with null-check plus testSetAndClear plus sum-value.
// Evidence: callees rowed 0x30A146 testSetAndClear and 0x24250 _M_increment;
// ThingTemplate KindOf at +0x108; callers 0x3C2EC9/0x3E5C04; ret 0x38 proves two
// BitFlags<116> by value.

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

class Rva0039BF67
{
public:
	int rva0039BF67(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear);
private:
	char m_pad[0x1FC];
	ObjectCountMap m_maps[20];
};

int Rva0039BF67::rva0039BF67(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear)
{
	int total = 0;
	ObjectCountMap *map = m_maps;
	int remaining = 20;
	do
	{
		_STL::_Rb_tree_node_base *node = map->m_header->_M_left;
		while (node != map->m_header)
		{
			const ThingTemplate *tmpl = ((ObjectCountNode *)node)->m_key;
			if (tmpl && tmpl->isKindOfMulti(mustBeSet, mustBeClear))
				total += ((ObjectCountNode *)node)->m_value;
			node = _STL::_Rb_global<bool>::_M_increment(node);
		}
		++map;
	} while (--remaining != 0);
	return total;
}
