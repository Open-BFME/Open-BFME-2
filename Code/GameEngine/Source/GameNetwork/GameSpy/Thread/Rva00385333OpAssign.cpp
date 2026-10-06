// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
// ??4Rva00385333@@QAEAAV0@ABV0@@Z 0x00387A68 91B
// Evidence: pin operator= tournament block; calls Rva003844D7 operator= 0x3874F9 and basic_string assign 0x120C0; LINK 2 files wait.
typedef int Int;

namespace _STL
{
template <class T> class char_traits {};
template <class T> class allocator {};
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
	basic_string<CharT, Traits, Alloc> &assign(const basic_string<CharT, Traits, Alloc> &that);
private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};
}

class Rva003844D7
{
public:
	Rva003844D7 &operator=(const Rva003844D7 &that);
	char m_pad[0x190];
};

class Rva00385333 : public Rva003844D7
{
public:
	Rva00385333 &operator=(const Rva00385333 &that);
private:
	unsigned short m_190;
	unsigned short m_192;
	Int m_194;
	Int m_198;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_19C;
};

Rva00385333 &Rva00385333::operator=(const Rva00385333 &that)
{
	Rva003844D7::operator=(that);
	m_190 = that.m_190;
	m_192 = that.m_192;
	m_194 = that.m_194;
	m_198 = that.m_198;
	m_19C.assign(that.m_19C);
	return *this;
}
