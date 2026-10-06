// ?rva002B5B55@Rva002B5B55@@QAEXPAVRva002B5B55Arg@@@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva002B5B55@Rva002B5B55@@QAEXPAVRva002B5B55Arg@@@Z @0x002B5B55 101B:
// __thiscall void with 1 stack arg (ret 4). Null-arg early-out, set +0x75
// flag, LivingWorld id lookup via rowed 0x2B51F8 find(int,unsigned*); on hit
// call the +0x1B8-table worker 0x2E10BD (pinned). Then recount through the
// rowed 3-arg cdecl 0x20E873 helper (same worker as Rva002B4BC9, temp homed
// over the dead incoming-arg slot); on change erase through the rowed
// vector<void*> erase 0x1FF51F. Tail: virtual slot 0 on the arg with 0, then
// scalar operator delete (rowed 0x02FD60) on its return; single-push cleanup
// via pop ecx. Evidence: retail
//   push esi; mov esi,[esp+8]; test esi,esi; push edi; mov edi,ecx; je END
//   mov [esi+0x75],1; mov eax,[esi+0x54]; push 0; push eax; call 0x2B51F8
//   test eax,eax; je SKIP; push esi; mov ecx,eax; call 0x2E10BD
//   SKIP: push ebx; mov ebx,[edi+0x110]; lea eax,[esp+0x10]; push eax
//   add edi,0x10C; push ebx; push [edi]; call 0x20E873; add esp,0xC
//   cmp eax,ebx; pop ebx; je NOSKIP; push eax; mov ecx,edi; call 0x1FF51F
//   NOSKIP: mov eax,[esi]; push 0; mov ecx,esi; call [eax]
//   push eax; call 0x02FD60; pop ecx; END: pop edi; pop esi; ret 4
// Boundary: Ghidra FUN_006b5b55 101B; prev tail is 0x2B5AF7's leave/ret,
// next byte 0x2B5BBA is an EH funclet (no prologue, frame slots, fs:[0]).
// Names address-derived except rowed callees and pins.
#include <vector>

class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

int rva0020E873(int a, int b, int *out);

class Rva002B5B55Arg
{
public:
	virtual void *rva002B5B55v0(int x);
	char m_pad[0x54 - 4];
	int m_id54; // +0x54 id passed by value to the 0x2B51F8 find
	char m_pad2[0x75 - 0x58];
	unsigned char m_flag75; // +0x75 set to 1
};

class Rva002E10BDWorker
{
public:
	void rva002E10BD(Rva002B5B55Arg *arg);
};

class Rva002B5B55
{
public:
	void rva002B5B55(Rva002B5B55Arg *arg);
private:
	char m_pad[0x10C];
	void *m_begin10C; // +0x10C vector start (vector<void*> layout)
	void *m_end110; // +0x110 vector finish
};

void Rva002B5B55::rva002B5B55(Rva002B5B55Arg *arg)
{
	// Keep the incoming pointer in a register copy (esi) for all real uses;
	// only the dead incoming stack slot itself is addressed ((int *)&arg)
	// as the worker's out-param home, so no ebp frame is needed. This is the
	// same slot-reuse spelling that landed Rva002B4BC9 frameless.
	Rva002B5B55Arg *self = arg;
	if (self == 0)
		return;
	self->m_flag75 = 1;
	Rva002E2903Player *found = ((Rva002BA8F1Logic *)this)->find(self->m_id54, 0);
	if (found != 0)
		((Rva002E10BDWorker *)found)->rva002E10BD(self);
	int lim = (int)m_end110;
	int got = rva0020E873((int)m_begin10C, lim, (int *)&arg);
	if (got != lim)
		((_STL::vector<void *> *)&m_begin10C)->erase((void **)got);
	::operator delete((void *)self->rva002B5B55v0(0));
}
