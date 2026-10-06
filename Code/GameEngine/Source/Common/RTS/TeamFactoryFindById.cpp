// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0039F72C@Rva0039FE6COwner@@QAEPAVTeamPrototype@@I@Z @0x0039F72C 53B
// TeamFactory prototype map linear find by id. Walks the +0xB0 map from
// header->left via rowed _M_increment 0x00024250; each node carries the
// 8-byte key at +0x10 and the TeamPrototype at +0x18 whose +0x0C id is
// compared to the arg. Returns the prototype or null. Same owner/map/node
// as siblings 0x0039FE6C and 0x0039FE11; callers at 0x002B17B4 0x003A31C4
// 0x004EDB33 prove the single-arg thiscall shape.
// Evidence: ret 4 thiscall; [ecx+0xB0] header and [header+8] begin.
namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

struct Rva0039D8FBKey
{
	int m_first;
	int m_second;
};

class TeamPrototype
{
public:
	char m_pad00[0x0C];
	unsigned int m_id0C;
};

struct Rva0039EA4ENode : public _STL::_Rb_tree_node_base
{
	Rva0039D8FBKey m_key10;
	TeamPrototype *m_value18;
};

struct Rva0039EA4EHeader
{
	int m_color00;
	Rva0039EA4ENode *m_parent04;
	Rva0039EA4ENode *m_left08;
	Rva0039EA4ENode *m_right0C;
};

class Rva0039FE6COwner
{
public:
	TeamPrototype *rva0039F72C(unsigned int id);
private:
	unsigned char m_pad00[0xB0];
	Rva0039EA4EHeader *m_mapB0;
};

TeamPrototype *Rva0039FE6COwner::rva0039F72C(unsigned int id)
{
	Rva0039EA4ENode *node = (Rva0039EA4ENode *)m_mapB0->m_left08;
	if (node != (Rva0039EA4ENode *)m_mapB0) {
		do {
			TeamPrototype *proto = node->m_value18;
			if (proto->m_id0C == id)
				return proto;
			node = (Rva0039EA4ENode *)_STL::_Rb_global<bool>::_M_increment(node);
		} while (node != (Rva0039EA4ENode *)m_mapB0);
	}
	return 0;
}
