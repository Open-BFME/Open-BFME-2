// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357AF8@ScriptEngine@@QAE_NPAX@Z, retail 0x00357AF8 69B leaf.
// Evidence: prev ScriptEngine 0x00357A36 same TU flags; map at +0x190B8 from
// ScriptEngine_dtor Rva0020766DMap; StringBase compare rowed 0x000069D6;
// _M_increment rowed 0x00024250; global string data 0x009E0878.

template <typename T>
class StringBase
{
public:
	int compare(const StringBase &other) const;

private:
	T *m_data;
};

extern StringBase<char> g_str009E0878;

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

struct ScriptArg
{
	char m_pad0[0x74];
	int m_id74; // +0x74
	char m_pad1[0x10]; // +0x78..0x87
	StringBase<char> m_str88; // +0x88
};

struct MapNode
{
	char m_pad[0x18];
	int m_id18; // +0x18
};

class ScriptEngine
{
public:
	bool rva00357AF8(void *p);

private:
	char m_pad[0x190B8];
	_STL::_Rb_tree_node_base *m_header190B8; // +0x190B8
};

bool ScriptEngine::rva00357AF8(void *p)
{
	ScriptArg *arg = (ScriptArg *)p;
	if (arg->m_str88.compare(g_str009E0878) != 0)
		return true;
	_STL::_Rb_tree_node_base *header = m_header190B8;
	_STL::_Rb_tree_node_base *node = header->_M_left;
	while (node != header)
	{
		if (((MapNode *)node)->m_id18 == arg->m_id74)
			return true;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return false;
}
// ?g_str009E0878@@3V?$StringBase@D@@A: the global at VA 0xde0878 is ?TheEmptyString@AsciiString@@2V1@B.
#pragma comment(linker, "/alternatename:?g_str009E0878@@3V?$StringBase@D@@A=?TheEmptyString@AsciiString@@2V1@B")
