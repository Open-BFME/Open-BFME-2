// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x001EC9BD divides its vector span by 0xAC. The shrink path calls
// the rowed range erase at 0x001EBDFa; the grow path calls the rowed fill
// insert at 0x001EBEAB. It destroys its by-value element through 0x0037DEE4.
// The one-argument wrapper at 0x001ECCF3 constructs a 0xAC temporary through
// 0x0037DF2C before forwarding. Resize semantics and element size are target
// evidence; original vector and record identities remain unresolved.
struct BfmeAssignRecord172
{
public:
	BfmeAssignRecord172(const BfmeAssignRecord172 &);
	~BfmeAssignRecord172();
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &);
	int a[43];
};
struct Rva001EBEABElement
{
public:
	Rva001EBEABElement();
	Rva001EBEABElement(const Rva001EBEABElement&);
	~Rva001EBEABElement();
	Rva001EBEABElement&operator=(const Rva001EBEABElement&);
	bool operator<(const Rva001EBEABElement&)const;
	bool operator==(const Rva001EBEABElement&)const;
	char bytes[172]; // +0x00
};

#include <vector>
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

namespace _STL {
template <> BfmeAssignRecord172 *vector<BfmeAssignRecord172, allocator<BfmeAssignRecord172> >::erase(BfmeAssignRecord172 *, BfmeAssignRecord172 *);
template <> void vector<Rva001EBEABElement, allocator<Rva001EBEABElement> >::_M_fill_insert(Rva001EBEABElement *, unsigned int, const Rva001EBEABElement &);
}

class Object;
class Player;
struct CarryoverUnit
{
public:
	CarryoverUnit();
	virtual ~CarryoverUnit();
	Object *createSingleObject(Player *player);
	AsciiString m_name; // +0x04
	char m_pad08[0x90 - 0x08];
	int m_quantity; // +0x90
	char m_pad94[0xAC - 0x94];
};

class Rva001EC9BDVector : public _STL::vector<CarryoverUnit>
{
public:
	void resize(unsigned int newSize, CarryoverUnit value);
	void resize(unsigned int newSize);
};

void Rva001EC9BDVector::resize(unsigned int newSize, CarryoverUnit value)
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
	resize(newSize, CarryoverUnit());
}
