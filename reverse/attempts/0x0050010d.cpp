// ?rva0050010D@Rva004FF8DA@@QAE_NHH@Z
// partial score=0.96 date=2026-10-08
// cl: /D_STLP_USE_MALLOC /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail boundaries: 004FF8DA..004FF910 (54B), 004FF910..004FF98D (125B).
// WB12FC890 supports LivingWorldAIBuildingTypes::GetUnitOfType for the latter.
// Retail proves the tree at receiver+38, its mapped pointer at node+14,
// eight 12-byte vector views and 88-byte elements. Their full types are unknown.
// Keep RVA owner/method names and partial call views; do not claim allocation
// layouts or emit competing STL helpers. Both use the rowed int-key _M_find
// at 00388F63; the random call is the named provider at 00233FF4.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <vector>
class Rva004FF8DA;
namespace _STL { template<class T> struct _Select1st {}; template<class T> struct less {};
struct _Rb_tree_node_base {
 int color; _Rb_tree_node_base *parent,*left,*right;
};
template<class T> struct _Rb_tree_node : _Rb_tree_node_base { T value; };

template<class T,class Traits> struct _Rb_tree_iterator { _Rb_tree_node_base *_M_node; };
template<class D> class _Rb_global { public: static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base*); };

template<class K, class V, class S, class C, class A> class _Rb_tree {
	friend class ::Rva004FF8DA;
	template<class Key> _Rb_tree_node<V> *_M_find(const Key &) const;
 _Rb_tree_node<V> *_M_upper_bound(const K &) const;
public:
 _Rb_tree_node_base *header;
 char unknown04[8];
 unsigned count(const K &) const;
 pair<_Rb_tree_iterator<V,_Const_traits<V> >,_Rb_tree_iterator<V,_Const_traits<V> > > equal_range(const K &) const;

};
}

typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>,
	_STL::less<int>, _STL::allocator<IntIntPair> > IntIntTree;

struct BfmePod88 { int a[22]; };
struct UnitArray {
	BfmePod88 *first, *last, *limit;
	unsigned size() const { return (unsigned)(last - first); }
	BfmePod88 &operator[](int i) { return first[i]; }
};

class Rva004FF8DA
{
	char pad[0x38];
	IntIntTree tree;
 IntIntTree fightTree;
public:
	bool rva004FF8DA(int idx, int key);
	void *rva004FF910(int idx, int key);
 bool rva0050010D(int idx,int key);
};

int GetGameLogicRandomValue(int, int, char *, int);


class ModuleData;
struct BfmeE16 { float x,y,z,w; };
typedef _STL::pair<const int,void*> IntPtrPair;
typedef _STL::_Rb_tree<int,IntPtrPair,_STL::_Select1st<IntPtrPair>,_STL::less<int>,_STL::allocator<IntPtrPair> > IntPtrTree;
typedef _STL::pair<const unsigned,void*> UIntPtrPair;
typedef _STL::_Rb_tree<unsigned,UIntPtrPair,_STL::_Select1st<UIntPtrPair>,_STL::less<unsigned>,_STL::allocator<UIntPtrPair> > UIntPtrTree;
typedef _STL::vector<ModuleData const*,_STL::allocator<ModuleData const*> > PointerVector;
struct Out00418CC8 { int m_lo,m_hi; };
class LivingWorldAutoResolveCombatChain {
 public: bool getHighestPriorityTarget(Out00418CC8*);
};
// ?rva004FF910@Rva004FF8DA@@QAEPAXHH@Z
void *Rva004FF8DA::rva004FF910(int idx, int key)
{
	_STL::_Rb_tree_node<IntIntPair> *node = tree._M_find(key);
	UnitArray *&arr = *(UnitArray **)((char *)node + 0x14);
	UnitArray *v = &arr[idx];
	if (idx < 8 && v->size() > 0) {
		int chosen = GetGameLogicRandomValue(0, v->size() - 1,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIInformation.cpp", 246);
		return &(*v)[chosen];
	}
	for (unsigned i = 0; i < 8; ++i) {
		if (arr[i].size() > 0)
			return &arr[i][0];
	}
	return &arr[0][0];
}

// ?rva004FF8DA@Rva004FF8DA@@QAE_NHH@Z
bool Rva004FF8DA::rva004FF8DA(int idx, int key)
{
	_STL::_Rb_tree_node<IntIntPair> *node = tree._M_find(key);
	UnitArray *arr = *(UnitArray **)((char *)node + 0x14);
	UnitArray *v = &arr[idx];
	if (idx < 8 && v->size() > 0)
		return true;
	return false;
}

bool Rva004FF8DA::rva0050010D(int idx,int key) {
 int unitType=idx;
 if(unitType<8) {
  PointerVector keys;
  PointerVector *v=&keys;
  ((_STL::vector<void*>*)v)->erase((void**)v->begin(),(void**)v->end());
  _STL::_Rb_tree_node<IntIntPair> *outer=fightTree._M_find(key);
  UIntPtrTree &inner=*(UIntPtrTree*)((char*)outer+0x14);
  _STL::_Rb_tree_node_base *n=inner.header->left;
  while(n!=inner.header) {
   idx=*(int*)((char*)n+0x10);
   Out00418CC8 out={7,0};
   ((LivingWorldAutoResolveCombatChain*)idx)->getHighestPriorityTarget(&out);
   if(out.m_lo==unitType) v->push_back(*(ModuleData const**)&idx);
   n=inner._M_upper_bound(*(unsigned*)&idx);
  }
  ModuleData const **start=v->begin();
 unsigned size=v->end()-start;
  if(size>0) {
   int chosen=GetGameLogicRandomValue(0,size-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIInformation.cpp",217);
   int *selected=(int*)&start[chosen];
   idx=((IntPtrTree*)&inner)->count(*selected);
   if((unsigned)idx>0) {
    _STL::pair<_STL::_Rb_tree_iterator<IntPtrPair,_STL::_Const_traits<IntPtrPair> >,_STL::_Rb_tree_iterator<IntPtrPair,_STL::_Const_traits<IntPtrPair> > > range=((IntPtrTree*)&inner)->equal_range(*selected);
    _STL::_Rb_tree_node_base *found=range.first._M_node;
    int steps=GetGameLogicRandomValue(0,idx-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIInformation.cpp",224);
    for(int i=0;i<steps;++i) found=_STL::_Rb_global<bool>::_M_increment(found);
    return true;
   }
  }
 }
 return false;
}
