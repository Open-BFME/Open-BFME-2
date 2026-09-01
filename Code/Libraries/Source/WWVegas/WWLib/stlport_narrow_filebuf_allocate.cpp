// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_filebuf<char>::_M_allocate_buffers(char *, streamsize).
// The member offsets come straight out of the retail body: _M_int_buf_dynamic
// at 0x66, _M_int_buf at 0x6C, _M_int_buf_EOS at 0x70, _M_ext_buf at 0x74,
// _M_ext_buf_EOS at 0x78 and _M_codecvt at 0xA0. The two virtuals sit at
// slots 4 and 7 - encoding at 0x10 and max_length at 0x1C - which is fixed by
// the ORDER retail calls them in: MSVC 7.1 evaluates the outer max's arguments
// right to left, so max_length goes first and lands on the 0x1C slot.

typedef unsigned int size_t;
typedef int streamsize;

extern "C" __declspec(dllimport) void *__cdecl malloc(size_t size);

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
inline const T &(max)(const T &a, const T &b)
{
	return a < b ? b : a;
}

class codecvt_base
{
public:
	virtual ~codecvt_base();
	virtual int do_out();
	virtual int do_in();
	virtual int do_unshift();
	virtual int encoding() const;
	virtual int do_length();
	virtual int always_noconv();
	virtual int max_length() const;
};

template <class CharT, class Traits>
class basic_filebuf
{
private:
	bool _M_allocate_buffers(CharT *buf, streamsize n);
	void _M_deallocate_buffers();

	unsigned char _M_pad0[0x66];
	bool _M_int_buf_dynamic;
	unsigned char _M_pad1[5];
	CharT *_M_int_buf;
	CharT *_M_int_buf_EOS;
	char *_M_ext_buf;
	char *_M_ext_buf_EOS;
	unsigned char _M_pad2[0xA0 - 0x7C];
	codecvt_base *_M_codecvt;
};

template <class CharT, class Traits>
bool basic_filebuf<CharT, Traits>::_M_allocate_buffers(CharT *__buf, streamsize __n)
{
	if (__buf == 0)
	{
		_M_int_buf = static_cast<CharT *>(malloc(__n * sizeof(CharT)));
		if (!_M_int_buf)
			return false;
		_M_int_buf_dynamic = true;
	}
	else
	{
		_M_int_buf = __buf;
		_M_int_buf_dynamic = false;
	}

	size_t __ebufsiz = (max)(__n * (max)(_M_codecvt->encoding(), 1),
			streamsize(_M_codecvt->max_length()));

	_M_ext_buf = static_cast<char *>(malloc(__ebufsiz));
	if (!_M_ext_buf)
	{
		_M_deallocate_buffers();
		return false;
	}

	_M_int_buf_EOS = _M_int_buf + __n;
	_M_ext_buf_EOS = _M_ext_buf + __ebufsiz;
	return true;
}

template class basic_filebuf<char, char_traits<char> >;

}
