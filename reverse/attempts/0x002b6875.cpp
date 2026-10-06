// ?rva002B6875@Rva002B4C09@@QAEXXZ
// partial score=0.8 date=2026-10-06
// cl: /O1 /MD
// ?rva002B6875@Rva002B4C09@@QAEXXZ @0x002B6875 53B: __thiscall void gate on
// the Rva002B4C09 view (+0x160 target, +0x154 table). When the +0x160
// target is set but the rowed 0x2B3621 probe fails it, the pinned
// 0x2BED91 worker runs on the target slot; a non-empty +0x154 table then
// tail-jumps to the 0x2B5BBA EH funclet with this in ecx.
// Evidence: retail
//   push esi; mov esi,ecx; lea edx,[esi+0x160]; cmp [edx],0; je SKIP
//   call 0x2B3621; test al,al; jne EXIT; mov ecx,edx; call 0x2BED91
//   SKIP: lea eax,[esi+0x154]; mov ecx,[eax]; cmp ecx,[eax+4]; je EXIT
//   mov ecx,esi; pop esi; jmp 0x2B5BBA
//   EXIT: pop esi; ret
// Boundary: 53B [0x2B6875,0x2B68AA); prev ret, next prologue. The jmp is a
// tail entry into 5BBA (which uses the caller frame); spelled as a void
// tail return so MSVC emits jmp, not call. Same-class view as the rowed
// 0x2B3621/0x2B4C09 bodies (identical +0x154/+0x160 use).
struct Rva002B3621Target
{
	char m_pad[0x25];
	unsigned char m_25flag; // +0x25
};

class Rva002BED91Holder
{
public:
	void rva002BED91();
};

class Rva002B5BBA
{
public:
	void rva002B5BBA();
};

class Rva002B4C09
{
public:
	bool rva002B3621();
	bool rva002B4C09();
	void rva002B6875();
private:
	char m_pad0[0xF4];
	int m_f4; // +0xF4
	char m_pad1[0x154 - 0xF8];
	void *m_vecBegin; // +0x154
	void *m_vecEnd; // +0x158
	char m_pad2[0x160 - 0x15C];
	Rva002B3621Target *m_160target; // +0x160
};

void Rva002B4C09::rva002B6875()
{
	Rva002B3621Target **slot = &m_160target;
	if (*slot != 0) {
		if (!rva002B3621()) {
			((Rva002BED91Holder *)slot)->rva002BED91();
		}
	}
	if (m_vecBegin != m_vecEnd)
		return ((Rva002B5BBA *)this)->rva002B5BBA();
}
