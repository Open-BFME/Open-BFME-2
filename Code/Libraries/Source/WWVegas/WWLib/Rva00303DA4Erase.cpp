// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00303DA4@Rva00303DA4@@QAEXPAURva00303DA4Node@@@Z @0x00303DA4 59B: Rb erase-one.
// Evidence: calls rowed 0x00025620 _Rebalance_for_erase plus rowed 0x0022DDF4
// ??1Rva0022DDF4@@QAE@XZ value dtor at +16 plus _free 0x00030830; dec count at
// +4 ret 4; same 59B shape as Rva002A408B 0x002A408B Rva00358DC2 0x00358DC2
// Rva00439325 0x00439325; neighbours pair ctors 0x00303D6B 0x00303DDF map
// AsciiString->MapMetaData; caller 0x003042DD; unblocks 0x003042DD.
extern "C" void __cdecl free(void *block);

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	typedef _Rb_tree_Color_type _Color_type;
	typedef _Rb_tree_node_base *_Base_ptr;
	_Color_type _M_color;
	_Base_ptr _M_parent;
	_Base_ptr _M_left;
	_Base_ptr _M_right;
};
template <class _Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _Rebalance_for_erase(
		_Rb_tree_node_base *__z, _Rb_tree_node_base *&__root,
		_Rb_tree_node_base *&__leftmost, _Rb_tree_node_base *&__rightmost);
};
}

class Rva0022DDF4
{
public:
	~Rva0022DDF4();
};

struct Rva00303DA4Node : public _STL::_Rb_tree_node_base
{
};

class Rva00303DA4
{
	_STL::_Rb_tree_node_base *m_header;
	int m_count;
public:
	void rva00303DA4(Rva00303DA4Node *pos);
};

void Rva00303DA4::rva00303DA4(Rva00303DA4Node *pos)
{
	_STL::_Rb_tree_node_base *toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		pos, m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((Rva0022DDF4 *)(toDelete + 1))->~Rva0022DDF4();
	if (toDelete)
		free(toDelete);
	--m_count;
}
