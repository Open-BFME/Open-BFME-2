// cl: /EHsc
// platformsdk
// ?rva002DC681@Rva002DC267@@QBE_NXZ, retail 0x002DC681, 201 bytes.
//
// Save-dir disk-space check via rva002DC267 + GetDiskFreeSpaceExW. Retail
// str() falls back to UnicodeString TheNullChr at 0x00BBB5C4
// (?TheNullChr@?1??str@UnicodeString) when m_data is null; see the
// class-gate note below for why this body keeps a private view of that.
//
// The 0.99 bank reached 199 bytes and was missing the `jb` at +0x99. Retail
// splits the free-space test into a three-way unsigned branch on the high
// dword:
//
//   cmp  DWORD PTR [ebp-0x18], edi   ; high word vs a register zero
//   ja   +0x0f                        ; -> mov bl,1  (plenty of space)
//   jb   +0x09                        ; -> the low-word compare
//   cmp  DWORD PTR [ebp-0x1c], 0F00000h
//
// which is ONE predicate, not two nested tests: `ja` and `jb` are the two
// arms of a single unsigned comparison and the `jb` arm falls into the same
// low-word compare as the equal case. Spelled as the two-armed ternary the
// bank used (`if (hi > 0) ok = true; else if (lo >= F00000) ...`) MSVC folds
// the pair into a single test/ja, dropping the `jb` and the two bytes with it.
// Written as one disjunction both arms survive and the body is byte-exact:
//
//   ok = ((unsigned)(freeBytes.QuadPart >> 32) > 0u) || (freeBytes.QuadPart >= 0xF00000);
//
// Everything else in the bank was already correct: the UnicodeString temporary,
// the isEmpty guard that only calls set() when the string has data, and the
// ok-is-true-on-API-failure arm.

typedef int Int;
typedef unsigned short WideChar;
#include <windows.h>
#include "../../../../../../reference/shims/bfme2_ascii/unicode_string.h"

#include "../../../../Include/Common/Rva002DC267.h"

bool Rva002DC267::rva002DC681() const
{
	UnicodeString path(L"C:\\");	// retail literal VA 0x00C03F94
	bool has = !rva002DC267().isEmpty();
	if (has) {
		path.set(rva002DC267());
	}
	ULARGE_INTEGER freeBytes;
	freeBytes.QuadPart = 0;
	bool ok;
	if (GetDiskFreeSpaceExW(path.str(), &freeBytes, 0, 0) != 0) {
		ok = ((unsigned)(freeBytes.QuadPart >> 32) > 0u) || (freeBytes.QuadPart >= 0xF00000);
	} else {
		ok = true;
	}
	return ok;
}