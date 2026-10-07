// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x001D5470 is the cdecl CPU-feature probe called by the
// jump-table dispatcher at 0x001C4390 (sole caller: calls the probe,
// maps 0/1 to flag 1/12, dispatches through the table at 0x5C441C).
// Ported from the Open-BFME-1 conversion of its twin at 0x009C4B70
// (Code/GameEngine/Source/Common/Rva009C4B70CpuFeatureProbe.cpp).
// CPUID is inline because MSVC 7.1 has no intrinsic for it; the
// surrounding vendor test and SEH remain ordinary C++.
// The row covers the SEH filter and handler funclets retail places after the
// body (0x001D5510..0x001D553F, 208 bytes in all). The filter saves the
// exception code, which only happens when the handler reads it, and retail
// reads it then returns the constant 0 (result is still 0 on that path).

#include <excpt.h>
extern "C" unsigned long __cdecl _exception_code(void);
#define GetExceptionCode _exception_code


extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int);

// ?Rva001D5470_CpuFeatureProbe@@YAHXZ
int __cdecl Rva001D5470_CpuFeatureProbe(void)
{
	char vendor[12];
	int result;

	result = 0;
	__try
	{
		__asm
		{
			lea	esi, vendor
			mov	eax, 0
			cpuid
			mov	dword ptr [esi], ebx
			mov	dword ptr [esi+4], edx
			mov	dword ptr [esi+8], ecx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		unsigned long code = GetExceptionCode();
		if (code)
			return result;
		return result;
	}

	if (strncmp(vendor, "GenuineIntel", 12) == 0
		|| strncmp(vendor, "AuthenticAMD", 12) == 0)
	{
		__asm
		{
			mov	eax, 1
			cpuid
			test	edx, 04000000h
			je	no_sse2
			mov	result, 1
		no_sse2:
			nop
		}
	}

	return result;
}
