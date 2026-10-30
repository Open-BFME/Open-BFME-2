// cl: /O1 /MD
void __cdecl Rva00030830GameFree(void *p);
// stlport
#ifndef _STLP_USE_STATIC_LIB
#define _STLP_USE_STATIC_LIB 1
#endif
#include <map>
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
struct BurningCellTreeNode
{
	unsigned char m_pad[0x10];
	Rva002860CFVirt m_10;
};
// STLport's tree iterator, passed by value with its copy constructor.
struct Rva00286214Node;
struct Rva002860CFIterator
{
	Rva00286214Node *m_node;
	Rva002860CFIterator(Rva00286214Node *node) : m_node(node) {}
	Rva002860CFIterator(const Rva002860CFIterator &that) : m_node(that.m_node) {}
};
// The erase(iterator) of FireLogicSystem's m_cellsOnFire set (+0x84), called
// by ChangeBurnRate 0x00286926 after the find at 0x00286214.
class Rva002860CFHost
{
public:
	void rva002860CF(Rva002860CFIterator it);
private:
	void *m_ptr; // +0x00
	int m_4; // +0x04
};
// ?rva002860CF@Rva002860CFHost@@QAEXURva002860CFIterator@@@Z
void Rva002860CFHost::rva002860CF(Rva002860CFIterator it)
{
	_STL::_Rb_tree_node_base *node = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		reinterpret_cast<_STL::_Rb_tree_node_base *>(it.m_node),
		*(_STL::_Rb_tree_node_base **)((char *)m_ptr + 4),
		*(_STL::_Rb_tree_node_base **)((char *)m_ptr + 8),
		*(_STL::_Rb_tree_node_base **)((char *)m_ptr + 12));
	Rva002860CFVirt *pm = &((BurningCellTreeNode *)node)->m_10;
	pm->v2C(0);
	if (node != 0)
		Rva00030830GameFree(node);
	m_4--;
}
