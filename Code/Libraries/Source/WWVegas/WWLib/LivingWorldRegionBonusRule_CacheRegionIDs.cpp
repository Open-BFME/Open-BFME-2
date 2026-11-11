// cl: /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?CacheRegionIDs@LivingWorldRegionBonusRule@@QAEXPAVRva00210390@@@Z @0x002103B6 119B: clear Science vector at +0x2C, reserve src count at +0x20, resolve each AsciiString via rowed 0x00210390.
// Evidence: retail erase 0x00532803 on [edi]/[edi+4], reserve 0x002A1410 of (0x24-0x20)>>2, loop lea+push into rowed 0x00210390 with this=[ebp+8], [eax+0x12C] or -1 into push_back 0x002E01C6; caller 0x00210714.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

#include "ascii_string.h"

#include "Rva00210390.h"

enum ScienceType
{
	SCIENCE_INVALID = -1
};

struct Rva002103B6Node
{
	char m_pad[0x12C];
	ScienceType m_science;
};

class LivingWorldRegionBonusRule
{
public:
	void CacheRegionIDs(Rva00210390 *lookup);
private:
	char m_pad00[0x20];
	_STL::vector<AsciiString> m_src20;
	_STL::vector<ScienceType> m_dst2C;
};

// bfme link decl-only begin
namespace _STL { template <> template <> ScienceType * vector<ScienceType,_STL::allocator<ScienceType> >::_M_allocate_and_copy<ScienceType *>(unsigned int,ScienceType *,ScienceType *); }
namespace _STL { template <> void vector<ScienceType,_STL::allocator<ScienceType> >::_M_clear(); }
namespace _STL { template <> void vector<ScienceType,_STL::allocator<ScienceType> >::_M_insert_overflow(ScienceType *,ScienceType const &,_STL::__false_type const &,unsigned int,bool); }
namespace _STL { template <> ScienceType * _STLP_alloc_proxy<ScienceType *,ScienceType,_STL::allocator<ScienceType> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> ScienceType * allocator<ScienceType>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ScienceType *,ScienceType,_STL::allocator<ScienceType> >::deallocate(ScienceType *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<ScienceType>::deallocate(ScienceType *,unsigned int) const; }
namespace _STL { template <> void vector<ScienceType,_STL::allocator<ScienceType> >::reserve(unsigned int); }
namespace _STL { template <> void vector<ScienceType,_STL::allocator<ScienceType> >::push_back(ScienceType const &); }
// bfme link decl-only end
void LivingWorldRegionBonusRule::CacheRegionIDs(Rva00210390 *lookup)
{
	_STL::vector<ScienceType> &dst = m_dst2C;
	dst.erase(dst.begin(), dst.end());
	dst.reserve(m_src20.size());
	for (unsigned int i = 0; i < m_src20.size(); ++i) {
		void *node = lookup->rva00210390(&m_src20[i]);
		int v;
		if (node)
			v = ((Rva002103B6Node *)node)->m_science;
		else
			v = -1;
		dst.push_back((ScienceType)v);
	}
}
