// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common/System
// Four inline-asm profiler helpers recovered from the Open-BFME-1 donor
// game/GameEngine/Source/Common/System/Rva54b800.cpp (reference/open-bfme-1),
// recompiled /Os. Each is byte-identical to retail once relocations are masked,
// at a unique masked placement on unclaimed .text:
//
//   ?rva54b800@@YAPAXXZ  0x00226819  16 B  mov [esp],esp  -- the stack pointer
//   ?rva61b20@@YAPAXXZ   0x00226809  16 B  mov [esp],ebp  -- the frame pointer
//   ?rva61ae0@@YAIXZ    0x0056E692  18 B  rdtsc
//   ?rva61b40@@YAIXZ    0x0056DD9C  20 B  pushfd
//
// INLINE ASSEMBLY IS REQUIRED, NOT CHOSEN.  `rdtsc` has no VC7.1 intrinsic
// (`__rdtsc` arrives with VC8) and `pushfd` has none at all; reading ebp as a
// value is not expressible in C++ in any compiler.  The `mov [esp],esp` body
// needs it too: MSVC 7.1 always materialises the address of an address-taken
// local into a register at the top of the function (`lea eax,[esp]`), and the
// thirteen C++ spellings that were tried all reproduce that hoisted lea.
// Naming the local directly in an `__asm` block assembles to `mov DWORD PTR
// stackPtr$[esp], esp`, which is 89 24 24 exactly because the slot sits at
// displacement zero.
//
// These four are emitted out of line once per translation unit that includes
// the header, which is why each occurs many times over .text as an identical
// copy: MSVC 7.1 refuses to inline a function containing inline assembly.  At a
// fixed 0x20 stride the copies interleave, e.g. 0x0006DDB0 / 0x0006DE30 /
// 0x0006DEB0 / 0x0006DF30.  The corpus-wide counts are 44, 32, 25 and 22.
//
// IDENTITY IS NOT RECOVERED for any of them.  No named caller reaches them and
// no string or RTTI descriptor in the image names them, so the names are
// address-derived placeholders.  A profiler or stack-walker header is the
// obvious home for the set, but "obvious" is not evidence and no such name
// survives in the image.
//
// The dead `mov [esp],0` in front of each body is the local's zero-initialiser,
// which survives /O2 only because an `__asm` block follows it and the
// optimiser stops tracking the slot.


// ?rva54b800@@YAPAXXZ -- retail 0x00226819, 16 bytes
void *rva54b800( void )
{
	void *stackPtr = 0;

	__asm mov stackPtr, esp

	return stackPtr;
}

// ?rva61ae0@@YAIXZ -- retail 0x0056E692, 18 bytes
// push ecx / mov [esp],0 / rdtsc / mov [esp],eax / mov eax,[esp] / pop ecx / ret
unsigned int rva61ae0( void )
{
	unsigned int cycles = 0;

	__asm
	{
		rdtsc
		mov cycles, eax
	}

	return cycles;
}

// ?rva61b20@@YAPAXXZ -- retail 0x00226809, 16 bytes
void *rva61b20( void )
{
	void *framePtr = 0;

	__asm mov framePtr, ebp

	return framePtr;
}

// ?rva61b40@@YAIXZ -- retail 0x0056DD9C, 20 bytes
//     51                push ecx                 ; the local's slot
//     c7 04 24 00000000 mov dword ptr [esp],0    ; its zero-initialiser
//     50                push eax
//     9c                pushfd
//     58                pop eax
//     89 44 24 04       mov dword ptr [esp+4],eax
//     58                pop eax
//     8b 04 24          mov eax,dword ptr [esp]
//     59                pop ecx
//     c3                ret
// The store to the local is spelled [esp+4] and not [esp]: MSVC adjusting the
// local's displacement for the `push eax` that precedes it inside the same asm
// block -- the source names the variable, not a displacement.  The
// push eax / pop eax pair is the caller-visible register preserved by hand.
unsigned int rva61b40( void )
{
	unsigned int flags = 0;

	__asm
	{
		push eax
		pushfd
		pop eax
		mov flags, eax
		pop eax
	}

	return flags;
}
