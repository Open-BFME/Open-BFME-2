// ?rva002B4C35@Rva002B4C35@@QAEXXZ
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD
// ?rva002B4C35@Rva002B4C35@@QAEXXZ @0x002B4C35 184B: __thiscall void nest.
// Outer recount loop over the +0x8C/+0x90 table; inner recount loop over
// each element's +0x1B8/+0x1BC table. Each inner element with a clear
// +0x74 flag goes through the pinned 0x318C32 match; on a hit the +0x13C
// value -1 schedules via rowed 0x2B388D while any other value differing
// from the outer +0x14 goes through the pinned 0x31912E worker.
// Evidence: retail
//   push ebp; mov ebp,esp; push ecx; push ecx; and [ebp-8],0; push edi
//   mov edi,ecx; mov eax,[edi+0x90]; sub eax,[edi+0x8C]; sar eax,2
//   je EXIT; push ebx; push esi
//   OUTER: mov eax,[edi+0x8C]; mov ecx,[ebp-8]; mov esi,[eax+ecx*4]
//   mov eax,[esi+0x1B8]; mov ecx,[esi+0x1BC]; and [ebp-4],0
//   sub ecx,eax; sar ecx,2; je INNER_DONE
//   INNER: mov ecx,[ebp-4]; mov ebx,[eax+ecx*4]
//   cmp byte [ebx+0x74],0; jne NEXT; mov ecx,ebx; call 0x318C32
//   test eax,eax; je NEXT; mov ecx,[eax+0x13C]; cmp ecx,-1; jne NOTNEG
//   push esi; push eax; mov ecx,edi; call 0x2B388D; jmp NEXT
//   NOTNEG: cmp ecx,[esi+0x14]; je NEXT; mov ecx,ebx; call 0x31912E
//   NEXT: reload +0x1B8/+0x1BC; inc [ebp-4]; recount; cmp [ebp-4],ecx
//   jb INNER; INNER_DONE: reload +0x8C/+0x90; inc [ebp-8]; recount
//   cmp [ebp-8],eax; jb OUTER
//   EXIT: pop esi; pop ebx; pop edi; leave; ret
// Boundary: 184B [0x2B4C35,0x2B4CED); prev ret, next prologue (rowed
// 0x2B4CED body). Sibling shape of blocked 0x2B49A8 with resolved pins.
// Names address-derived except the rowed 0x2B388D schedule and pins.
class Refresh0023FA80AI;
class Refresh0023FA80Object;

class Refresh0023FA80Primary
{
public:
	void scheduleNullable(Refresh0023FA80AI *ai, Refresh0023FA80Object *obj);
};

class Rva00318C32Ret
{
public:
	char m_pad[0x13C];
	int m_13C; // +0x13C
};

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
	char m_pad74[0x74];
	unsigned char m_74; // +0x74
};

class Rva0031912E
{
public:
	int rva0031912E();
};

struct Rva002B4C35Outer
{
	char m_pad[0x14];
	int m_14; // +0x14
	char m_pad18[0x1B8 - 0x18];
	int m_begin1B8; // +0x1B8
	int m_end1BC; // +0x1BC
};

class Rva002B4C35
{
public:
	void rva002B4C35();
private:
	char m_pad[0x8C];
	int m_begin8C; // +0x8C
	int m_end90; // +0x90
};

void Rva002B4C35::rva002B4C35()
{
	int d = m_end90;
	d -= m_begin8C;
	unsigned i = 0;
	if ((d >> 2) != 0) {
		do {
			Rva002B4C35Outer *o = ((Rva002B4C35Outer **)m_begin8C)[i];
			int d2 = o->m_end1BC - o->m_begin1B8;
			unsigned j = 0;
			if ((d2 >> 2) != 0) {
				do {
					Rva00318C79Owner *e = ((Rva00318C79Owner **)o->m_begin1B8)[j];
					if (e->m_74 == 0) {
						Rva00318C32Ret *r = e->rva00318C32();
						if (r != 0) {
							int v = r->m_13C;
							if (v == -1) {
								((Refresh0023FA80Primary *)this)->scheduleNullable((Refresh0023FA80AI *)r, (Refresh0023FA80Object *)o);
							}
							else if (v != o->m_14) {
								((Rva0031912E *)e)->rva0031912E();
							}
						}
					}
					++j;
				} while (j < (((o->m_end1BC - o->m_begin1B8) >> 2)));
			}
			++i;
		} while (i < (((m_end90 - m_begin8C) >> 2)));
	}
}
