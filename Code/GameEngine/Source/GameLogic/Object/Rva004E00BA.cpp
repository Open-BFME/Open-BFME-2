// cl: /EHsc /DNDEBUG /MD
// stlport
// ?addObject@Rva004E00BAOwner@@QAEXPAVObject@@@Z @ 0x004E00BA (31B).
// Ghidra boundary 0x004E00BA..0x004E00D6 ends in ret 4; the next body starts
// at 0x004E00D9. The bytes push the Object* into a vector at this+4 via the
// pinned STLport vector<Object*>::push_back at 0x001F211B, then call 0x004DFF2C
// with the same receiver and Object*. The callee's identity and the owner's
// class identity are unresolved; these address-derived names preserve that.
#include <vector>

class Object;

namespace _STL { template <> void vector<Object *, allocator<Object *> >::push_back(Object *const &); }

typedef void *(__cdecl *Rva004DFE4FCallback)(void *key);

class Rva00281A76;

// 0x004DFF2C is rowed as ?rva004DFF2C@Rva004DFF2C@@QAEXPAX@Z; bind to that row.
class Rva004DFF2C
{
public:
 virtual float padding() = 0;
 void rva004DFF2C(void *key);
private:
 char m_pad04[0xC];
 _STL::vector<Rva00281A76 *> m_groups;
 int m_1C;
 Rva004DFE4FCallback m_callback;
};

class Rva004E00BAOwner
{
public:
	void addObject(Object *object);

private:
	unsigned int m_opaquePrefix;
	_STL::vector<Object *> m_objects;
};

void Rva004E00BAOwner::addObject(Object *object)
{
	m_objects.push_back(object);
	reinterpret_cast<Rva004DFF2C *>(this)->rva004DFF2C(object);
}
