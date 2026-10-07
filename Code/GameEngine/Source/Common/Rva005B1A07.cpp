// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva005B1A07@Rva005B1A07@@QAEXIUBfmePod20@@@Z, retail 0x005B1A07 73B.
// Index into pod20 array at +0/+4: if in range tail-call rowed 0x005B129F else rowed fill_insert 0x005B1748.
// Evidence: rowed callees; ret 0x18 index plus 20B pod; caller 0x005B1B53; prev 0x005B1830 shares STL.
struct BfmePod20
{
	int a[5];
};

// Call the single retained erase owner at 0x005B129F. Record identity is
// address-derived; only the pointer ABI is needed in this caller.
struct Rva005B09D8Record;
class Rva005B129FVector {
public:
    Rva005B09D8Record *erase(Rva005B09D8Record *, Rva005B09D8Record *);
};
class Rva005B129FClass
{
public:
	int m_0;
	int m_4;
};

namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	void _M_fill_insert(T *pos, unsigned int n, const T &val);
};
}

class Rva005B1A07
{
public:
	void rva005B1A07(unsigned int index, BfmePod20 val);

private:
	BfmePod20 *m_0;
	BfmePod20 *m_4;
	BfmePod20 *m_8;
};

void Rva005B1A07::rva005B1A07(unsigned int index, BfmePod20 val)
{
	int b = (int)m_0;
	int e = (int)m_4;
	int c = (e - b) / 20;
	if (index < (unsigned int)c) {
		int elem = b + (int)(index * 20);
		((Rva005B129FVector *)this)->erase((Rva005B09D8Record *)elem, (Rva005B09D8Record *)e);
		return;
	}
	int e2 = *(volatile int *)&m_4;
	int c2 = (e2 - b) / 20;
	unsigned int need = index - (unsigned int)c2;
	((_STL::vector<BfmePod20> *)this)->_M_fill_insert((BfmePod20 *)e2, need, val);
}
