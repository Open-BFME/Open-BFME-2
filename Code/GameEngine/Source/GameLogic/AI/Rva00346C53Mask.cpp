// cl: /O1 /DNDEBUG /MD
// ?rva00346C53@Object@@QAEXW4ObjectStatusTypes@@_N@Z @0x00346C53 38B.
// Native RET8 builder consumes (reserved zero, enum). The bool is pushed
// first and remains for the following RET8 Object mask-plus-bool helper.
// The former three-argument builder / one-argument helper declarations
// reproduced bytes while misrepresenting stack cleanup. Receiver is Object:
// its three callers (AIStatesBfmeOnExit.cpp, BloodthirstyUpdateIfaceChecks.cpp,
// QueueProductionExitUpdateRva004A0547.cpp) call it on an Object, and it
// forwards to the rowed Object::rva00293D3B on the same this.
enum ObjectStatusTypes
{
	OBJECT_STATUS_00 = 0
};

// LINK: 0x0023DA79 is rowed as Rva0023DA79::rva0023DA79(int, int) (Rva0023DA79Bitset.cpp); the mask is that object.
class Rva0023DA79
{
public:
	Rva0023DA79 *rva0023DA79(int a, int b);
};

struct ObjectStatusMask
{
public:

private:
	char m_data[16];
};

class Rva00346BC0;
#include "../Object/object.h"

void Object::rva00346C53(ObjectStatusTypes a, bool b)
{
	ObjectStatusMask mask;
	setStatusForHorde(*reinterpret_cast<Rva00346BC0 *>(((Rva0023DA79 *)&mask)->rva0023DA79(0, a)), b);
}
