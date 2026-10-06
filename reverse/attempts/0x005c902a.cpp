// ?method_005C902A@TargetObj005C8DBF@@QAEXM@Z
// partial score=0.96 date=2026-10-06
// stlport
// cl: /O1 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::pair<const int, void *> TreeValue005530A8;
typedef _STL::_Rb_tree<int, TreeValue005530A8, _STL::_Select1st<TreeValue005530A8>, _STL::less<int>, _STL::allocator<TreeValue005530A8> > Tree005530A8;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;

struct TreeNode005C8DBF
{
	char m_pad[0x14];
	int m_count;
};

class Rva005C8C73 : public Tree005530A8
{
public:
	void *rva005C8CA0(const void *key);
};

class Rva005C8F9A
{
public:
	_STL::pair<Tree00372FF4::iterator, bool> rva005C8F9A(const TreeValue00372FF4 &v);
private:
	Tree00372FF4 m_tree;
};

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad04() = 0;
	virtual void _pad08() = 0;
	virtual void _pad0C() = 0;
	virtual void _pad10() = 0;
	virtual void _pad14() = 0;
	virtual void _pad18() = 0;
	virtual void _pad1C() = 0;
	virtual void _pad20() = 0;
	virtual void _pad24() = 0;
	virtual void _pad28() = 0;
	virtual void _pad2C() = 0;
	virtual void _pad30() = 0;
	virtual void _pad34() = 0;
	virtual void _pad38() = 0;
	virtual void _pad3C() = 0;
	virtual void _pad40() = 0;
	virtual void _pad44() = 0;
	virtual void _pad48() = 0;
	virtual void _pad4C() = 0;
	virtual void _pad50() = 0;
	virtual void _pad54() = 0;
	virtual void _pad58() = 0;
	virtual void _pad5C() = 0;
	virtual void _pad60() = 0;
	virtual void _pad64() = 0;
	virtual void _pad68() = 0;
	virtual void _pad6C() = 0;
	virtual void _pad70() = 0;
	virtual void _pad74() = 0;
	virtual void _pad78() = 0;
	virtual void _pad7C() = 0;
	virtual void _pad80() = 0;
	virtual void _pad84() = 0;
	virtual void _pad88() = 0;
	virtual void _pad8C() = 0;
	virtual void _pad90() = 0;
	virtual void _pad94() = 0;
	virtual void _pad98() = 0;
	virtual void _pad9C() = 0;
	virtual void _padA0() = 0;
	virtual void _padA4() = 0;
	virtual void _padA8() = 0;
	virtual void _padAC() = 0;
	virtual void _padB0() = 0;
	virtual void _padB4() = 0;
	virtual void _padB8() = 0;
	virtual void _padBC() = 0;
	virtual void _padC0() = 0;
	virtual void _padC4() = 0;
	virtual void _padC8() = 0;
	virtual void _padCC() = 0;
	virtual void _padD0() = 0;
	virtual void _padD4() = 0;
	virtual void _padD8() = 0;
	virtual void method_DC(int handle, float val, int flag) = 0;
};
extern AudioManager *TheAudio;

class Matrix3D
{
public:
	void Set_Z_Translation(float z);
};

struct BfmePoolHolder
{
	char m_pad00[0x0c];
	int m_audioHandle0C;
	char m_pad10[0x1c];
	float m_float2C;
};

struct Rva005C8D17Inner
{
	unsigned char m_pad[0x10];
	float m_10;
};

struct Rva005C8D17Mid
{
	unsigned char m_pad[8];
	Rva005C8D17Inner *m_08;
};

class Rva005C8D17
{
public:
	float rva005C8D17();
	char m_pad00[0x2c];
	Rva005C8D17Mid *m_2C;
	int m_30;
};

float Rva005C8D17::rva005C8D17()
{
	if (m_30 == 0)
		return 1.0f;
	return m_2C->m_08->m_10;
}

class TargetObj005C8DBF
{
public:
	char m_pad00[8];
	BfmePoolHolder *m_target08;
	char m_pad0C[0x20];
	Rva005C8C73 m_tree2C;

	void method_005C8D6B();
	void method_005C8DBF(float val);
	void method_005C902A(float val);
};

void TargetObj005C8DBF::method_005C8D6B()
{
	BfmePoolHolder *target = m_target08;
	if (!target)
		return;
	float val = ((Rva005C8D17 *)this)->rva005C8D17();
	if (val != target->m_float2C)
	{
		((Matrix3D *)target)->Set_Z_Translation(val);
		TheAudio->method_DC(m_target08->m_audioHandle0C, val, 0);
	}
}

void TargetObj005C8DBF::method_005C8DBF(float val)
{
	TreeValue00372FF4 v;
	*(float *)&v.first = val;
	v.second.m_bits = 0;
	TreeNode005C8DBF *node = (TreeNode005C8DBF *)m_tree2C.rva005C8CA0(&v);
	if (node != (TreeNode005C8DBF *)m_tree2C.end()._M_node)
	{
		int *p = &node->m_count;
		(*p)--;
		if (node->m_count == 0)
		{
			Tree005530A8::iterator it;
			it._M_node = (_STL::_Rb_tree_node_base *)node;
			m_tree2C.erase(it);
			method_005C8D6B();
		}
	}
}

void TargetObj005C8DBF::method_005C902A(float val)
{
	TreeValue00372FF4 v;
	*(float *)&v.first = val;
	v.second.m_bits = 0;
	_STL::pair<Tree00372FF4::iterator, bool> res = ((Rva005C8F9A *)&m_tree2C)->rva005C8F9A(v);
	TreeNode005C8DBF &node = *(TreeNode005C8DBF *)res.first._M_node;
	++node.m_count;
	if (node.m_count == 1)
		method_005C8D6B();
}
