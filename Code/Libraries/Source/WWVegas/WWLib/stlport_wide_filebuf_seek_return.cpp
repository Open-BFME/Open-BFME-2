// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_filebuf<wchar_t>::_M_seek_return, the wide twin of
// 0x000143D0. The four mode flags sit at 0x37..0x3A rather than 0x67..0x6A,
// the same 0x30 shift the rest of the wide filebuf carries - but the get and
// put areas are NOT the same shape: the wide streambuf holds its six pointers
// directly at +4 through +0x18, where the narrow one reaches them through two
// pointers at +4 and +8. That is the whole four-byte size difference.

namespace _STL
{

template <class T>
class char_traits {};

template <class StateT>
class fpos
{
public:
	fpos(long off) : _M_pos(off), _M_st(0) {}

	long _M_pos;
	StateT _M_st;
};

template <class CharT, class Traits>
class basic_filebuf
{
private:
	fpos<int> _M_seek_return(long off, int state);

	void _M_exit_input_mode();

	void setg(CharT *begin, CharT *next, CharT *end)
	{
		_M_gbegin = begin;
		_M_gnext = next;
		_M_gend = end;
	}

	void setp(CharT *begin, CharT *end)
	{
		_M_pbegin = begin;
		_M_pnext = begin;
		_M_pend = end;
	}

	void *_M_vptr;
	CharT *_M_gbegin;
	CharT *_M_gnext;
	CharT *_M_gend;
	CharT *_M_pbegin;
	CharT *_M_pnext;
	CharT *_M_pend;
	unsigned char _M_pad0[0x37 - 0x1C];
	bool _M_in_input_mode;
	bool _M_in_output_mode;
	bool _M_in_error_mode;
	bool _M_in_putback_mode;
};

template <class CharT, class Traits>
fpos<int> basic_filebuf<CharT, Traits>::_M_seek_return(long off, int state)
{
	if (off != -1)
	{
		if (_M_in_input_mode)
			_M_exit_input_mode();
		_M_in_input_mode = false;
		_M_in_output_mode = false;
		_M_in_putback_mode = false;
		_M_in_error_mode = false;
		setg(0, 0, 0);
		setp(0, 0);
	}

	fpos<int> result(off);
	result._M_st = state;
	return result;
}

template class basic_filebuf<unsigned short, char_traits<unsigned short> >;

}
