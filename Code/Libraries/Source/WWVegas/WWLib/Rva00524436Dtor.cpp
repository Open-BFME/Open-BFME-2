// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00524436@@QAE@XZ @0x00524436 65B evidence: dtor via rowed clear 0x00523F8C plus the independent vector at +0xc via 0x005243BB plus vector AsciiString at +0 via 0x0002CC70; callers 0x005248D0 0x0052634F 0x0052936C 0x005C7954
#include <vector>

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

// The native +C member calls its own 5243BB destructor, not the canonical
// vector<CameraMarker> at CF60B. Use that recovered twelve-byte member view
// directly so the linker selects the same callee as the native call/EH path.
// The original template/element identity remains unknown.
struct Rva005243BBVector
{
	~Rva005243BBVector();
	void *m_start;
	void *m_finish;
	void *m_end;
};

#include "Rva00524021.h"

class Rva00524436
{
public:
	~Rva00524436();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
	Rva005243BBVector m_0c;
};

Rva00524436::~Rva00524436()
{
	((Rva00524021 *)this)->rva00523F8C();
}
