// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<wchar_t>::_M_insert_aux, the wide twin of
// 0x00011D20. Same body; the character type carries through the traits move
// (a byte count, so twice the element count), the uninitialized_copy and the
// proxy's sizeof multiply. __copy_trivial is a DECLARATION here where the
// narrow unit defines it inline: retail calls 0x000179B0 twice, and inlining
// the memmove costs 57 bytes.
//
// Two shapes in the else branch are load-bearing, and they pull in opposite
// directions - a previous attempt sat eight bytes long with each of them
// picked the other way round:
//
//   * `__new_finish = __new_pos + 1` and not the equivalent through
//     __new_start. Written the long way MSVC 7.1 keeps the position parameter
//     in ebp instead of ebx, and every [ebp] needs the displacement byte that
//     [ebx] does not.
//   * `__extra` has to be its own named constant. Folded into the __len
//     expression the growth term becomes the base of the `lea` that adds it
//     to the old length, and retail has the old length there.

typedef unsigned int size_t;

extern "C" __declspec(dllimport) void *__cdecl memmove(void *destination,
    const void *source, size_t count);
extern "C" void __cdecl free(void *block);

inline void *operator new(size_t, void *place)
{
    return place;
}

namespace _STL
{

template <class T>
inline const T &(max)(const T &a, const T &b)
{
    return a < b ? b : a;
}

template <class T1, class T2>
inline void _Construct(T1 *p, const T2 &value)
{
    new (p) T1(value);
}

// Retail calls this rather than inlining it, which the narrow twin does not.
void *__cdecl __copy_trivial(const void *first, const void *last, void *result);

inline unsigned short *uninitialized_copy(const unsigned short *first,
    const unsigned short *last, unsigned short *result)
{
    return (unsigned short *)__copy_trivial(first, last, result);
}

template <class T>
class char_traits {};

template <>
class char_traits<unsigned short>
{
public:
    static unsigned short *__cdecl move(unsigned short *s1, const unsigned short *s2,
        size_t size)
    {
        return size == 0 ? s1 : (unsigned short *)memmove(s1, s2, size * 2);
    }
    static void __cdecl assign(unsigned short &c1, const unsigned short &c2) { c1 = c2; }
};

template <class T>
class allocator
{
public:
    static T *allocate(size_t count, const void *hint);
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
    Value *allocate(size_t count)
    {
        return count != 0 ? Alloc::allocate(count * sizeof(Value), 0) : 0;
    }
    void deallocate(Value *block, size_t)
    {
        if (block != 0)
            free(block);
    }

    Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
    typedef CharT *pointer;
    typedef unsigned int size_type;

    size_type size() const
    {
        return static_cast<size_type>(_M_finish - _M_start);
    }

private:
    pointer _M_insert_aux(CharT *position, CharT value);

    void _M_construct_null(CharT *p) { *p = 0; }
    void _M_deallocate_block()
    {
        _M_end_of_storage.deallocate(_M_start,
            static_cast<size_type>(_M_end_of_storage._M_data - _M_start));
    }

    CharT *_M_start;
    CharT *_M_finish;
    _STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
typename basic_string<CharT, Traits, Alloc>::pointer
basic_string<CharT, Traits, Alloc>::_M_insert_aux(CharT *__p, CharT __c)
{
    pointer __new_pos = __p;
    if (_M_finish + 1 < _M_end_of_storage._M_data) {
        _M_construct_null(_M_finish + 1);
        Traits::move(__p + 1, __p, _M_finish - __p);
        Traits::assign(*__p, __c);
        ++_M_finish;
    }
    else {
        const size_type __old_len = size();
        const size_type __extra = (max)(__old_len, static_cast<size_type>(1));
        const size_type __len = __old_len + __extra + 1;
        pointer __new_start = _M_end_of_storage.allocate(__len);
        pointer __new_finish = __new_start;
        __new_pos = uninitialized_copy(_M_start, __p, __new_start);
        _Construct(__new_pos, __c);
        __new_finish = __new_pos + 1;
        __new_finish = uninitialized_copy(__p, _M_finish, __new_finish);
        _M_construct_null(__new_finish);
        _M_deallocate_block();
        _M_start = __new_start;
        _M_finish = __new_finish;
        _M_end_of_storage._M_data = __new_start + __len;
    }
    return __new_pos;
}

template basic_string<unsigned short, char_traits<unsigned short>,
    allocator<unsigned short> >::pointer
basic_string<unsigned short, char_traits<unsigned short>,
    allocator<unsigned short> >::_M_insert_aux(unsigned short *, unsigned short);

}
