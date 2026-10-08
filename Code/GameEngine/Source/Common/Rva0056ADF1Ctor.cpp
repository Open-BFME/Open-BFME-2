// cl: /MD
//
// ??0Rva0056ADF1@@QAE@PAXH@Z @0x0056ADF1 53B.
// Constructor: run the pinned 0x0056AD80 initializer, null +0x14, install
// the 0x00C6D23C vftable at +0 and the 0x00C6D200 vftable at +8, then set
// +0x14 to the global-int at g_00DFEF10[0x100] plus the int argument.
// Honest address-derived name.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0056AD80
{
public:
	void rva0056AD80(void *arg);
};

extern "C" const void *const vtbl_00C6D23C[];
extern "C" const void *const vtbl_00C6D200[];

struct Rva0056ADF1Glob
{
	char m_pad[0x100];
	int m_100;
};

class Rva0056ADF1
{
public:
	Rva0056ADF1(void *arg1, int arg2);
};

Rva0056ADF1::Rva0056ADF1(void *arg1, int arg2)
{
	((Rva0056AD80 *)this)->rva0056AD80(arg1);
	*(int *)((char *)this + 0x14) = 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D23C);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D200);
	*(int *)((char *)this + 0x14) = (*(Rva0056ADF1Glob **)&TheLivingWorldLogic)->m_100 + arg2;
}
