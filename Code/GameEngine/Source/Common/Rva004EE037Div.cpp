// cl: /MD
//
// ?rva004EE037@LivingWorldScoreKeeper@@QAEIXZ retail 0x004EE037 12B unsigned div.
// Evidence: [ecx+0x74] div by LogicFramesPerSecond 0x009BA4E4; callers 0x005BE3D6 0x005BFDE4.

#include <time.h>

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern int BfmeLogicFramesPerSecond;

#define LogicFramesPerSecond (*(const unsigned *)&BfmeLogicFramesPerSecond)
struct Rva004EE79ESub;
class Rva004E06FBPtrChase32Field
{
public:
	int get()const;
	char m_pad00[0x20];
	int m_20; // +0x20
	void *m_ptr; // +0x24
	Rva004EE79ESub *m_28; // +0x28
};
class Rva00DFEF10
{
public:
	char m_pad[0xFC];
	int m_FC;
};
// Use the linked singleton's established Living World logic pointer name and
// type; the local view below only describes the target's +0xFC integer read.
class Rva002BA8F1Logic;

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
class LivingWorldScoreKeeper
{
public:
	unsigned rva004EE037();
	int rva004EE043();
	void rva004EE072(const class Rva004E06FBPtrChase32Field *a, int b);
	void rva004EE0A6(int a, int b);
	int GetBuildingsOfTypeBuilt(int i);
	int rva004EE016();
	int rva004EE33B();
private:
	char m_pad[0x5C];
	int m_5C;
	int m_60;
	char m_low0[0x08];
	int m_6C;
	int m_70;
	unsigned m_74;
	int m_78;
	char m_mid0[0x04];
	int m_80[5];
	char m_high0[0x08];
	_STL::_Rb_tree_node_base *m_9C;
	char m_high1[0x4C];
	int m_EC;
};

unsigned LivingWorldScoreKeeper::rva004EE037()
{
	return m_74 / LogicFramesPerSecond;
}

int LivingWorldScoreKeeper::rva004EE043()
{
	if (m_78 == -1)
		return ((Rva00DFEF10 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->m_FC;
	return m_78;
}





int LivingWorldScoreKeeper::GetBuildingsOfTypeBuilt(int i)
{
	if (i < 0 || (unsigned)i >= 5)
		return 0;
	return m_80[i];
}

int LivingWorldScoreKeeper::rva004EE016()
{
	if (m_70 != 0)
		return time(0) + m_6C - m_70;
	return m_6C;
}

int LivingWorldScoreKeeper::rva004EE33B()
{
	_STL::_Rb_tree_node_base *h = m_9C;
	_STL::_Rb_tree_node_base *node = h->_M_left;
	int sum = 0;
	while (node != h) {
		sum += *(int *)((char *)node + 0x14);
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}
