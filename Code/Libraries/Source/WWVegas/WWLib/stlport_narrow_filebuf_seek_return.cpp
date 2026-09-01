// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_filebuf<char>::_M_seek_return. On a real position it
// leaves input mode and clears the four mode flags at 0x67..0x6A, then blanks
// the get and put areas through the two pointers at +4 and +8, and finally
// builds the fpos in the caller's return slot.

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

template <class CharT>
struct _Stream_area
{
	CharT *_M_begin;
	CharT *_M_next;
	CharT *_M_end;
};

template <class CharT, class Traits>
class basic_filebuf
{
private:
	fpos<int> _M_seek_return(long off, int state);

	void _M_exit_input_mode();

	void setg(CharT *begin, CharT *next, CharT *end)
	{
		_Stream_area<CharT> *area = _M_get_area;
		area->_M_end = end;
		area->_M_begin = begin;
		area->_M_next = next;
	}

	void setp(CharT *begin, CharT *end)
	{
		_Stream_area<CharT> *area = _M_put_area;
		area->_M_end = end;
		area->_M_begin = begin;
		area->_M_next = begin;
	}

	void *_M_vptr;
	_Stream_area<CharT> *_M_get_area;
	_Stream_area<CharT> *_M_put_area;
	unsigned char _M_pad0[0x67 - 0x0C];
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

template class basic_filebuf<char, char_traits<char> >;

}
