// cl: /O1 /MD
//
// ??0Rva0056AF94@@QAE@PAX@Z @0x0056AF94 31B.
// Constructor: run the pinned EH 0x0056AD80 initializer, then install the
// 0x00C6D19C vftable at +0 and the 0x00C6D160 vftable at +8. Honest
// address-derived name.
class Rva0056AD80
{
public:
	void rva0056AD80(void *arg);
};

extern "C" const void *const vtbl_00C6D19C[];
extern "C" const void *const vtbl_00C6D160[];

class Rva0056AF94
{
public:
	Rva0056AF94(void *arg);
};

Rva0056AF94::Rva0056AF94(void *arg)
{
	((Rva0056AD80 *)this)->rva0056AD80(arg);
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D19C);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D160);
}
