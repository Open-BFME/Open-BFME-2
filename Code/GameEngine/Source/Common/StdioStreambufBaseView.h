#ifndef STDIO_STREAMBUF_BASE_VIEW_H
#define STDIO_STREAMBUF_BASE_VIEW_H

#include <iosfwd>
#include <stdio.h>

// Partial FILE-backed narrow streambuf view shared by this TU's fragments.
// Keep the mutable-return locale assignment used by retail at RVA 0x00007160;
// the vendor header declares a different return type. No vtable is emitted.
namespace _STL
{
struct BfmeFileBuf
{
	char *_ptr;
	int _cnt;
	char *_base;
};

inline char *_FILE_I_begin(BfmeFileBuf *f) { return f->_base; }
inline char *_FILE_I_next(BfmeFileBuf *f) { return f->_ptr; }
inline char *_FILE_I_end(BfmeFileBuf *f) { return f->_ptr + f->_cnt; }
inline int _FILE_I_avail(BfmeFileBuf *f) { return f->_cnt; }
inline void _FILE_I_set(BfmeFileBuf *f, char *begin, char *next, char *end)
{
	f->_base = begin;
	f->_ptr = next;
	f->_cnt = (int)(end - next);
}

class locale
{
public:
	locale(const locale &);
	~locale();
	locale &operator=(const locale &);

private:
	void *_M_impl;
};

template <>
class basic_streambuf<char, char_traits<char> >
{
public:
	typedef char char_type;
	typedef int int_type;

	virtual ~basic_streambuf();
	virtual basic_streambuf *setbuf(char *, int);
	virtual int seekoff(int, int, int);
	virtual int seekpos(int, int);
	virtual int sync();
	virtual int showmanyc();

protected:
	virtual int xsgetn(char *, int);
	virtual int underflow();
	virtual int uflow();
	virtual int pbackfail(int);
	virtual int xsputn(const char *, int);
	virtual int _M_xsputnc(char, int);
	virtual int overflow(int);
	virtual void imbue(const locale &);

	char *eback() const { return _FILE_I_begin(_M_get); }
	char *gptr() const { return _FILE_I_next(_M_get); }
	char *egptr() const { return _FILE_I_end(_M_get); }
	void setg(char *begin, char *next, char *end)
	{
		_FILE_I_set(_M_get, begin, next, end);
	}

public:
	locale pubimbue(const locale &);
	int sgetc()
	{
		if (_FILE_I_avail(_M_get) > 0)
			return (unsigned char)*_FILE_I_next(_M_get);
		return underflow();
	}

private:
	int _M_snextc_aux();
	BfmeFileBuf *_M_get;
	BfmeFileBuf *_M_put;
	FILE _M_default_get;
	FILE _M_default_put;
	locale _M_locale;
};
}

#endif
