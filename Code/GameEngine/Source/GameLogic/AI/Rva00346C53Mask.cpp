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

struct ObjectStatusMask
{
public:
	ObjectStatusMask *Rva0023DA79(int a, ObjectStatusTypes b);

private:
	char m_data[16];
};

class Rva00346BC0;
class Object
{
public:
	void rva00293D3B(const Rva00346BC0 &mask, bool set);
	void rva00346C53(ObjectStatusTypes a, bool b);
};

void Object::rva00346C53(ObjectStatusTypes a, bool b)
{
	ObjectStatusMask mask;
	rva00293D3B(*reinterpret_cast<Rva00346BC0 *>(mask.Rva0023DA79(0, a)), b);
}
