// cl: /O1 /MD
//
// ??0Rva0056AF4B@@QAE@PAXHH@Z @0x0056AF4B 45B.
// Constructor: run the pinned EH 0x0056AD80 initializer with the first
// arg, store the second/third args at +0x14/+0x18, then install the
// 0x00C6D14C vftable at +0 and the 0x00C6D110 vftable at +8. Follows the
// landed Rva0056AF94/Rva0056ADF1 recipe (standalone address-derived class,
// base via cast, vtbls via externs). Honest address-derived name.

class Rva0056AD80
{
public:
	void rva0056AD80(void *arg);
};

extern const void *const g_00C6D14C[];
extern const void *const g_00C6D110[];

class Rva0056AF4B
{
public:
	Rva0056AF4B(void *arg1, int arg2, int arg3);
};

Rva0056AF4B::Rva0056AF4B(void *arg1, int arg2, int arg3)
{
	((Rva0056AD80 *)this)->rva0056AD80(arg1);
	*(int *)((char *)this + 0x14) = arg2;
	*(int *)((char *)this + 0x18) = arg3;
	*(unsigned int *)this = ((unsigned int)g_00C6D14C);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)g_00C6D110);
}
