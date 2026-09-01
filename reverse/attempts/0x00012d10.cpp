// ?_M_insert_aux@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEPAGPAGG@Z
// partial score=0.96 date=2026-09-02
// ?_M_insert_aux@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEPAGPAGG@Z
// partial score=0.96 date=2026-09-02
//
// The wide twin of the _M_insert_aux landed at 0x00011D20, name taken from the
// reloc-derived table. Two corrections to the narrow unit carry it most of the
// way: the traits move takes a BYTE count so the element count doubles, and
// __copy_trivial is a DECLARATION here - retail calls 0x000179B0 twice where
// the narrow unit inlines the memmove, and inlining it costs 57 bytes.
//
// 240 bytes against 232, and every one of those eight is the same choice:
// retail keeps the position parameter in ebx, MSVC 7.1 keeps it in ebp, and
// [ebp] needs a displacement byte that [ebx] does not. Nothing else differs -
// normalise the two registers and the disassembly is identical throughout.
// -G7 gives 236 by folding one memory operand differently but still picks ebp;
// -O2 and -Ox give 240.
//
// The narrow twin, which does inline __copy_trivial, gets ebx. That extra
// register pressure is the most likely lever and is what the next attempt
// should reach for - something that occupies ebp without changing the calls.

// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<wchar_t>::_M_insert_aux, the wide twin of
// 0x00011D20. Same body; the character type carries through the traits move
// (a byte count, so twice the element count), the uninitialized_copy and the
// proxy's sizeof multiply.

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
        __new_finish = __new_start + (__new_pos - __new_start + 1);
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
