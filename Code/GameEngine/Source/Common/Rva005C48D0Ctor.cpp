// cl: /MD
// ??0Rva005C48D0@@QAE@XZ @0x005C48D0 21B
// Honest address-derived ctor: stores vtable 0x00C40818 at [this] after
// constructing member at +4 via rowed ??0Rva00330757Member@@QAE@XZ.
// Unlock lane: landing it makes 0x005C4986 ready. Caller at 0x005C499C.
// Prev 0x005C4808 xfer and next 0x005C493A getter in same page. Class has no
// virtuals so the compiler emits no implicit vptr store; the explicit
// *(void **)this write gives retail call-then-store order (Rva0098477Ctor).
extern "C" const void *const vtbl_00C40818[];  // folded, 7 classes; via ??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40818=??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@")

class Rva00330757Member
{
public:
	Rva00330757Member();
};

class Rva005C48D0
{
public:
	Rva005C48D0();
private:
	int m_pad0; // +0 vptr slot written manually
	Rva00330757Member m_mem; // +4
};

Rva005C48D0::Rva005C48D0()
{
	*(void **)this = (void *)((unsigned int)vtbl_00C40818);
}
