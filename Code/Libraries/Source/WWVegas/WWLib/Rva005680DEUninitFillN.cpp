// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// STLport uninitialized_fill_n helper for the 16-byte Rva00567BD7 record.
//
// The target wrapper at 0x005680DE forwards (first, count, value) with a
// false_type tag to the 37-byte worker at 0x00567FFC. The worker's loop calls
// the rowed copy helper at 0x00567F91 and advances by 0x10, establishing the
// record stride; the copy constructor row at 0x00567BD7 establishes the
// nontrivial-copy path. This helper is a source-level STLport name for the
// same verified worker body already recorded under its address-derived name.

class Rva00567BD7
{
public:
	Rva00567BD7(const Rva00567BD7 &that);
	char m_body[0x10];
};

void Rva00567F91Copy(Rva00567BD7 *dst, const Rva00567BD7 *src);

namespace _STL
{
	struct __false_type {};

	template <class ForwardIter, class Size, class T>
	ForwardIter __uninitialized_fill_n(ForwardIter first, Size count,
		const T &value, const __false_type &tag);

	template <class ForwardIter, class Size, class T>
	inline ForwardIter uninitialized_fill_n(ForwardIter first, Size count,
		const T &value)
	{
		return __uninitialized_fill_n(first, count, value, __false_type());
	}

	template <>
	Rva00567BD7 *__uninitialized_fill_n<Rva00567BD7 *, unsigned int, Rva00567BD7>(
		Rva00567BD7 *first, unsigned int count, const Rva00567BD7 &value,
		const __false_type &)
	{
		Rva00567BD7 *cur = first;
		for (; count > 0; --count, ++cur)
			Rva00567F91Copy(cur, &value);
		return cur;
	}
}

template Rva00567BD7 *_STL::uninitialized_fill_n<Rva00567BD7 *, unsigned int,
	Rva00567BD7>(Rva00567BD7 *, unsigned int, const Rva00567BD7 &);
