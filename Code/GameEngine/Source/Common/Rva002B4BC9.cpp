// cl: /MD
// ?rva002B4BC9@Rva002B4BC9@@QAE_NH@Z @0x002B4BC9 64B: __thiscall bool fetch.
// When the rowed StringBase<char>::isEmpty on the +0x18 member of the
// argument passes false, fetches through the cdecl 0x20E873 worker with the
// +0x10C/+0x110 members and a dead stack temp (homed over the dead arg
// slot), returning whether the result differs from +0x110. Evidence: retail
//   push esi; mov esi,ecx; mov ecx,[esp+8]; add ecx,0x18; call 0x1E2F
//   test al,al; je ELSE; xor al,al; jmp END
//   ELSE: push edi; mov edi,[esi+0x110]; lea eax,[esp+0xC]; push eax
//   push edi; push [esi+0x10C]; call 0x20E873; add esp,0xC
//   xor ecx,ecx; cmp eax,edi; setne cl; mov al,cl; pop edi
//   END: pop esi; ret 4
// Boundary: Ghidra FUN_006b4bc9-adjacent 64B; successor 0x2B4C09 is the
// next range target. Names are address-derived except the rowed isEmpty.
// class-gate: allow AsciiString TU-local isEmpty-only view; the shared header defines isEmpty inline and the compiler would inline it, erasing the rowed out-of-line call at 0x00001E2F that retail makes here.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct Rva002B4BC9Arg
{
	char m_pad[0x18];
	AsciiString m_str18;
};

// The search is the rowed STLport find<CreateAHeroData **, CreateAHeroData *>.
class CreateAHeroData;
namespace _STL
{
template <class It, class T> It find(It first, It last, const T &value);
}

class Rva002B4BC9
{
public:
	bool rva002B4BC9(Rva002B4BC9Arg *arg);
private:
	char m_pad[0x10C];
	int m_arg10C;
	int m_arg110;
};

bool Rva002B4BC9::rva002B4BC9(Rva002B4BC9Arg *arg)
{
	if (arg->m_str18.isEmpty())
		return false;
	// The worker's temp is homed by the optimizer over this function's own
	// dead argument slot (retail lea eax,[esp+0xC] == incoming arg home
	// after the two saves, with no sub esp and no ebp frame). Spelling it
	// as a named int local forces an ebp frame and misses; taking the
	// parameter's address reproduces the slot reuse exactly.
	int lim = m_arg110;
	int got = (int)_STL::find<CreateAHeroData **, CreateAHeroData *>((CreateAHeroData **)m_arg10C, (CreateAHeroData **)lim, *(CreateAHeroData *const *)&arg);
	return got != lim;
}
