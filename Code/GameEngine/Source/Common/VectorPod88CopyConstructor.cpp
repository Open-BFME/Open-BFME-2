// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// Nested-vector copy and append use the existing retail helper providers.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct BfmePod88
{
	char m_body[88];
};
namespace _STL { template <> vector<BfmePod88, allocator<BfmePod88> >::~vector(); }

// The outer clear and placement copy have existing out-of-line providers.
namespace _STL {
template <> void vector<vector<BfmePod88> >::_M_clear();
typedef vector<BfmePod88> Pod88Vector;
typedef vector<Pod88Vector> Pod88VectorVector;
template <> void _Construct<Pod88Vector, Pod88Vector>(Pod88Vector *, const Pod88Vector &);

template <> inline Pod88Vector *__uninitialized_fill_n<Pod88Vector *, unsigned int, Pod88Vector>(
    Pod88Vector *first, unsigned int count, const Pod88Vector &value, const __false_type &)
{
    Pod88Vector *current = first;
    for (; count > 0; --count, ++current)
        _Construct(current, value);
    return current;
}
// Retail's overflow path propagates allocation/copy failure without cleanup.
// ?vector<Pod88Vector>::_M_insert_overflow present-unmatched
template <> inline void vector<Pod88Vector>::_M_insert_overflow(
    pointer position, const Pod88Vector &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer newStart = this->_M_end_of_storage.allocate(length);
    pointer newFinish = newStart;
    newFinish = __uninitialized_copy((const Pod88Vector *)this->_M_start,
        (const Pod88Vector *)position, newStart, __false_type());
    if (fillLength == 1) {
        _Construct(newFinish, value);
        ++newFinish;
    } else {
        newFinish = __uninitialized_fill_n(newFinish, fillLength, value, __false_type());
    }
    if (!atEnd)
        newFinish = __uninitialized_copy((const Pod88Vector *)position,
            (const Pod88Vector *)this->_M_finish, newFinish, __false_type());
    _M_clear();
    _M_set(newStart, newFinish, newStart + length);
}
}

template _STL::vector<_STL::Pod88Vector>::vector(const _STL::Pod88VectorVector &);
template void _STL::Pod88VectorVector::push_back(const _STL::Pod88Vector &);
