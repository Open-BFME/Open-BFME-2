// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail boundaries: 004FF8DA..004FF910 (54B), 004FF910..004FF98D (125B).
// WB12FC890 supports LivingWorldAIBuildingTypes::GetUnitOfType for the latter.
// Retail proves the tree at receiver+38, its mapped pointer at node+14,
// eight 12-byte vector views and 88-byte elements. Their full types are unknown.
// Keep RVA owner/method names and partial call views; do not claim allocation
// layouts or emit competing STL helpers. Both use the rowed int-key _M_find
// at 00388F63; the random call is the named provider at 00233FF4.
class Rva004FF8DA;

namespace _STL {
template<class A, class B> struct pair { A first; B second; };
template<class T> struct _Select1st {};
template<class T> struct less {};
template<class T> class allocator {};
template<class T> struct _Rb_tree_node;
template<class K, class V, class S, class C, class A> class _Rb_tree {
	friend class ::Rva004FF8DA;
	template<class Key> _Rb_tree_node<V> *_M_find(const Key &) const;
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
public:
	bool rva004FF8DA(int idx, int key);
	void *rva004FF910(int idx, int key);
};

int GetGameLogicRandomValue(int, int, char *, int);

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
