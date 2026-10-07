// cl: /O1 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva00216245@Rva00216245@@QAEPAURva0021618ARecord@@ABU2@@Z @0x00216245 34B. STL helper is rowed; field offsets come from retail operands.
// stlport
struct Rva0021618ARecord
{
	char bytes[1];
	bool operator<(const Rva0021618ARecord &) const;
};

namespace _STL
{
	template <class ForwardIter, class Size, class T>
	ForwardIter uninitialized_fill_n(ForwardIter first, Size count, const T &value);
}

class Rva00216245
{
public:
	Rva0021618ARecord *rva00216245(const Rva0021618ARecord &value);

private:
	char m_pad00[0x28];
	Rva0021618ARecord *m_data;
	int m_count;
};

Rva0021618ARecord *Rva00216245::rva00216245(const Rva0021618ARecord &value)
{
	int count = m_count;
	Rva0021618ARecord *end = _STL::uninitialized_fill_n(m_data, count, value);
	return (int)end != count ? end : 0;
}
