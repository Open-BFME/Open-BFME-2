// cl: /MD
// ?rva002B3EFA@@YAXPAX@Z @0x002B3EFA 65B: file-static scan, MSVC private
// EAX-incoming convention (StringBaseWideTrim/0x35800 precedent: a static
// taking the pointer arrives in eax; the sole retail caller 0x2BE23E does
// mov eax,[ebp+8] then a bare call).
// Iterates the 8-byte-entry vector at +0x78 (count = ([+0x44]-[+0x40])>>3 via
// the rowed 0x40CB2C indexed getter for the second dword), keeps each value
// live in eax across a bare call to the 0x2B3E7E check (pointer arrives in
// EAX: retail mov ebp,eax / call / test al,al), and on true sets +0xC4 and
// notifies via the 0x40C45C thiscall. Evidence: retail
//   push ebx/esi/edi; mov edi,[eax+0x78]; mov esi,[edi+0x44]; sub esi,[edi+0x40]
//   xor ebx,ebx; sar esi,3; test esi,esi; jle end
//   push ebp; push ebx; mov ecx,edi; call 0x40CB2C (rowed get)
//   mov ebp,eax; call 0x2B3E7E; test al,al; je skip
//   mov ecx,ebp; mov byte [ebp+0xC4],1; call 0x40C45C
//   inc ebx; cmp ebx,esi; jl loop; pop ebp/end pops; ret
// Boundary: Ghidra FUN_006b3efa 65B; preceded by the rowed 0x2B3EF7 zero getter
// tail (ret; xor eax,eax; ret); successor 0x2B3F3B starts the next target.
// No identity beyond the address: the name is address-derived.
class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
	char m_pad[0x40];
	char *m_first;
	char *m_last;
};

class Rva002B3EFAElem
{
public:
	void rva0040C45C();
	char m_pad[0xC4];
	unsigned char m_flagC4;
};

// 0x2B3E7E check: the candidate pointer arrives in EAX, so the caller keeps
// it live in eax across a bare call and tests al (banked 0x2b3e7e partials:
// fastcall/__cdecl spellings add mov ecx/push and miss). Declared zero-arg so
// the compiler emits the plain call with eax undisturbed.
bool Rva002B3E7ECheck();

struct Rva002B3EFAVec
{
	char m_pad[0x78];
	Rva0040CB2CIndexedField *m_vec;
};

static void rva002B3EFA(void *self)
{
	Rva0040CB2CIndexedField *vec = ((Rva002B3EFAVec *)self)->m_vec;
	char *first = vec->m_first;
	char *last = vec->m_last;
	int i = 0;
	int count = (int)((last - first) >> 3);
	if (count <= 0)
		return;
	do {
		int value = vec->get(i);
		if (Rva002B3E7ECheck()) {
			Rva002B3EFAElem *elem = (Rva002B3EFAElem *)value;
			elem->m_flagC4 = 1;
			elem->rva0040C45C();
		}
		++i;
	} while (i < count);
}

// Visible keep-alive so the static is emitted and keeps the EAX convention.
// Not claimed.
void *rva002B3EFA_keep(void *p)
{
	rva002B3EFA(p);
	return p;
}
