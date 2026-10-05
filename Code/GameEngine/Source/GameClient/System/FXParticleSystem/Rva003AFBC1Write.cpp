// cl: /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?Rva003AFBC1Write@@YAXPBDPAVFile@@PAI@Z at 0x003AFBC1 size 170
// Evidence: chain via rowed Pad 0x001F6951; oss ctor 0x001FA85C push 1 push 0x10 then Pad then single _M_put_nowiden then _M_put_char 0xA then str 0x001FA473 then Write 0x001F458B then free 0x30830 then flags+=2 then oss dtors; precedent Rva0055CB5DWrite.cpp.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <sstream>

class File {
public:
	virtual ~File();
	virtual bool open(const char *n, int a = 0);
	virtual void close();
	virtual int read(void *b, int bsz);
	virtual int write(const void *b, int bsz);
};
struct Rva001F458BText {
	const char *m_start;
	const char *m_finish;
};
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
extern "C" void __cdecl free(void *p);
extern const char g_00C1D838[];

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);

void Rva003AFBC1Write(const char *value, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(oss, *flags);
	r._M_put_nowiden(value);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	*flags += 2;
}

void Rva003AFC6BWrite(File *file, unsigned int *flags)
{
	*flags -= 2;
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(oss, *flags);
	r._M_put_nowiden(g_00C1D838);
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
}
