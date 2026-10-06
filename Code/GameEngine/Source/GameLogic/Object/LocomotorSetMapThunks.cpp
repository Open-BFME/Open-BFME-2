// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??1Rva004FFE81@@QAE@XZ @0x004FFE81 8B: pair-value style destructor thunk.
// Retail is add ecx 4 then jmp to the rowed LocomotorSet map Rb_tree dtor
// at 0x004FF5F3 (rowed via Code/GameEngine/Source/GameLogic/Object/LocomotorSetMapSubscript.cpp).
// Caller 0x00500CB8 destroys an array with stride 0x14 calling here with
// ecx set to each element so the map sits at +4 and the element size is 0x14.
// LocomotorSetType values from the Zero Hour donor
// (GameEngine/Include/GameLogic/Module/AIUpdate.h).

#include <map>
#include <vector>

class LocomotorTemplate;

enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,

	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,

	LOCOMOTORSET_COUNT
};

typedef _STL::vector<const LocomotorTemplate *> BfmeLocomotorTemplateVector;

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;

// Use the existing rowed tree bodies instead of emitting competing copies.
typedef _STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> BfmeLocomotorSetValue;
typedef _STL::_Rb_tree<LocomotorSetType, BfmeLocomotorSetValue,
    _STL::_Select1st<BfmeLocomotorSetValue>, _STL::less<LocomotorSetType>,
    _STL::allocator<BfmeLocomotorSetValue> > BfmeLocomotorSetTree;
namespace _STL {
template<> BfmeLocomotorSetTree::~_Rb_tree();
template<> BfmeLocomotorSetTree& BfmeLocomotorSetTree::operator=(const BfmeLocomotorSetTree&);
}

struct Rva004FFE81
{
	int m_first;
	BfmeLocomotorSetMap m_second;
	int m_third;	// +0x10: assignment 0x0050052F copies [edi+0x10] to [esi+0x10]; stride 0x14 in 0x00500CB8/0x0050094B
	~Rva004FFE81();
	Rva004FFE81& operator=(const Rva004FFE81&);
};

Rva004FFE81::~Rva004FFE81()
{
}

struct Rva004FFE89
{
	int m_first;
	int m_second;
	BfmeLocomotorSetMap m_map;
	~Rva004FFE89();
};

Rva004FFE89::~Rva004FFE89()
{
}

// ?Rva00500CB8Destroy@@YAXPAURva004FFE81@@0@Z @0x00500CB8 25B: range destroy.
// Destroys [first, last) with stride 0x14 calling ??1Rva004FFE81@@QAE@XZ.
// Callers 0x005011DA 0x0050126C 0x00501356 pass vector start/finish.
void __cdecl Rva00500CB8Destroy(Rva004FFE81 *first, Rva004FFE81 *last)
{
	for (; first != last; ++first)
		first->~Rva004FFE81();
}

extern "C" void __cdecl free(void *block);

// ?rva00501356@Rva00501356@@QAEXXZ @0x00501356 30B: vector storage helper.
// Destroys [m_first, m_last) via rowed 0x00500CB8 then frees m_first.
// Evidence: callees rowed 0x00500CB8 and 0x00030830; caller 0x00501A7C
// overwrites start/finish/end right after the call.
struct Rva00501356
{
	Rva004FFE81 *m_first;
	Rva004FFE81 *m_last;
	void rva00501356();
};

void Rva00501356::rva00501356()
{
	Rva00500CB8Destroy(m_first, m_last);
	if (m_first)
		free(m_first);
}

// Retail 0x0050052F / 37: assign the two scalar fields around the map.
// The call at 0x00500543 reaches the rowed tree assignment at 0x004FFDA5;
// the element's semantic name remains unknown.
Rva004FFE81& Rva004FFE81::operator=(const Rva004FFE81& other)
{
    m_first = other.m_first;
    m_second = other.m_second;
    m_third = other.m_third;
    return *this;
}

// Explicit STLport random-access copy. Retail 0x0050094B divides the
// pointer difference by 20 and calls the element assignment at 0x0050052F.
template Rva004FFE81* _STL::__copy<Rva004FFE81*, Rva004FFE81*, int>(
    Rva004FFE81*, Rva004FFE81*, Rva004FFE81*,
    const _STL::random_access_iterator_tag&, int*);

// The vector's nontrivial assignment dispatch reaches __copy at 0x0050094B.
template Rva004FFE81* _STL::__copy_ptrs<Rva004FFE81*, Rva004FFE81*>(
    Rva004FFE81*, Rva004FFE81*, Rva004FFE81*, const _STL::__false_type&);

// Native 0x0050126C has two pointer arguments, returns the first, copies
// [last, finish) into first and destroys the vacated tail before updating finish.
template Rva004FFE81* _STL::vector<Rva004FFE81>::erase(Rva004FFE81*, Rva004FFE81*);
