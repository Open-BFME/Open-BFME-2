// cl: /O1 /arch:SSE /G7 /MD /EHs /EHc- /D_STLP_USE_MALLOC /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ?rva005E56FC@Rva005E56FC@@QAEPAXXZ @0x005E56FC 78B.
// View then player then singleton member query with its native ECX receiver.
// Evidence: thiscall ret 0 no args returning void pointer; global g_009FEF10
// view at +0xB0 rowed 0x0020EAF6 with this+8; id chain this+4 then +0x18 +0x54;
// find rowed 0x002B51F8; member query rowed 0x002B4948; shared xor eax null path.

class LivingWorldLogic
{
public:
    void *rva002B4948(void *a1, void *a2, void *a3);
};
extern LivingWorldLogic *TheLivingWorldLogic;
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
// The 12-byte vector ABI is established by the rowed range constructor
// at 0x005E60D1 and its base at 0x00211E58. Declare that constructor here
// so this caller cannot emit competing range/copy helpers. The destructor
// follows the observed start-pointer test and free at both return sites.
namespace _STL {
template <> class vector<int, allocator<int> > {
public:
    template <class Iter> vector(Iter, Iter, const allocator<int>&);
    ~vector() { if (start) ::free(start); }
private:
    int *start;
    int *finish;
    int *end_of_storage;
};
}
class Rva002B6C9F {public: bool rva002B6CE5(int,int,int);};

class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);
};
class Rva002E2903Player;
struct Rva002B488EResult;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
	Rva002B488EResult *rva002B488E(int id);
public:
	char m_pad[0xB0];
	Rva0020EAF6View *m_B0;
};

struct Rva005E56FCIdInner
{
	char m_pad[0x54];
	int m_id54;
};
struct Rva005E56FCOuter
{
	void rva005E652E(void *garrison);
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
	void rva005E6765();
	void rva005E66DF();
private:
	int m_00;
	Rva005E56FCOuter *m_04;
	int m_08;
};
void *Rva005E56FC::rva005E56FC()
{
	Rva0020E89C *view = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_B0->rva0020EAF6(m_08);
	if (view != 0)
	{
		int id = m_04->m_ptr18->m_id54;
		Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(id, 0);
		if (player != 0)
		{
			return TheLivingWorldLogic->rva002B4948(player, view, 0);
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
    if (result && ((Rva002B6C9F *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B6CE5(
            (int)m_04->m_ptr18, (int)&values, (int)result))
        return 14;
    return -1;
}

// Native 0x005E6765..0x005E67E2 (125B). Shares the receiver, tree range,
// range constructor and query with the rowed cursor routine above. Retail
// calls 0x005E652E with the +4 owner in ECX and the garrison as its one
// stack argument only after the query succeeds. The WB callgraph twin
// calls the named MoveArmyMembers at the corresponding point; that is
// semantic evidence for the operation, not a name claim for this method.
void Rva005E56FC::rva005E6765()
{
    void *result = rva005E56FC();
    _STL::vector<int> values(Rva005E59FCKeyIterator(m_04->m_keyView.begin()),
        Rva005E59FCKeyIterator(m_04->m_keyView.end()), _STL::allocator<int>());
    if (result && ((Rva002B6C9F *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B6CE5(
            (int)m_04->m_ptr18, (int)&values, (int)result))
        m_04->rva005E652E(result);
}

// Native 0x005E66DF..0x005E6765 (134B). This receiver, owner tree,
// range constructor, query and owner dispatch are shared with rva005E6765.
// The difference is the rowed findArmy call on this+8 instead of the
// garrison lookup. WB's SelectedMemberArmyDest::MoveTo corroborates this
// call relationship; the receiver retains its established opaque name.
void Rva005E56FC::rva005E66DF()
{
    void *result = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(m_08);
    _STL::vector<int> values(Rva005E59FCKeyIterator(m_04->m_keyView.begin()),
        Rva005E59FCKeyIterator(m_04->m_keyView.end()), _STL::allocator<int>());
    if (result && ((Rva002B6C9F *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B6CE5(
            (int)m_04->m_ptr18, (int)&values, (int)result))
        m_04->rva005E652E(result);
}
