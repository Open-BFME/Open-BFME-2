// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// The body is folded across 4-byte vectors; its callees are the out-of-line
// __false_type __copy_ptrs (0x25BF40), __uninitialized_copy (0x1DD10D) and
// _M_allocate_and_copy (0x31B9EB), so the element is a non-POD-traited 4-byte record.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
#include <vector>

struct Rva0021C21BElement { char bytes[4]; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > & _STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> >::operator=(_STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > const &);

// Callers elsewhere reach this body through another spelling; bind it.
#pragma comment(linker, "/alternatename:?bfmeCopyOneCDF@BfmePartCDF@@QAEXPAU1@@Z=??4?$vector@URva0021C21BElement@@V?$allocator@URva0021C21BElement@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z")
