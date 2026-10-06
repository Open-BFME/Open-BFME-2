// ?rva0020530E@Rva0020530EHost@@QAEXXZ
// partial score=0.7 date=2026-10-06
// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <map>
class Singleton1644
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void slot40(int v);
	virtual void slot44(int a, void *b);
};
extern Singleton1644 *TheSingletonE02D98;
struct TreeHead
{
	void *m_00;
	void *m_04;
	void *m_first08;
};
struct TreeNode
{
	char m_pad[0x10];
	void *m_10;
	unsigned char m_14;
};
class Rva0020530EHost
{
public:
	void rva0020530E();
private:
	char m_pad00[0x190C4];
	TreeHead *m_head190C4;
	char m_pad190C8[0x1A4C9-0x190C8];
	unsigned char m_1A4C9;
};
void Rva0020530EHost::rva0020530E()
{
	TheSingletonE02D98->slot40(m_1A4C9);
	TreeHead *head = m_head190C4;
	_STL::_Rb_tree_node_base *node = (_STL::_Rb_tree_node_base *)head->m_first08;
	if (node == (_STL::_Rb_tree_node_base *)head)
		return;
	while (true)
	{
		TreeNode *tn = (TreeNode *)node;
		TheSingletonE02D98->slot44(tn->m_14, &tn->m_10);
		node = _STL::_Rb_global<bool>::_M_increment(node);
		if (node == (_STL::_Rb_tree_node_base *)head)
			break;
	}
}
