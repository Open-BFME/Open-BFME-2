// cl: /EHsc /MD
// ??0Rva0031F7EB@@QAE@XZ @0x0031F7EB 70B ctor.
// Retail zeroes 36B with releaseBuffer in middle. Evidence: unlock lane;
// rowed releaseBuffer 0x36410; caller 0x003201CB; sibling 0x0031F7AB pattern
// (base init for +0, no redundant m_data store).
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
	friend class Rva0031F7EB;
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
class Rva0031F7EB
{
public:
	Rva0031F7EB();
private:
	AsciiString m_str;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
	int m_g;
	int m_h;
};
Rva0031F7EB::Rva0031F7EB()
{
	m_c = 0;
	m_e = 0;
	m_d = 0;
	((StringBase<char> &)m_str).releaseBuffer();
	m_a = 0;
	m_b = 0;
	m_g = 0;
	m_f = 0;
	m_h = 0;
}
