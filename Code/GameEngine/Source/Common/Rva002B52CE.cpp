// cl: /MD
// ?rva002B52CE@Rva002B52CE@@QAEXXZ @0x002B52CE 102B: __thiscall void sweep.
// Skips everything when the +0x8C/+0x90 table holds under 4 bytes
// (test eax,-4 / jle: the (diff>>2)<=0 shape, which MSVC folds to the mask
// test without the sar). Otherwise each pass resolves index 0 through the
// rowed 0x2B52A8 lookup, fires state2/state1 on a non-sentinel element, and
// runs the 0x4FBB25 worker on its +0x4C subobject, recounting every pass.
// Evidence: retail
//   push ebx/esi; mov esi,ecx; mov eax,[esi+0x90]; sub eax,[esi+0x8C]
//   xor ebx,ebx; test eax,0xFFFFFFFC; jle END
//   TOP: push edi; push ebx; mov ecx,esi; call 0x2B52A8; mov edi,eax
//   cmp edi,[esi+0x98]; je WORK
//   cmp [edi+0x44],1; mov ecx,edi; jne ALT; call state2; jmp WORK
//   ALT: call state1
//   WORK: push [esi+0xF4]; lea ecx,[edi+0x4C]; call 0x4FBB25
//   mov eax,[esi+0x90]; sub eax,[esi+0x8C]; inc ebx; sar eax,2
//   cmp ebx,eax; jl TOP; pop edi; END: pops; ret
// Boundary: range-table 102B ending at 0x2B5334 (push ebx). Element layout
// (m_44 flag) matches the established Rva002E2903Player view. Names are
// address-derived except rowed callees and state pins.
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int index);
};

class Rva004FBB25Sub
{
public:
	void rva004FBB25(int val);
};

class Rva002E2903Player
{
public:
	void state2();
	void state1();
	char m_pad[0x44];
	int m_44;
	char m_pad48[0x4C - 0x48];
	Rva004FBB25Sub m_4C;
};

class Rva002B52CE
{
public:
	void rva002B52CE();
private:
	char m_pad[0x8C];
	int m_begin8C;
	int m_end90;
	int m_pad94;
	Rva002E2903Player *m_sentinel98;
	char m_pad9C[0xF4 - 0x9C];
	int m_f4;
};

void Rva002B52CE::rva002B52CE()
{
	int d = m_end90 - m_begin8C;
	int i = 0;
	if ((d >> 2) <= 0)
		return;
	do {
		Rva002E2903Player *p = ((Rva002BA8F1Logic *)this)->rva002B52A8(i);
		if (p != m_sentinel98) {
			if (p->m_44 == 1) {
				p->state2();
			}
			else {
				p->state1();
				p->m_4C.rva004FBB25(m_f4);
			}
		}
		++i;
	} while (i < ((m_end90 - m_begin8C) >> 2));
}
