// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva0058431D@Rva0058431D@@QAEXPAVRva002337F0@@PBURva002337F0Blk@@HIUArg5@@@Z retail 0x0058431D 189B.
// Unlock: landing makes 0x00584405 ready. Vector _M_fill_insert_aux shape (size+max(size,n)
// grow via rowed allocator 0xB40EA, rowed Copy 0x583B11, Set 0x583A72, FillN 0x583A84, free 0x30830).
// Prev/next Rva005843DACtor.cpp same dir. No callers rowed. Splash: EBP frame so /O1.

struct BfmeStringRecord00111ACF { char m_data[28]; };

struct Rva002337F0Blk
{
	int a;
	int b;
	int c;
	int d;
	char e;
	int f;
	int g;
};

class Rva002337F0
{
	Rva002337F0Blk m;
};

struct Tag
{
	char x;
};

struct Arg5
{
	bool m_flag;
	char m_pad[2];
	Tag m_tag;
};

namespace _STL {
template <class T> class allocator;
template <> class allocator<BfmeStringRecord00111ACF>
{
public:
	BfmeStringRecord00111ACF* allocate(unsigned int n, const void* hint) const;
};
}

Rva002337F0* __cdecl Rva00583B11Copy(Rva002337F0* first, Rva002337F0* last, Rva002337F0* result, const Tag& tag);
void __cdecl Rva00583A72Set(Rva002337F0* a, const Rva002337F0Blk* b);
Rva002337F0* __cdecl Rva00583A84FillN(Rva002337F0* result, unsigned int count, const Rva002337F0Blk& value, const Tag& tag);
extern "C" void __cdecl free(void* p);

class Rva0058431D
{
public:
	void rva0058431D(Rva002337F0* pos, const Rva002337F0Blk* value, int unused, unsigned int n, Arg5 arg);
private:
	Rva002337F0* m_start;
	Rva002337F0* m_finish;
	Rva002337F0* m_end;
};

void Rva0058431D::rva0058431D(Rva002337F0* pos, const Rva002337F0Blk* value, int unused, unsigned int n, Arg5 arg)
{
	unsigned int size = m_finish - m_start;
	unsigned int size_save = size;
	unsigned int* p = &n;
	if (size >= n)
		p = &size_save;
	unsigned int total = size + *p;
	Rva002337F0* new_start = (Rva002337F0*)((const _STL::allocator<BfmeStringRecord00111ACF>*)&m_end)->allocate(total, 0);
	Rva002337F0* new_finish = Rva00583B11Copy(m_start, pos, new_start, arg.m_tag);
	Rva002337F0* hold_start = new_start;
	if (n == 1)
	{
		Rva00583A72Set(new_finish, value);
		new_finish += 1;
	}
	else
	{
		new_finish = Rva00583A84FillN(new_finish, n, *value, arg.m_tag);
	}
	if (!arg.m_flag)
		new_finish = Rva00583B11Copy(pos, m_finish, new_finish, arg.m_tag);
	if (m_start)
		free(m_start);
	m_start = hold_start;
	m_finish = new_finish;
	m_end = hold_start + total;
}
