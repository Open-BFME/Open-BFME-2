// cl: /O1 /MD
void __cdecl rva00030830(void *p);
namespace _STL
{
struct _Rb_tree_node_base;
template <class _Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _Rebalance_for_erase(
		_Rb_tree_node_base *__z, _Rb_tree_node_base *&__root,
		_Rb_tree_node_base *&__leftmost, _Rb_tree_node_base *&__rightmost);
};
}
class Rva002860CFVirt
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C(int v);
};
struct Rva002860CFS
{
	unsigned char m_pad[0x10];
	Rva002860CFVirt m_10;
};
// STLport's tree iterator, passed by value with its copy constructor.
struct Rva002860CFIterator
{
	_STL::_Rb_tree_node_base *m_node;
	Rva002860CFIterator(const Rva002860CFIterator &that) : m_node(that.m_node) {}
};
// The erase(iterator) of FireLogicSystem's m_cellsOnFire set (+0x84), called
// by ChangeBurnRate 0x00286926 after the find at 0x00286214.
class Rva002860CFHost
{
public:
	void rva002860CF(Rva002860CFIterator it);
private:
	void *m_ptr;
	int m_4;
};
// ?rva002860CF@Rva002860CFHost@@QAEXURva002860CFIterator@@@Z
void Rva002860CFHost::rva002860CF(Rva002860CFIterator it)
{
	_STL::_Rb_tree_node_base *s = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		it.m_node,
		*(_STL::_Rb_tree_node_base **)((char *)m_ptr + 4),
		*(_STL::_Rb_tree_node_base **)((char *)m_ptr + 8),
		*(_STL::_Rb_tree_node_base **)((char *)m_ptr + 12));
	Rva002860CFVirt *pm = &((Rva002860CFS *)s)->m_10;
	pm->v2C(0);
	if (s != 0)
		rva00030830(s);
	m_4--;
}
