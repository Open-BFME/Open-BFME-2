// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Ghidra's 48-byte body walks the 4-byte start/finish range at this+0x158,
// erasing entries equal to the argument through 0x0025BF5D. The target proves
// only 32-bit value equality; ObjectID is the already-rowed helper instantiation
// used to model those opaque slots, not a claim about their runtime meaning.
#include <vector>
#include <algorithm>

enum ObjectID { INVALID_ID = 0 };

class Rva003F15A1
{
public:
	void rva003F15A1(void *object);

private:
	char m_pad[0x158];
	_STL::vector<ObjectID> m_items;
};

void Rva003F15A1::rva003F15A1(void *object)
{
	_STL::vector<ObjectID>::iterator it = m_items.begin();
	while (it != m_items.end()) {
		if (*it == (ObjectID)(int)object)
			it = m_items.erase(it);
		else
			++it;
	}
}
