// cl: /O2 /G7 /DNDEBUG /MD /EHsc
//
// CPUDetectClass::CPUID - the one place the engine reaches the CPUID
// instruction. Ported from the Westwood source; the __asm block is the
// original author's, not a lift of the retail bytes - BFME1 carries the
// identical block and the two builds agree instruction for instruction.
//
// The frame is what pins this. sub esp,0x10 carries the four unsigned
// locals and the three callee-saved pushes land under them, so inside the
// pushad the compiler reaches cpuid_type at [esp+0x50] and u_eax at
// [esp+0x2C] - the argument slot plus the 0x20 that pushad just spent.
// Naming the locals in the __asm block is what forces them onto the stack
// in that order in the first place.
//
// /G7 is what settles the entry. Retail reads the flag with a single
// cmp byte ptr [HasCPUIDInstruction],0; every other level loads it into al
// and follows with test al,al, which is three bytes longer and puts the
// load ahead of the sub esp. The Pentium-4 scheduler prefers the folded
// memory compare, so this unit was built with /G7 like the DX8Wrapper
// name tables - the flag is per-TU here too.

class CPUDetectClass
{
public:
	static bool Has_CPUID_Instruction() { return HasCPUIDInstruction; }

	static bool CPUID(
		unsigned& u_eax_,
		unsigned& u_ebx_,
		unsigned& u_ecx_,
		unsigned& u_edx_,
		unsigned cpuid_type);

	static bool HasCPUIDInstruction;
};

bool CPUDetectClass::CPUID(
	unsigned& u_eax_,
	unsigned& u_ebx_,
	unsigned& u_ecx_,
	unsigned& u_edx_,
	unsigned cpuid_type)
{
	if (!Has_CPUID_Instruction()) return false;	// Most processors since 486 have CPUID...

	unsigned u_eax;
	unsigned u_ebx;
	unsigned u_ecx;
	unsigned u_edx;

	__asm
	{
		pushad
		mov	eax, [cpuid_type]
		xor	ebx, ebx
		xor	ecx, ecx
		xor	edx, edx
		cpuid
		mov	[u_eax], eax
		mov	[u_ebx], ebx
		mov	[u_ecx], ecx
		mov	[u_edx], edx
		popad
	}

	u_eax_=u_eax;
	u_ebx_=u_ebx;
	u_ecx_=u_ecx;
	u_edx_=u_edx;

	return true;
}
