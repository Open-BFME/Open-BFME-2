// cl: /EHs /O1 /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva001F949DConvert@@YA?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@ABV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@D@Z 0x001F949D 135B evidence: rowed wide get_allocator 0x001627F0 narrow reserve-ctor 0x00027150 bfmeFwdVMX 0x0002B250 narrow push_back 0x0000C330 narrow copy-ctor 0x00009170 free 0x00030830 caller writeINI 0x001FB449
extern "C" void __cdecl free(void *block);

struct BfmeObjVMX
{
	int a;
	int b;
};

class BfmeStrVMX
{
public:
	void bfmeFwdVMX(BfmeObjVMX *p);
};

namespace _STL
{
// ?_STL::_String_reserve_t present-unmatched
struct _String_reserve_t
{
};
template <class T>
class char_traits
{
};

template <class T>
class allocator
{
public:
	allocator()
	{
	}
	allocator(const allocator &other)
	{
	}
	template <class U>
	allocator(const allocator<U> &)
	{
	}
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef _String_reserve_t _Reserve_t;
	typedef unsigned int size_type;
	basic_string(_Reserve_t, size_type n, const allocator<char> &a);
	basic_string(const basic_string &that);
	allocator<unsigned short> get_allocator() const;
	void push_back(char c);
	__declspec(dllimport) __forceinline ~basic_string()
	{
		if (_M_start != 0)
			free(_M_start);
	}
	char *_M_start;
	char *_M_finish;
	struct _Proxy
	{
		char *_M_data;
	} _M_end;
};

template <class CharT, class Traits, class Alloc>
class basic_string_w
{
public:
	allocator<unsigned short> get_allocator() const;
	unsigned short *_M_start;
	unsigned short *_M_finish;
	char _m[8];
};
}

_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > __cdecl Rva001F949DConvert(const _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>, _STL::allocator<unsigned short> > &wide, char extra)
{
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > tmp(
		_STL::_String_reserve_t(),
		(unsigned int)((char *)((const _STL::basic_string_w<char, _STL::char_traits<char>, _STL::allocator<char> > &)wide)._M_finish - (char *)((const _STL::basic_string_w<char, _STL::char_traits<char>, _STL::allocator<char> > &)wide)._M_start) + 1,
		*(const _STL::allocator<char> *)&wide.get_allocator());
	((BfmeStrVMX *)&tmp)->bfmeFwdVMX((BfmeObjVMX *)&wide);
	tmp.push_back(extra);
	return tmp;
}
