// cl: /DNDEBUG /MD
//
// ?rva0023C420@Rva0023C420@@QAEXXZ @0x0023C420, 20B.
// Null-checked virtual-slot-7 plus operator delete. Retail does
// p=NULL; if (this!=0) p=this->s7(0); ::operator delete(p).
// Evidence: sole caller 0x00241507 passes the Object* it just removed via
// ?removeObjectFromLookupTable@GameLogic@@QAEXPAVObject@@@Z (ebx), so this
// is an Object-family slot, but the vtable owner and slot identity are
// unproven so the name stays address-derived. Callee
// ??3@YAXPAX@Z is rowed (mem_ops.cpp). /O1 selects retail xor-first cmp,
// edx slot load, push-eax and pop-ecx cleanup (defaults give test-ecx,
// push-0 and one extra byte).

void __cdecl operator delete(void *p);

class Rva0023C420
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void *s7(int x);
	void rva0023C420();
};

void Rva0023C420::rva0023C420()
{
	void *p = 0;
	if (this != 0)
		p = s7(0);
	::operator delete(p);
}
