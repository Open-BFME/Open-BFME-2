// cl: /O1 /Oy- /G7 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F3AB5@Rva003F3AB5@@QAEXIUDynamicPortalLink@@@Z @0x003F3AB5 115B. Index-or-append over 12B DynamicPortalLink array.
// True branch forwards to rowed 0x003F3159, false to rowed vector fill-insert 0x003F35E3, then frees owned block via rowed free 0x00030830.
// Evidence: rowed callees, unblocks 0x003F3B28, ret 0x10 with index plus 12B value.
#include <vector>

extern "C" void __cdecl free(void *block);

struct DynamicPortalLink
{
	void *m_owned;
	int m_second;
	int m_third;
	~DynamicPortalLink() { if (m_owned != 0) free(m_owned); }
};

class Rva003F3159
{
public:
	DynamicPortalLink *rva003F3159(DynamicPortalLink *a, DynamicPortalLink *b);
private:
	char m_pad[4];
	DynamicPortalLink *m_finish;
};

// The 12-byte record of the rowed fill-insert at 0x003F35E3, declared as that
// unit declares it, which instantiates the template: here it is only called.
struct Rva003F3277Record { Rva003F3277Record(); Rva003F3277Record(const Rva003F3277Record &); ~Rva003F3277Record(); Rva003F3277Record &operator=(const Rva003F3277Record &); private: char bytes[12]; };
extern template void _STL::vector<Rva003F3277Record, _STL::allocator<Rva003F3277Record> >::_M_fill_insert(
	Rva003F3277Record *, unsigned int, const Rva003F3277Record &);

class Rva003F3AB5
{
public:
	void rva003F3AB5(unsigned index, DynamicPortalLink value);
private:
	DynamicPortalLink *m_begin;
	DynamicPortalLink *m_end;
	DynamicPortalLink *m_cap;
};

void Rva003F3AB5::rva003F3AB5(unsigned index, DynamicPortalLink value)
{
	unsigned count = (unsigned)(m_end - m_begin);
	if (index < count) {
		((Rva003F3159 *)this)->rva003F3159(m_begin + index, m_end);
	} else {
		unsigned n = index - (unsigned)(m_end - m_begin);
		(((_STL::vector<Rva003F3277Record, _STL::allocator<Rva003F3277Record> > *)this)->_M_fill_insert((Rva003F3277Record *)m_end, (unsigned)n, *(const Rva003F3277Record *)&value));
	}
}
