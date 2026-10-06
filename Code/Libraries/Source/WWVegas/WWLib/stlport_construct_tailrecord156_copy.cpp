// cl: /DNDEBUG /MD
// stlport
//
// ??0BfmeStringTailRecord156@@QAE@ABV0@@Z @0x001D9975, 27 bytes.
// Identity is inferred from the called template specialization
// _STL::_Construct<BfmeStringTailRecord156,BfmeStringTailRecord156> at
// 0x001D9A4F. Retail bytes call the matched Rva0036CA00Str copy constructor
// at +0, copy a dword at +4, and return this; this supports the member view
// below. Ghidra boundary and size are 0x001D9975/27, checked against retail
// disassembly. No matching ZH/Open-BFME-1 donor was found.

class Rva0036CA00Str
{
    void *m_item;
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
	~Rva0036CA00Str();
};

class BfmeStringTailRecord156
{
    Rva0036CA00Str m_string;
    int m_value;
public:
	BfmeStringTailRecord156(const BfmeStringTailRecord156 &) throw();
	~BfmeStringTailRecord156() throw();
};

BfmeStringTailRecord156::BfmeStringTailRecord156(
	const BfmeStringTailRecord156 &other) throw()
	: m_string(other.m_string), m_value(other.m_value)
{
}
