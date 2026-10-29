// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport46
// 0x0001A090 (33B): STLport 4.5.3 _Messages::do_get, wide overload.
// Retail's RTTI-named vftable 0x007BC8D4 (.?AV_Messages@_STL@@) holds
// do_open, do_get(wstring), do_get(string), do_close, ~_Messages: overloads
// of one name enter MSVC's vftable in reverse declaration order, so slot 1
// is the wstring overload. The classic messages implementation cannot open a
// catalog and returns the caller's default: copy-construct the hidden result
// from __dfault through the rowed wide copy ctor (call 0x0000EA90).
namespace _STL
{
template <class T> class char_traits {};
template <class T> class allocator {};
template <class C, class T, class A> class basic_string
{
public:
	basic_string(const basic_string &src);
	~basic_string();
};
typedef basic_string<char, char_traits<char>, allocator<char> > string;
typedef basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > wstring;
class locale;

class _Messages
{
public:
	virtual int do_open(const string &, const locale &) const;
	virtual string do_get(int, int, int, const string &) const;
	virtual wstring do_get(int, int, int, const wstring &) const;
	virtual void do_close(int) const;
	virtual ~_Messages();
};

wstring _Messages::do_get(int, int, int, const wstring &dfault) const
{
	return dfault;
}
}
