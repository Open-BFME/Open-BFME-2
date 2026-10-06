// cl: /MD /GX-
//
// ?rva002B9CFC@Rva002B9CFC@@QAEXPAVOther002B9CFC@@@Z @0x002B9CFC 203B
// Rebuild with Other virtuals (0x28/4/0x78/0x30) plus Rva clear 0x002B6900
// plus new 0x20 plus ctor 0x002B644A plus map<int int> subscript 0x0028932C
// plus increment 0x00024250 loop; minimal _STL forward declares (no <map>
// to keep direct E8 calls and avoid dllimport/redefinition).
class Rva002B644A
{
public:
	Rva002B644A();
};

void *__cdecl operator new(unsigned int size);
inline void *__cdecl operator new(unsigned int, void *p)
{
	return p;
}

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
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct less
{
};
template <class T> class allocator
{
};
template <class K, class V, class C, class A> class map
{
public:
	int &operator[](const int &key);
};
}

class Rva002B6900
{
public:
	void rva002B6900();
};

class Other002B9CFC
{
public:
	virtual void v00();
	virtual bool v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28(void *out);
	virtual void v2C();
	virtual void v30(void *arg);
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5C();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6C();
	virtual void v70();
	virtual void v74();
	virtual void v78(int *out);
};

struct TwoBools002B9CFC
{
	bool m_b0;
	bool m_b1;
};

class Rva002B9CFC : public Rva002B6900
{
public:
	void rva002B9CFC(Other002B9CFC *other);
};

// ?rva002B6900@Rva002B6900@@QAEXXZ @0x002B6900 rowed
// ??0Rva002B644A@@QAE@XZ @0x002B644A rowed
// ??A?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAEAAHABH@Z @0x0028932C rowed
// ??2@YAPAXI@Z @0x0002FDA0 rowed
// ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z @0x00024250 rowed
void Rva002B9CFC::rva002B9CFC(Other002B9CFC *other)
{
	TwoBools002B9CFC bb;
	bb.m_b0 = true;
	bb.m_b1 = true;
	other->v28(&bb);
	if (other->v04())
	{
		((Rva002B6900 *)this)->rva002B6900();
		unsigned int count = 0;
		other->v78((int *)&count);
		if (count > 0)
		{
		_STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > *map130 = (_STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > *)((char *)this + 0x130);
			unsigned int i = 0;
			do
			{
				Rva002B644A *p = (Rva002B644A *)::operator new(0x20);
				p = p ? (Rva002B644A *)new (p) Rva002B644A() : 0;
				other->v30(p);
				int key = *(int *)((char *)p + 4);
				(*map130)[key] = (int)p;
			} while (++i < count);
		}
	}
	else
	{
		int cnt = *(int *)((char *)this + 0x134);
		int outCount = cnt;
		other->v78(&outCount);
		_STL::_Rb_tree_node_base *header = *(_STL::_Rb_tree_node_base **)((char *)this + 0x130);
		_STL::_Rb_tree_node_base *node = header->_M_left;
		while (node != header)
		{
			void *val = *(void **)((char *)node + 0x14);
			other->v30(val);
			node = _STL::_Rb_global<bool>::_M_increment(node);
		}
	}
}
