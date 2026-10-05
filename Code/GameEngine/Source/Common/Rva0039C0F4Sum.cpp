// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

// ?rva0039C0F4@Rva0039C0F4@@QAEHABVAsciiString@@@Z @0x0039C0F4 93B
// Sum over 20 ObjectCountMaps matching ScoreKeeperMapCount shape: outer 20x12B array at +0x1FC,
// inner RB-tree walk with null-check plus name compare plus sum-value. Evidence: callees rowed
// 0x000069D6 StringBase compare and 0x00024250 _M_increment; callers 0x003C2E61 0x003E82E2;
// ret 4 proves one AsciiString const-ref arg; twin of 0x0039BF67 sum with KindOf.

class ThingTemplate
{
public:
	__declspec(dllimport) __forceinline const AsciiString &getName() const { return *(const AsciiString *)((const char *)this + 0x64); }
private:
	char m_pad[0x108];
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

class Rva0039C0F4
{
public:
	int rva0039C0F4(const AsciiString &name);
private:
	char m_pad[0x1FC];
	ObjectCountMap m_maps[20];
};

int Rva0039C0F4::rva0039C0F4(const AsciiString &name)
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
			int value = ((ObjectCountNode *)node)->m_value;
			if (tmpl && tmpl->getName().compare(name) == 0)
				total += value;
			node = _STL::_Rb_global<bool>::_M_increment(node);
		}
		++map;
	} while (--remaining != 0);
	return total;
}
