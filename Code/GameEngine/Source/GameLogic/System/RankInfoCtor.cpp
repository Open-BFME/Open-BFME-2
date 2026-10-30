// cl: /DNDEBUG /MD /EHsc
// stlport46
//
// ??0RankInfo@@QAE@XZ,
// retail 0x0020010B, 76 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/System/RankInfoConstructorThunk.cpp,
// RankInfo::RankInfo): BFME2 layout measured from retail (vector at +0x38,
// seven -1 words at +0x18..+0x30, zeros at +0x10/+0x14/+0x34, -1 at +0x0C).

#include <vector>
// bfme link decl-only begin
// The 4.6 member binds the native 28-byte provider in VectorObjectIDFillInsert.cpp.
namespace _STL { template <> int * allocator<int>::allocate(unsigned int, void const *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@HV?$allocator@H@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<int, allocator<int> >::_M_clear(); }

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

// The science vector's assignment is the rowed body at 0x0021C21B
// (StlSweepW5Rva0021C21B.cpp); call it by that row's name.
struct Rva0021C21BElement { char bytes[4]; };
namespace _STL { template <> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &); }

typedef int Int;

class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isAllocatedOverride(0), m_extra0C(-1) {}
	virtual ~Overridable();
	Overridable &operator=(const Overridable &that);

private:
	Overridable *m_nextOverride; // +0x04
	unsigned char m_isAllocatedOverride; // +0x08
	Int m_extra0C; // +0x0C, -1 (BFME2-new third Overridable word)
};

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	void set(const StringBase &that);

private:
	void *m_data;
};

class RankInfo : public Overridable
{
public:
	RankInfo();
	virtual ~RankInfo();
	RankInfo &operator=(const RankInfo &that);

private:
	StringBase<wchar_t> m_rankName; // +0x10, null
	Int m_skillPointsNeeded; // +0x14, 0
	Int m_skillPointsNeededCampaign; // +0x18, -1
	Int m_skillPointsNeededMen; // +0x1C, -1
	Int m_skillPointsNeededElves; // +0x20, -1
	Int m_skillPointsNeededDwarves; // +0x24, -1
	Int m_skillPointsNeededIsengard; // +0x28, -1
	Int m_skillPointsNeededMordor; // +0x2C, -1
	Int m_skillPointsNeededWild; // +0x30, -1
	Int m_sciencePurchasePointsGranted; // +0x34, 0
	_STL::vector<Int> m_sciencesGranted; // +0x38
};

// ??0RankInfo@@QAE@XZ
RankInfo::RankInfo()
{
	m_skillPointsNeeded = 0;
	m_skillPointsNeededCampaign = -1;
	m_skillPointsNeededMen = -1;
	m_skillPointsNeededElves = -1;
	m_skillPointsNeededDwarves = -1;
	m_skillPointsNeededIsengard = -1;
	m_skillPointsNeededMordor = -1;
	m_skillPointsNeededWild = -1;
	m_sciencePurchasePointsGranted = 0;
}

// ??4RankInfo@@QAEAAV0@ABV0@@Z
RankInfo &RankInfo::operator=(const RankInfo &that)
{
	Overridable::operator=(that);
	m_rankName.set(that.m_rankName);
	m_skillPointsNeeded = that.m_skillPointsNeeded;
	m_skillPointsNeededCampaign = that.m_skillPointsNeededCampaign;
	m_skillPointsNeededMen = that.m_skillPointsNeededMen;
	m_skillPointsNeededElves = that.m_skillPointsNeededElves;
	m_skillPointsNeededDwarves = that.m_skillPointsNeededDwarves;
	m_skillPointsNeededIsengard = that.m_skillPointsNeededIsengard;
	m_skillPointsNeededMordor = that.m_skillPointsNeededMordor;
	m_skillPointsNeededWild = that.m_skillPointsNeededWild;
	m_sciencePurchasePointsGranted = that.m_sciencePurchasePointsGranted;
	reinterpret_cast<_STL::vector<Rva0021C21BElement> &>(m_sciencesGranted) =
		reinterpret_cast<const _STL::vector<Rva0021C21BElement> &>(that.m_sciencesGranted);
	return *this;
}

// The vector<Int> allocate-and-copy worker (0x0053BD39) lives in this unit.
template int *_STL::vector<int, _STL::allocator<int> >::_M_allocate_and_copy<const int *>(size_t, const int *, const int *);
