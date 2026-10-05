// cl: /O1 /MD
// Range-11 pair sharing class Rva002B4C09 (callee defined in-TU so the
// caller keeps `this` in ecx across the call with no esi park).
// ?rva002B3621@Rva002B4C09@@QAE_NXZ @0x002B3621 23B: __thiscall bool probe.
// True when the +0x160 target is non-null and its +0x25 flag is set.
// Evidence: retail
//   mov eax,[ecx+0x160]; test eax,eax; je FAIL
//   cmp byte [eax+0x25],0; je FAIL
//   xor eax,eax; inc eax; ret; FAIL: xor eax,eax; ret
// Boundary: 23B [0x002B3621,0x002B3638); prev ret, next prologue.
// Absorbs the former 3B tail row at 0x002B3635 (its two je targets).
// ?rva002B4C09@Rva002B4C09@@QAE_NXZ @0x002B4C09 44B: __thiscall bool gate.
// True only when +0xF4 is 1 or 5, the 0x2B3621 probe on this returns
// false, and the +0x154 begin/end pair is empty. Evidence: retail
//   mov eax,[ecx+0xF4]; cmp eax,1; je DO; cmp eax,5; jne FAIL(0x2B4C32)
//   DO: call 0x2B3621; test al,al; jne FAIL
//   lea eax,[ecx+0x154]; mov ecx,[eax]; cmp ecx,[eax+4]; jne FAIL
//   mov al,1; ret; FAIL: xor al,al; ret
// Boundary: 44B [0x2B4C09,0x2B4C35); prev ret-4, next prologue at 0x2B4C35.
// Absorbs the former 3B tail row at 0x002B4C32 (its three jne targets).
// Names address-derived except rowed callees.
struct Rva002B3621Target
{
	char m_pad[0x25];
	unsigned char m_25flag; // +0x25
};

class Rva002B4C09
{
public:
	bool rva002B3621();
	bool rva002B4C09();
private:
	char m_pad0[0xF4];
	int m_f4; // +0xF4
	char m_pad1[0x154 - 0xF8];
	void *m_vecBegin; // +0x154
	void *m_vecEnd; // +0x158
	char m_pad2[0x160 - 0x15C];
	Rva002B3621Target *m_160target; // +0x160
};

bool Rva002B4C09::rva002B3621()
{
	Rva002B3621Target *t = m_160target;
	return t != 0 && t->m_25flag != 0;
}

bool Rva002B4C09::rva002B4C09()
{
	if (m_f4 == 1 || m_f4 == 5) {
		if (!rva002B3621()) {
			void **pp = (void **)((char *)this + 0x154);
			if (*pp == pp[1])
				return true;
		}
	}
	return false;
}
