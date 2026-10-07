// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 0x4613EB destroys 12B Link elements through the clearer at
// 0x003F29F8 (stride 0xC, per-element destruction through 0x0007FAB3),
// then frees the vector storage. Target 0x003F29F8 is the element
// clearer loop; target 0x0007FAB3 is the element dtor itself (null-checked
// free of the owned pointer at +0). Link elements are therefore 12B owner
// records; interiors are positional (the dtor proves +0 is an owned
// pointer, the rest is unproven). StlportAsciiStringVectorDtor precedent
// (explicit instantiation emits the foldable family).
#include <vector>

extern "C" void _free(void *ptr);

struct DynamicPortalLink
{
	void *m_owned;
	int m_second;
	int m_third;
	~DynamicPortalLink();
};

template _STL::vector<DynamicPortalLink>::~vector();

// ?rva0032E7E2@Rva0032E7E2@@QAEXXZ — RVA 0x0032E7E2, 30B.
// Vector storage teardown: destroy range [start finish) via the rowed
// _Destroy at 0x003F29F8, then free start via the rowed _free at 0x00030830.
// Evidence: retail push [esi+4] push [esi] plus call 0x003F29F8,
// mov esi [esi] plus test, push esi plus call 0x00030830;
// prev 0x0032E7A3 same TU and flags, same Link Destroy callee.
extern "C" void free(void *p);

class Rva0032E7E2
{
public:
	void rva0032E7E2();
	DynamicPortalLink *m_start;
	DynamicPortalLink *m_finish;
};

void Rva0032E7E2::rva0032E7E2()
{
	_STL::_Destroy(m_start, m_finish);
	if (m_start != 0)
		free(m_start);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1DynamicPortalLinkVec@@QAE@XZ=??1?$vector@UDynamicPortalLink@@V?$allocator@UDynamicPortalLink@@@_STL@@@_STL@@QAE@XZ")
