// ?rva002B5A5F@Rva002B5A5F@@QAE_NPAURva002B5A5FArg@@@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /MD
// Range-11 pair sharing class Rva002B5A5F (5AF7 calls 5A5F in-TU).
// ?rva002B5A5F@Rva002B5A5F@@QAE_NPAURva002B5A5FArg@@@Z @0x002B5A5F 152B:
// __thiscall bool probe on a Rva002B5A5FArg. True only through the late
// m_f4 gate (zero, or 4 with an empty +0x18 string and a rowed 0x2B4BC9
// hit). Early outs on null +0x98, failed rowed 0x2B59FF/0x2B254F probes,
// failed virtual check, clear +0x58 flag or failed rowed 0x318D05 check.
// Evidence: retail
//   push esi; mov esi,ecx; cmp [esi+0x98],0; je FAIL
//   call 0x2B59FF; test al,al; jne DO; FAIL: xor al,al; jmp END
//   DO: push edi; mov ecx,esi; call 0x2B254F; test al,al
//   mov edi,[esp+0xC]; je ALT
//   mov ecx,[0xE02D6C]; call 0x3B8BAA; mov edx,[eax]
//   push edi; mov ecx,eax; call [edx+4]; test al,al; jne ALT
//   xor al,al; jmp END2
//   ALT: cmp byte [edi+0x58],0; je FAIL2; mov eax,[esi+0x98]
//   push ebx; push [eax+0x14]; mov ecx,edi; call 0x318D05
//   test al,al; je FAIL2; cmp byte [edi+0x58],0; je FAIL2
//   mov ebx,[esi+0xF4]; test ebx,ebx; jne HASF4
//   mov al,1; jmp END3
//   HASF4: lea ecx,[edi+0x18]; call 0x1E2F(isEmpty); test al,al; jne FAIL2
//   cmp ebx,4; jne FAIL2; push edi; mov ecx,esi; call 0x2B4BC9
//   test al,al; jne TRUEBACK; FAIL2: xor al,al
// END3/END2/END share pops by push depth. The 0x2B254F int result is
// consumed through (char) to reproduce the test-al shape.
// ?rva002B5AF7@Rva002B5A5F@@QAEXXZ @0x002B5AF7 94B: __thiscall void sweep
// over the +0x98 object's +0x1B8/+0x1BC table with per-pass recount,
// probing each element through 0x2B5A5F and reporting to rowed 0x318C05.
// Evidence: retail
//   push ebp; mov ebp,esp; push ecx; push ecx; push esi
//   mov esi,[ecx+0x98]; test esi,esi; mov [ebp-4],ecx; je EXIT
//   mov eax,[esi+0x1B8]; mov ecx,[esi+0x1BC]; push edi
//   sub ecx,eax; xor edi,edi; sar ecx,2; je INNER_DONE
//   push ebx; LOOP: mov ebx,[eax+edi*4]; mov ecx,[ebp-4]
//   push ebx; call 0x2B5A5F; mov [ebp-8],al; push [ebp-8]
//   mov ecx,ebx; call 0x318C05; reload; inc edi; sar; cmp edi,ecx
//   jb LOOP; pop ebx; INNER_DONE: pop edi; EXIT: pop esi; leave; ret
// Boundary: 152B [0x2B5A5F,0x2B5AF7) + 94B [0x2B5AF7,0x2B5B55); prev
// xor/pop/ret, next prologue (0x2B5B55). Names address-derived except
// rowed callees, the established g_00E02D6C global and pins.
class AsciiString
{
	char m_opaque[4]; // size 4 from evidence: m_str18 at +0x18 with m_58 at +0x58
public:
	bool isEmpty() const;
};

struct Rva002B5A5FArg
{
	char m_pad[0x18];
	AsciiString m_str18; // +0x18
	char m_pad1C[0x58 - 0x1C];
	unsigned char m_58; // +0x58
};

struct Rva002B5A5FHolder
{
	char m_pad[0x14];
	int m_14; // +0x14
	char m_pad18[0x1B8 - 0x18];
	int m_begin1B8; // +0x1B8
	int m_end1BC; // +0x1BC
};

class Rva002B59FF
{
public:
	bool rva002B59FF();
};

class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva003B8BAA
{
public:
	void *rva003B8BAA();
};

extern Rva003B8BAA *g_00E02D6C;

class Rva002B5A5FVirt
{
public:
	virtual void *v0();
	virtual bool v4(Rva002B5A5FArg *arg);
};

class Rva00318D05
{
public:
	bool rva00318D05(int v);
};

struct Rva002B4BC9Arg;
class Rva002B4BC9
{
public:
	bool rva002B4BC9(Rva002B4BC9Arg *arg);
};

class Rva00318C05
{
public:
	void rva00318C05(bool b);
};

class Rva002B5A5F
{
public:
	bool rva002B5A5F(Rva002B5A5FArg *arg);
	void rva002B5AF7();
private:
	char m_pad[0x98];
	Rva002B5A5FHolder *m_ptr98; // +0x98
	char m_pad9C[0xF4 - 0x9C];
	int m_f4; // +0xF4
};

bool Rva002B5A5F::rva002B5A5F(Rva002B5A5FArg *arg)
{
	if (m_ptr98 != 0) {
		if (!((Rva002B59FF *)this)->rva002B59FF())
			return false;
		if ((char)((Rva002B254F *)this)->rva002B254F()) {
			Rva002B5A5FVirt *v = (Rva002B5A5FVirt *)((Rva003B8BAA *)g_00E02D6C)->rva003B8BAA();
			if (v->v4(arg)) {
				if (arg->m_58 != 0) {
					int t = m_ptr98->m_14;
					if (((Rva00318D05 *)arg)->rva00318D05(t)) {
						if (arg->m_58 != 0) {
							int f = m_f4;
							if (f == 0)
								return true;
							if (arg->m_str18.isEmpty())
								return false;
							if (f != 4)
								return false;
							if (((Rva002B4BC9 *)this)->rva002B4BC9((Rva002B4BC9Arg *)arg))
								return true;
							return false;
						}
					}
				}
			}
		}
	}
	return false;
}

void Rva002B5A5F::rva002B5AF7()
{
	Rva002B5A5F *t = this;
	Rva002B5A5FHolder *o = m_ptr98;
	if (o == 0)
		return;
	const int d = o->m_end1BC - o->m_begin1B8;
	unsigned j = 0;
	if ((d >> 2) != 0) {
		do {
			Rva002B5A5FArg *e = ((Rva002B5A5FArg **)o->m_begin1B8)[j];
			bool b = t->rva002B5A5F(e);
			((Rva00318C05 *)e)->rva00318C05(b);
			++j;
		} while (j < (((o->m_end1BC - o->m_begin1B8) >> 2)));
	}
}
