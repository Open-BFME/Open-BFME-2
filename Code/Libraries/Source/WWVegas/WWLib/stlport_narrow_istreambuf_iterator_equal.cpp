// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow istreambuf_iterator::equal. Both the cache fill and
// the streambuf's sgetc inline into this body, so the whole get area -- the
// FILE the narrow specialization keeps its read pointer and count in -- has
// to be visible here.

namespace _STL
{

template <class T>
class char_traits {};

template <>
class char_traits<char>
{
public:
	typedef int int_type;
};

struct _Get_area
{
	char *_M_next;
	int _M_count;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	__declspec(dllimport) __forceinline typename Traits::int_type sgetc()
	{
		_Get_area *area = _M_get;
		if (area->_M_count > 0)
			return static_cast<unsigned char>(*area->_M_next);

		return underflow();
	}

protected:
	virtual ~basic_streambuf();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual typename Traits::int_type underflow();

private:
	_Get_area *_M_get;
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	bool equal(const istreambuf_iterator &other) const;

private:
	__declspec(dllimport) __forceinline void _M_getc() const
	{
		if (_M_have_c)
			return;

		typename Traits::int_type value = _M_buf->sgetc();
		_M_c = static_cast<CharT>(value);
		_M_eof = value == static_cast<typename Traits::int_type>(-1);
		_M_have_c = true;
	}

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
bool istreambuf_iterator<CharT, Traits>::equal(
		const istreambuf_iterator &other) const
{
	if (_M_buf != 0)
		_M_getc();
	if (other._M_buf != 0)
		other._M_getc();

	return _M_eof == other._M_eof;
}

template class istreambuf_iterator<char, char_traits<char> >;

}
