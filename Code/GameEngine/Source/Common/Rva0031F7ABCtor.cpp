// ??0Rva0031F7AB@@QAE@XZ
// partial score=0.93 date=2026-09-29
// cl: /EHsc /MD
// ??0Rva0031F7AB@@QAE@XZ @0x0031F7AB 64B.
// Honest-address default ctor zeroing 28 bytes with an AsciiString at +0.
// Evidence: callee rowed releaseBuffer 0x36410; callers 0x0031FA62 0x0032017A.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class Rva0031F7AB;
private:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	~AsciiString() {}
};

class Rva0031F7AB
{
public:
	Rva0031F7AB();
private:
	AsciiString m_str;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
};

Rva0031F7AB::Rva0031F7AB()
{
	((StringBase<char> &)m_str).releaseBuffer();
	m_b = 0;
	m_a = 0;
	m_d = 0;
	m_c = 0;
	m_e = 0;
	m_f = 0;
}
