// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// ?rva00439920@Rva00439920@@QAEXXZ @0x00439920 30B.
// Reset: clear map at +4 via landed 0x00240C60, zero +0x14, store 1.0f
// (global 0x00BBB8D8) to +0x10. Evidence: chain lane (calls just-landed
// 0x00240C60); same +4 clear as Rva000D3FA0Map dtor neighbours; caller
// 0x002443C8; float 1.0f proven by re_attempts 0x000C9251 and 0x005DB928.
extern float g_Va00BBB8D8;

#define kOne00439920 g_Va00BBB8D8

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
}

struct Rva00439325
{
	_STL::_Rb_tree_node_base *m_header;
	int m_count;
	void rva00240C60();
};

class Rva00439920
{
public:
	void rva00439920();
private:
	char m_pad00[4];
	Rva00439325 m_map04;
	char m_pad0C[4];
	float m_unk10;
	int m_unk14;
};

void Rva00439920::rva00439920()
{
	m_map04.rva00240C60();
	float one = kOne00439920;
	m_unk14 = 0;
	m_unk10 = one;
}
