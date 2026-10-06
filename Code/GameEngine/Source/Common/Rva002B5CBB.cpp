// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ob2
// ?rva002B5CBB@Rva002B5CBB@@QAE_NPAURva002B5CBBArg@@@Z @0x002B5CBB 64B
// Evidence: linkbody lane; map at +0x130 via rowed _M_increment 0x00024250 like sibling 0x002B5C5E;
// node +0x14 value with byte +0x1c gate and rowed-equivalent pin 0x004FBED6 compare to arg +0x14.
// TU-local honest-address views.
namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class D> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

class Rva004FBED6Call
{
public:
	void *rva004FBED6();
	char m_pad00[0x1C];
	unsigned char m_1C;
};

struct Rva002B5CBBArg
{
	char m_pad00[0x14];
	void *m_14;
};

class Rva002B5CBB
{
public:
	bool rva002B5CBB(Rva002B5CBBArg *arg);
private:
	char m_pad00[0x130];
	_STL::_Rb_tree_node_base *m_header130;
};

bool Rva002B5CBB::rva002B5CBB(Rva002B5CBBArg *arg)
{
	_STL::_Rb_tree_node_base *header = m_header130;
	_STL::_Rb_tree_node_base *node = header->_M_left;
	while (node != header)
	{
		Rva004FBED6Call *v = *(Rva004FBED6Call **)((char *)node + 0x14);
		if (v->m_1C == 0)
		{
			void *want = arg->m_14;
			void *got = v->rva004FBED6();
			if (got == want)
				return true;
		}
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return false;
}
