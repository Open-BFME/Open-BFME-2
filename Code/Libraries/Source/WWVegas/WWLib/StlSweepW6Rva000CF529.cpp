// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

// The native loop proves an eight-byte stride and calls the already verified
// placement-copy owner directly. Keep only that neutral footprint here;
// original element identity and the provider's inherited type view are unknown.
struct Rva000CF529Element { unsigned words[2]; };
struct TreeKey00242F5E;
void Rva000CF4D6Construct(TreeKey00242F5E *, const TreeKey00242F5E &);

#include <vector>

namespace _STL {
// Specialize the reference operation after its declaration so this forwarding
// glue also applies when the containing TU has already included <vector>.
// Its force-inlined body has no separate retail entry.
// ?_STL::_Construct absent-from-retail
template <> __forceinline void _Construct<Rva000CF529Element, Rva000CF529Element>(Rva000CF529Element *destination,
                                    const Rva000CF529Element &value)
{
    Rva000CF4D6Construct(reinterpret_cast<TreeKey00242F5E *>(destination),
        *reinterpret_cast<const TreeKey00242F5E *>(&value));
}

// The element has no destructor work. A direct specialization preserves the
// reference loop without its empty cleanup/rethrow handler when another TU
// has included STLport with exception support enabled.
template <> Rva000CF529Element * __uninitialized_fill_n<Rva000CF529Element *, unsigned int, Rva000CF529Element>(
    Rva000CF529Element *destination, unsigned int count,
    const Rva000CF529Element &value, const __false_type &)
{
    Rva000CF529Element *current = destination;
    for (; count > 0; --count, ++current)
        _Construct(current, value);
    return current;
}
}
