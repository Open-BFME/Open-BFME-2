// ?rva004E00D9@Rva004E00BAOwner@@QAEXXZ
// partial score=0.97 date=2026-10-07
// cl: /EHsc /DNDEBUG /MD
// stlport
// ?rva004E00BA@Rva004E00BAOwner@@QAEXPAVObject@@@Z @ 0x004E00BA (31B).
// Ghidra boundary 0x004E00BA..0x004E00D6 ends in ret 4; the next body starts
// at 0x004E00D9. The bytes push the Object* into a vector at this+4 via the
// pinned STLport vector<Object*>::push_back at 0x001F211B, then call 0x004DFF2C
// with the same receiver and Object*. The callee's identity and the owner's
// class identity are unresolved; these address-derived names preserve that.
// ?rva004E00D9@Rva004E00BAOwner@@QAEXXZ @ 0x004E00D9 (98B).
// This adjacent body clears a second vector at +0x10 by destroying and
// deleting each non-null Rva00281A06 element, then erases that vector's range.
// It walks the Object* vector at +4 and calls the same 0x004DFF2C member as
// rva004E00BA. Retail also calls this method from 0x004E02D7 with the same
// receiver. These offsets, callees, and boundaries are target evidence; the
// method purpose and real owner class remain unresolved.

#include <vector>

class Object;
struct Rva00281A06
{
	~Rva00281A06();
};

class Rva004E00BAOwner
{
public:
	void rva004E00BA(Object *object);
	void rva004E00D9();
	void rva004DFF2C(Object *object);

private:
	unsigned int m_opaquePrefix;
	_STL::vector<Object *> m_objects;
	_STL::vector<Rva00281A06 *> m_opaqueSecond;
};

void Rva004E00BAOwner::rva004E00BA(Object *object)
{
	m_objects.push_back(object);
	rva004DFF2C(object);
}

void Rva004E00BAOwner::rva004E00D9()
{
	Rva00281A06 **last = m_opaqueSecond.end();
	for (Rva00281A06 **it = m_opaqueSecond.begin(); it != last; ++it)
	{
		Rva00281A06 *element = *it;
		if (element)
		{
			element->~Rva00281A06();
			::operator delete(element);
		}
	}
	// The existing Object* range-erase alias is byte-identical for four-byte
	// pointers. The second vector's target pointee type remains unresolved.
	((_STL::vector<Object *> *)&m_opaqueSecond)->erase(
		(Object **)m_opaqueSecond.begin(), (Object **)m_opaqueSecond.end());

	// Retail checks begin against the current +8 end pointer, then reloads +8
	// into the loop register. Keep the observed guard read distinct.
	Object ** volatile *objectBeginAddress = (Object ** volatile *)((char *)this + 4);
	Object ** volatile *objectEndAddress = (Object ** volatile *)((char *)this + 8);
	Object **objectStart = *objectBeginAddress;
	if (objectStart == *objectEndAddress)
		return;
	Object **objectIt = objectStart;
	Object **objectEnd = m_objects.end();
	while (objectIt != objectEnd)
	{
		rva004DFF2C(*objectIt);
		++objectIt;
	}
}
