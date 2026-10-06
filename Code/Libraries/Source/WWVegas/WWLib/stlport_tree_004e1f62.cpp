// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport

// ?rva004E1F62@Rva004E1F62@@QAEXXZ, RVA 0x004E1F62, 53B. Unlock lane: iterate
// Rb_tree map via rowed _M_increment at 0x00024250; each node +0x14 holds a
// payload pointer whose virtual slot 6 (bool) gates virtual slot 5 (void).
// Caller jmps at 0x003EEABA. Prev TreeHintPayload004E2257 family so same
// flags. Owner unknown so honest address-derived names.
namespace _STL { struct _Rb_tree_node_base { bool _M_color; _Rb_tree_node_base *_M_parent; _Rb_tree_node_base *_M_left; _Rb_tree_node_base *_M_right; }; template <class D> class _Rb_global { public: static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *); }; }
struct Rva004E1F62Payload
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void Apply();
	virtual bool ShouldApply();
};
struct Rva004E1F62
{
	_STL::_Rb_tree_node_base *m_header;
	void rva004E1F62();
};

void Rva004E1F62::rva004E1F62()
{
	_STL::_Rb_tree_node_base *node = m_header->_M_left;
	if (node == m_header)
		return;
	do {
		Rva004E1F62Payload *p = *(Rva004E1F62Payload **)((char *)node + 0x14);
		if (p != 0 && p->ShouldApply())
		{
			p = *(Rva004E1F62Payload **)((char *)node + 0x14);
			p->Apply();
		}
		node = _STL::_Rb_global<bool>::_M_increment(node);
	} while (node != m_header);
}
