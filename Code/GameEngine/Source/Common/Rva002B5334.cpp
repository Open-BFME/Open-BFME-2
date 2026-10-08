// cl: /O1 /MD
// ?AutoMarkUnitsForUpgrades@LivingWorldLogic@@QAEXXZ @0x002B5334 92B: __thiscall void sweep
// over the +0x2C element table behind +0xB0/+0x08. Each element whose +0x13C
// id is not -1 resolves through the rowed 0x2B51F8 find (id, NULL) and is
// handed to the 0x2E2D8D pin, recounting every pass. Evidence: retail
//   push ebx/ebp; mov ebp,ecx; mov eax,[ebp+0xB0]; mov eax,[eax+8]
//   test eax,eax; push esi; je NULL; lea esi,[eax+0x2C]; jmp TEST
//   NULL: xor esi,esi
//   TEST: mov eax,[esi]; mov ecx,[esi+4]; sub ecx,eax; xor ebx,ebx
//   sar ecx,2; je END
//   LOOP: push edi; mov edi,[eax+ebx*4]; mov eax,[edi+0x13C]
//   cmp eax,-1; je NEXT
//   push 0; push eax; mov ecx,ebp; call 0x2B51F8
//   push edi; mov ecx,eax; call 0x2E2D8D
//   NEXT: mov eax,[esi]; mov ecx,[esi+4]; sub ecx,eax; inc ebx
//   sar ecx,2; cmp ebx,ecx; jb LOOP
//   pop edi; END: pops; ret
// The null-subobject path dereferences [0] exactly like retail (callers
// guarantee non-null; the branch is defensive). Boundary: range-table 92B
// ending at 0x2B5390 (mov eax,[ecx+0xF4]). Names are address-derived
// except rowed callees.
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class Rva002E2903Player
{
public:
	void rva002E2D8D(void *elem);
};

class Rva002B5334Elem
{
public:
	char m_pad[0x13C];
	int m_id13C;
};

struct Rva002B5334Vec
{
	Rva002B5334Elem **m_begin;
	Rva002B5334Elem **m_end;
};

class Rva002B5334Sub
{
public:
	char m_pad[0x2C];
	Rva002B5334Vec m_vec2C;
};

class Rva002B5334Mid
{
public:
	char m_pad[0x08];
	Rva002B5334Sub *m_sub8;
};

class LivingWorldLogic
{
public:
	void AutoMarkUnitsForUpgrades();
private:
	char m_pad[0xB0];
	Rva002B5334Mid *m_midB0;
};

void LivingWorldLogic::AutoMarkUnitsForUpgrades()
{
	Rva002B5334Sub *sub = m_midB0->m_sub8;
	Rva002B5334Vec *vec;
	if (sub != 0)
		vec = &sub->m_vec2C;
	else
		vec = 0;
	for (unsigned i = 0; i < (unsigned)(((char *)vec->m_end - (char *)vec->m_begin) >> 2); ++i) {
		Rva002B5334Elem *elem = vec->m_begin[i];
		int id = elem->m_id13C;
		if (id != -1) {
			Rva002E2903Player *p = ((Rva002BA8F1Logic *)this)->find(id, 0);
			p->rva002E2D8D(elem);
		}
	}
}
