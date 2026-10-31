// cl: /O1 /G7 /arch:SSE /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$vector@URva004F77E0Element@@V?$allocator@URva004F77E0Element@@@_STL@@@_STL@@QAE@XZ
// retail 0x005EC919 (63B EH). The same 63B shape as the rowed
// vector<TreeHintRef00217D4C> dtor 0x000806B4: destroy the range through the
// pinned _Destroy forwarder 0x005F97BC (symbols.csv pins this element view's
// _Destroy there as an ICF twin) and free the storage through 0x00030830.
// The element identity is an address-derived view; only the vector-dtor
// spelling is new, so the pin's element name carries the twin.
#include <vector>

struct Rva004F77E0Element
{
	void *m_ptr;
	~Rva004F77E0Element();
};

// Native 0x005F97BC forwards the range and an unused tag to the already
// owned 27-byte destroy loop at 0x004F72ED. Keep the observed cdecl stack ABI.
void __cdecl Rva004F72EDDestroy(void *, void *);
namespace _STL {
template <>
inline __declspec(noinline) void _Destroy<Rva004F77E0Element *>(Rva004F77E0Element *first, Rva004F77E0Element *last)
{
    __false_type tag;
    typedef void (__cdecl *NativeRangeDestroy)(void *, void *, const __false_type &);
    reinterpret_cast<NativeRangeDestroy>(&Rva004F72EDDestroy)(first, last, tag);
}
}

template _STL::vector<Rva004F77E0Element>::~vector();
