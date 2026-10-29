// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
// list<Rva0024076D>::push_back @0x00248211 and its insert @0x00247089, which
// creates the node through _M_create_node 0x002461F1. 0x0024877A inserts into
// its record list through 0x00247089.
#include <list>
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@VRva0024076D@@V?$allocator@VRva0024076D@@@_STL@@@_STL@@IAEPAU?$_Lis:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva0024076D;
namespace _STL { template <> _List_node<Rva0024076D> * list<Rva0024076D,allocator<Rva0024076D> >::_M_create_node(Rva0024076D const &); }
// The 0x50-byte record whose dtor is 0x00240831 (Rva0024076DCtor.cpp).
class Rva0024076D {
public:
	// Copy ctor: the rowed out-of-line 0x002419E2 (Rva0024314ARecordCopy.cpp).
	Rva0024076D(const Rva0024076D &);
	~Rva0024076D();
private:
	char m_pad[0x50];
};
template void _STL::list<Rva0024076D>::push_back(const Rva0024076D &);
