// ?_M_fill_insert@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAEXPAUBfmePod28@@IABU3@@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAEXPAUBfmePod28@@IABU3@@Z @0x00584405 225B
// Vector<BfmePod28> fill-insert: in-capacity shift via rowed Rva Copy/FillN/Set plus
// StringRecord fill/copy_backward, overflow via 0x0058431D whose row types are wrong:
// row says (int, Arg5) but retail pushes (Tag& at +0xb, bool false) like donor
// _M_insert_overflow(pos, value, _IsPODType(), n, false); declared here as code uses it.
// Evidence: packet lane=leaf, pin BfmePod28, callers resize 0x00584A32 insert 0x005849EF,
// callees rowed 0x00583A1E 0x00583B11 0x00583B37 0x00583A4F 0x00583B54 0x0058431D, stride 0x1c ret 0xC.
struct BfmePod28
{
	int a[7];
};

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
public:
	Rva002337F0 &set(const Rva002337F0Blk *p);
};

struct Tag
{
};

struct Arg5
{
	bool m_flag;
	char m_pad[2];
	Tag m_tag;
};

struct BfmeStringRecord00111ACF
{
	char m_data[28];
};

namespace _STL
{
template <class T> class allocator
{
};
struct __false_type
{
};
template <class _BI1, class _BI2>
_BI2 __copy_backward_ptrs(_BI1 __first, _BI1 __last, _BI2 __result, const __false_type &);
template <class _ForwardIter, class _Tp>
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp &__val);
template <class T, class A> class vector
{
public:
	typedef unsigned int size_type;
	typedef BfmePod28 *iterator;
	void _M_fill_insert(iterator __position, size_type __n, const BfmePod28 &__x);
private:
	BfmePod28 *m_start;
	BfmePod28 *m_finish;
	BfmePod28 *m_end;
};
}

Rva002337F0 *__cdecl Rva00583B11Copy(Rva002337F0 *first, Rva002337F0 *last, Rva002337F0 *result, const Tag &tag);
Rva002337F0 *__cdecl Rva00583B54FillN(Rva002337F0 *first, unsigned int count, const Rva002337F0Blk &value);

class Rva0058431D
{
public:
	void rva0058431D(Rva002337F0 *pos, const Rva002337F0Blk *value, const Tag &tag, unsigned int n, bool atend);
private:
	Rva002337F0 *m_start;
	Rva002337F0 *m_finish;
	Rva002337F0 *m_end;
};

void _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >::_M_fill_insert(iterator __position, size_type __n, const BfmePod28 &__x)
{
	if (__n != 0)
	{
		if ((size_type)(m_end - m_finish) >= __n)
		{
			Rva002337F0 __x_copy;
			__x_copy.set((const Rva002337F0Blk *)&__x);
			const size_type __elems_after = (size_type)(m_finish - __position);
			BfmePod28 *__old_finish = m_finish;
			if (__elems_after > __n)
			{
				const Tag &tag = *(const Tag *)((const char *)&__position + 3);
				const _STL::__false_type &ft = *(const _STL::__false_type *)((const char *)&__position + 3);
				Rva00583B11Copy((Rva002337F0 *)(m_finish - __n), (Rva002337F0 *)m_finish, (Rva002337F0 *)m_finish, tag);
				m_finish += __n;
				_STL::__copy_backward_ptrs((BfmeStringRecord00111ACF *)__position, (BfmeStringRecord00111ACF *)(__old_finish - __n), (BfmeStringRecord00111ACF *)__old_finish, ft);
				_STL::fill((BfmeStringRecord00111ACF *)__position, (BfmeStringRecord00111ACF *)(__position + __n), *(const BfmeStringRecord00111ACF *)&__x_copy);
			}
			else
			{
				const Tag &tag2 = *(const Tag *)((const char *)&__position + 3);
				Rva00583B54FillN((Rva002337F0 *)m_finish, __n - __elems_after, *(const Rva002337F0Blk *)&__x_copy);
				m_finish += __n - __elems_after;
				Rva00583B11Copy((Rva002337F0 *)__position, (Rva002337F0 *)__old_finish, (Rva002337F0 *)m_finish, tag2);
				m_finish += __elems_after;
				_STL::fill((BfmeStringRecord00111ACF *)__position, (BfmeStringRecord00111ACF *)__old_finish, *(const BfmeStringRecord00111ACF *)&__x_copy);
			}
		}
		else
		{
			const Tag &otag = *(const Tag *)((const char *)&__position + 3);
			((Rva0058431D *)this)->rva0058431D((Rva002337F0 *)__position, (const Rva002337F0Blk *)&__x, otag, __n, false);
		}
	}
}
