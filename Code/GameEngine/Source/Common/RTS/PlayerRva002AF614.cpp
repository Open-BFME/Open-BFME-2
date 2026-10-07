// cl: /DNDEBUG /MD /EHsc
// ?rva002AF614@Player@@QAEXPAX@Z @0x002AF614 (17B): Player ecx pass-through to iterateObjects with callback at 0x002AF5EF and forwarded userdata.
// Native callback and rowed iterator both return int; use their actual ABI.
// Evidence: push [esp+4] then push 0x6af5ef then call pinned Player::iterateObjects @0x002AB08B then ret 4; 17B matches void Player method with void* arg; sibling PlayerRva002AE475 @0x002AE475 same 17B shape with callback 0x002AE435.
class Object;
typedef int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
	void rva002AF614(void *userData);
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector
	{
	public:
		void push_back(const T &value);
	};
}

// The fields the callback reads: the object's template at +0x04, whose byte
// at +0x10A carries the flag tested, and the object's position at +0x38.
struct Rva002AF5EFTemplate
{
	char m_pad[0x10A];
	unsigned char m_flags10A;
};

struct Rva002AF5EFObject
{
	void *m_vtbl;
	Rva002AF5EFTemplate *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_position;
};

// The iterateObjects callback at 0x002AF5EF (37B): it appends the position of
// every object whose template has flag 2 at +0x10A to the caller's
// vector<Coord3D> (push_back 0x002CE7DC) and always continues.
int __cdecl Rva002AF5EF(Object *obj, void *userData)
{
	Rva002AF5EFObject *object = (Rva002AF5EFObject *)obj;
	if (object && (object->m_template->m_flags10A & 2))
		((_STL::vector<Coord3D, _STL::allocator<Coord3D> > *)userData)->push_back(object->m_position);
	return 1;
}

void Player::rva002AF614(void *userData)
{
	iterateObjects(Rva002AF5EF, userData);
}
