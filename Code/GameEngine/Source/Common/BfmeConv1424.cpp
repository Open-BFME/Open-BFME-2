// cl: /Od /Gy

// STLport 4.5.2 allocator guard constructors, from
// vendor/stlport/stl/_alloc.c:126-150 (_config.h:56 identifies the release).
// Keep the real lock statics and call the rowed mutex implementation through
// its existing view; no additional global or callee identity is introduced.
namespace _STL
{
class _STLP_mutex_base
{
public:
    void _M_acquire_lock();
};

class NodeAllocMutex;

template <bool __threads, int __inst>
class _Node_Alloc_Lock
{
public:
    _Node_Alloc_Lock();
    static NodeAllocMutex _S_lock;
};

template <bool __threads, int __inst>
_Node_Alloc_Lock<__threads, __inst>::_Node_Alloc_Lock()
{
    if (__threads)
        ((_STLP_mutex_base *)&_S_lock)->_M_acquire_lock();
}

template class _Node_Alloc_Lock<false, 0>;
template class _Node_Alloc_Lock<true, 0>;
}
