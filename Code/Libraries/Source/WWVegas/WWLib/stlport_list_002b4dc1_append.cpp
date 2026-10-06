// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?rva002B87E0@Rva002B87E0@@QAE@URva002B87E0Param@@@Z @ 0x002B87E0 (55B).
// By-value 12-byte wide-string record forwarded to the rowed list-append
// thunk 0x002B8106 at +0xF0, then the inline StringBase<wchar_t> dtor runs
// the rowed releaseBuffer 0x00036E70. Evidence: callee rowed, caller none.
template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

struct BfmeStringRecord002B4DC1 { unsigned char m_data[12]; };

class Rva002B8106
{
public:
	void rva002B8106(const BfmeStringRecord002B4DC1 &v);
};

struct Rva002B87E0Param
{
	StringBase<unsigned short> m_base;
	unsigned char m_pad[8];
};

class Rva002B87E0
{
public:
	void rva002B87E0(Rva002B87E0Param s);

private:
	unsigned char m_pad[0xF0];
	Rva002B8106 m_holder;
};

void Rva002B87E0::rva002B87E0(Rva002B87E0Param s)
{
	m_holder.rva002B8106(reinterpret_cast<const BfmeStringRecord002B4DC1 &>(s));
}
