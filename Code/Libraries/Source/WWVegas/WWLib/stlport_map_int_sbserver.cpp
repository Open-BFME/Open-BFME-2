// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport map<int, SBServer> backing the PeerThread staging-server table.
// SBServer is a 4-byte refcounted server handle: copying one copies the
// handle word and takes a reference on the underlying server object, which is
// why the pair copy stays a real call instead of folding to a pointer move.
// Retail builds this unit without C++ exceptions, so _STLP_NO_EXCEPTIONS keeps
// the node-creation path free of unwind frames; the narrow allocator shim
// rebinds node allocation to the rowed 0x307F0 byte allocator.

// 4-byte handle. The copy keeps retail's shape: copy the word first, then
// AddRef the referent through its double-dereferenced slot when non-null.
struct SBServer
{
    void *m_handle;
    SBServer();
    __declspec(noinline) SBServer(const SBServer &src);
    __declspec(noinline) ~SBServer();
};

__declspec(noinline) SBServer::SBServer(const SBServer &src)
{
    void *handle = src.m_handle;
    m_handle = handle;
    if (handle != 0) {
        void *slot = *(void **)handle;
        char *obj = (char *)((void **)slot)[1] + (unsigned int)handle;
        ++*(int *)(obj + 4);
    }
}

#include <map>

// Teardown shares the rowed 0x7DEEF release helper: it computes the same
// slot-derived object and tail-jumps to it (the fastcall argument is already
// in ecx). Declaration mirrors TreeHintRefReleaseBFME2.cpp.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
extern void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

__declspec(noinline) SBServer::~SBServer()
{
    void *handle = m_handle;
    if (handle != 0) {
        void *slot = *(void **)handle;
        char *obj = (char *)((void **)slot)[1] + (unsigned int)handle;
        ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)obj);
    }
}

namespace _STL {

// Retail guards the placement construction with an explicit null check on the
// destination (the je lands on the trailing ret): model it as an explicit
// specialization so the mangled _Construct name is preserved.
template <>
inline void _Construct<_STL::pair<const int, SBServer>, _STL::pair<const int, SBServer> >(
    _STL::pair<const int, SBServer> *dest, const _STL::pair<const int, SBServer> &src)
{
    if (dest != 0) {
        new (dest) _STL::pair<const int, SBServer>(src);
    }
}

} // namespace _STL

template class _STL::map<int, SBServer, _STL::less<int>, _STL::allocator<_STL::pair<const int, SBServer> > >;
