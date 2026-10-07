// cl: /O1 /arch:SSE /G7 /MD /EHs /EHc- /D_STLP_USE_MALLOC /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ?rva005E56FC@Rva005E56FC@@QAEPAXXZ @0x005E56FC 78B.
// View then player then stdcall chain with redundant mov ecx before stdcall.
// Evidence: thiscall ret 0 no args returning void pointer; global g_009FEF10
// view at +0xB0 rowed 0x0020EAF6 with this+8; id chain this+4 then +0x18 +0x54;
// find rowed 0x002B51F8; stdcall rowed 0x002B4948; shared xor eax null path.
#include <vector>
#include <map>
#include <set>
struct Rva005E59FCKeyIterator {
 typedef _STL::bidirectional_iterator_tag iterator_category;
 typedef int value_type;
 typedef int difference_type;
 typedef int *pointer;
 typedef int &reference;
 _STL::_Rb_tree_node_base *node;
 Rva005E59FCKeyIterator(_STL::set<int>::iterator it):node(it._M_node) {}
 int &operator*() const {return *(int*)((char*)node+16);}
 Rva005E59FCKeyIterator &operator++(){node=_STL::_Rb_global<bool>::_M_increment(node);return *this;}
 Rva005E59FCKeyIterator &operator--(){node=_STL::_Rb_global<bool>::_M_decrement(node);return *this;}
 bool operator==(const Rva005E59FCKeyIterator&b)const{return node==b.node;}
 bool operator!=(const Rva005E59FCKeyIterator&b)const{return node!=b.node;}
};
class Rva002B6C9F {public: bool rva002B6CE5(int,int,int);};

class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);
};
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
public:
	char m_pad[0xB0];
	Rva0020EAF6View *m_B0;
};
extern Rva002BA8F1Logic *g_009FEF10;
void *__stdcall Rva002B4948Find(void *a1, void *a2, void *a3);
struct Rva005E56FCIdInner
{
	char m_pad[0x54];
	int m_id54;
};
struct Rva005E56FCOuter
{
	char m_pad[0x18];
	Rva005E56FCIdInner *m_ptr18;
	char m_pad1[0x10];
	_STL::set<int> m_keyView; // +0x2C: key-only view; original tree payload unknown
};
class Rva005E56FC
{
public:
	void *rva005E56FC();
	int rva005E61A8();
private:
	int m_00;
	Rva005E56FCOuter *m_04;
	int m_08;
};
void *Rva005E56FC::rva005E56FC()
{
	Rva0020E89C *view = g_009FEF10->m_B0->rva0020EAF6(m_08);
	if (view != 0)
	{
		int id = m_04->m_ptr18->m_id54;
		Rva002E2903Player *player = g_009FEF10->find(id, 0);
		if (player != 0)
		{
			(void)*(Rva002BA8F1Logic * volatile *)&g_009FEF10;
			return Rva002B4948Find(player, view, 0);
		}
	}
	return 0;
}

// Native 0x005E61A8..0x005E6237: RET0 thiscall shares the receiver of
// rva005E56FC. The +4 owner contributes the +0x18 argument and +0x2C
// tree header; its left link supplies begin. The rowed range constructor
// and rva002B6CE5 establish the calls. Original application identity is unknown.
// STLport 4.5.3 iterator view follows StlportTreeKeyRangeVector.cpp, whose
// 0x005E60D1 constructor is the target callee. /EHs preserves both free states.
int Rva005E56FC::rva005E61A8()
{
    void *result = rva005E56FC();
    _STL::vector<int> values(Rva005E59FCKeyIterator(m_04->m_keyView.begin()),
        Rva005E59FCKeyIterator(m_04->m_keyView.end()), _STL::allocator<int>());
    if (result && ((Rva002B6C9F *)g_009FEF10)->rva002B6CE5(
            (int)m_04->m_ptr18, (int)&values, (int)result))
        return 14;
    return -1;
}
