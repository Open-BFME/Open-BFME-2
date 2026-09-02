// ?_Init_timeinfo@_STL@@YAXAAV_Time_Info@1@@Z
// partial score=0.95 date=2026-09-02
// cl: -O2

// Locale-independent seed for _Time_Info: the "C" locale day/month names and
// the strftime patterns that go with them.  The tables live in the library's
// read-only data, so they are only declared here.

typedef int ptrdiff_t;
typedef unsigned int size_t;

extern "C" size_t __cdecl strlen(const char *);
#pragma intrinsic(strlen)

namespace _STL {

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Tp>
inline random_access_iterator_tag __iterator_category(const _Tp *) { return random_access_iterator_tag(); }

template <class _Tp>
inline ptrdiff_t *__distance_type(const _Tp *) { return 0; }

template <class _Container>
class back_insert_iterator
{
protected:
    _Container *container;

public:
    explicit back_insert_iterator(_Container &__x) : container(&__x) {}
    back_insert_iterator<_Container> &operator=(const typename _Container::value_type &__val)
    {
        container->push_back(__val);
        return *this;
    }
    back_insert_iterator<_Container> &operator*() { return *this; }
    back_insert_iterator<_Container> &operator++() { return *this; }
    back_insert_iterator<_Container> &operator++(int) { return *this; }
};

template <class _Container>
inline back_insert_iterator<_Container> back_inserter(_Container &__x)
{
    return back_insert_iterator<_Container>(__x);
}

// Out of line: the copy loop is shared by every container that can grow.
template <class _RandomAccessIter, class _OutputIter, class _Distance>
_OutputIter __copy(_RandomAccessIter __first, _RandomAccessIter __last, _OutputIter __result,
                   const random_access_iterator_tag &, _Distance *);

template <class _InputIter, class _OutputIter>
inline _OutputIter copy(_InputIter __first, _InputIter __last, _OutputIter __result)
{
    return __copy(__first, __last, __result, __iterator_category(__first), __distance_type(__first));
}

struct char_traits_char
{
    static size_t length(const char *__s) { return strlen(__s); }
};

class string
{
public:
    typedef char value_type;

    char *_M_start;
    char *_M_finish;
    char *_M_end_of_storage;

    void push_back(char __c);

    __forceinline string &operator=(const char *__s)
    {
        copy(__s, __s + char_traits_char::length(__s), back_inserter(*this));
        return *this;
    }
};

class _Time_Info
{
public:
    string _M_dayname[14];
    string _M_monthname[24];
    string _M_am_pm[2];
    string _M_time_format;
    string _M_date_format;
    string _M_date_time_format;
};

void _Init_timeinfo(_Time_Info &table);

} // namespace _STL

extern const char _dayname[14][14];
extern const char _monthname[24][24];

namespace _STL {

void _Init_timeinfo(_Time_Info &table)
{
    int __i;
    for (__i = 0; __i < 14; ++__i)
        table._M_dayname[__i] = _dayname[__i];
    for (__i = 0; __i < 24; ++__i)
        table._M_monthname[__i] = _monthname[__i];
    table._M_am_pm[0] = "AM";
    table._M_am_pm[1] = "PM";
    table._M_time_format = "%H:%M:%S";
    table._M_date_format = "%m/%d/%y";
    table._M_date_time_format = "%a %b %e %H:%M:%S %Y";
}

} // namespace _STL
