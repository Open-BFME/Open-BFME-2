// cl: /DNDEBUG /MD /EHsc
// ?Rva0039BFC5Count@@YGHPBVThingTemplate@@PBUObjectCountMap@@@Z @0x0039BFC5 56B
// Count of entries in one ObjectCountMap whose key isEquivalentTo the query.
// Evidence: callees rowed 0x0033BB04 ThingTemplate::isEquivalentTo and
// 0x00024250 _M_increment; neighbours 0x0039BF67/0x0039C0F4 prove the
// ObjectCountMap shape (header ptr +0, key +0x10, value +0x14); ret 8 proves
// two __stdcall args (query first, map second).

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
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

int __stdcall Rva0039BFC5Count(const ThingTemplate *tmpl, const ObjectCountMap *map)
{
	int total = 0;
	_STL::_Rb_tree_node_base *node = map->m_header->_M_left;
	while (node != map->m_header)
	{
		if (((ObjectCountNode *)node)->m_key->isEquivalentTo(tmpl))
			++total;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return total;
}
