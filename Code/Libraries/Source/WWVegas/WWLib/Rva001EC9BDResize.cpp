// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x001EC9BD divides its vector span by 0xAC. The shrink path calls
// the rowed range erase at 0x001EBDFa; the grow path calls the rowed fill
// insert at 0x001EBEAB. It destroys its by-value element through 0x0037DEE4.
// The one-argument wrapper at 0x001ECCF3 constructs a 0xAC temporary through
// 0x0037DF2C before forwarding. Resize semantics and element size are target
// evidence; original vector and record identities remain unresolved.
#include <vector>

struct BfmeAssignRecord172 { unsigned char bytes[172]; };
struct Rva001EBEABElement {
	unsigned char bytes[172];
	Rva001EBEABElement();
	Rva001EBEABElement(const Rva001EBEABElement &);
	~Rva001EBEABElement();
	Rva001EBEABElement &operator=(const Rva001EBEABElement &);
	bool operator<(const Rva001EBEABElement &) const;
	bool operator==(const Rva001EBEABElement &) const;
};

struct Rva0037DF2C {
	Rva0037DF2C();
	virtual ~Rva0037DF2C();
	unsigned char body[0xA8];
};

class Rva001EC9BDVector
{
public:
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	Rva0037DF2C *begin() { return m_start; }
	Rva0037DF2C *end() { return m_finish; }
	void resize(unsigned int newSize, Rva0037DF2C value);
	void resize(unsigned int newSize);

private:
	Rva0037DF2C *m_start;
	Rva0037DF2C *m_finish;
	Rva0037DF2C *m_endOfStorage;
};

void Rva001EC9BDVector::resize(unsigned int newSize, Rva0037DF2C value)
{
	if (newSize < size()) {
		reinterpret_cast<_STL::vector<BfmeAssignRecord172> *>(this)->erase(
			reinterpret_cast<BfmeAssignRecord172 *>(begin() + newSize),
			reinterpret_cast<BfmeAssignRecord172 *>(end()));
	} else {
		unsigned int extra = newSize - size();
		reinterpret_cast<_STL::vector<Rva001EBEABElement> *>(this)->_M_fill_insert(
			reinterpret_cast<Rva001EBEABElement *>(end()), extra,
			*reinterpret_cast<Rva001EBEABElement const *>(&value));
	}
}

void Rva001EC9BDVector::resize(unsigned int newSize)
{
	resize(newSize, Rva0037DF2C());
}
