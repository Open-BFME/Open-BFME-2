// cl: /EHsc /DNDEBUG /MD
// stlport
// ?rva004E00BA@Rva004E00BAOwner@@QAEXPAVObject@@@Z @ 0x004E00BA (31B).
// Ghidra boundary 0x004E00BA..0x004E00D6 ends in ret 4; the next body starts
// at 0x004E00D9. The bytes push the Object* into a vector at this+4 via the
// pinned STLport vector<Object*>::push_back at 0x001F211B, then call 0x004DFF2C
// with the same receiver and Object*. The callee's identity and the owner's
// class identity are unresolved; these address-derived names preserve that.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

class Object;

class Rva004E00BAOwner
{
public:
	void rva004E00BA(Object *object);
	void rva004DFF2C(Object *object);

private:
	unsigned int m_opaquePrefix;
	_STL::vector<Object *> m_objects;
};

void Rva004E00BAOwner::rva004E00BA(Object *object)
{
	m_objects.push_back(object);
	rva004DFF2C(object);
}
