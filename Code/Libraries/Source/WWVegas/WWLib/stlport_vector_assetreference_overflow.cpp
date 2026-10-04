// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VAssetReference@@V?$allocator@VAssetReference@@@_STL@@@_STL@@IAEXPAVAssetReference@@ABV3@ABU__false_type@2@I_N@Z @0x000C9C17 178B
// STLport 4.5.3 vector<AssetReference>::_M_insert_overflow (false_type). Same
// size-optimised no-exceptions instantiation as stlport_vector_e16_noexc.cpp.
// Evidence: chain packet (calls 0x000C9A51 now rowed); callers 0x000C9D01 push_back
// overflow path passing pos=end count=1 atend=1; callees rowed copy 0x000C9308
// fill 0x000C932E construct 0x000C92F6 and allocate 0x00068E15; ICF twins pinned
// for the PAV copy and AssetReference allocate and _M_clear at 0x000C9A51.
#include <vector>

class AssetReference
{
public:
	AssetReference();
	AssetReference(const AssetReference &other);
	~AssetReference();
	AssetReference &operator=(const AssetReference &other);
	void *m_ref;
};

template class _STL::vector<AssetReference, _STL::allocator<AssetReference> >;
