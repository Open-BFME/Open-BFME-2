// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Time_Info default constructor, the mirror of the destructor
// at 0x00007A00. Three array constructions through the compiler's eh vector
// constructor iterator - 14, 24 and 2 elements of 12 bytes, each handed the
// string's default constructor at 0x00007850 and its destructor at 0x00142D70
// for the unwind - then the five scalar strings one at a time.

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string();
	~basic_string();

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class _Time_Info
{
public:
	_Time_Info();

	string _M_dayname[14];
	string _M_monthname[24];
	string _M_am_pm[2];
	string _M_time_format;
	string _M_date_format;
	string _M_date_time_format;
	string _M_long_date_format;
	string _M_long_date_time_format;
};

_Time_Info::_Time_Info()
{
}

}
