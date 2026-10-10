// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// One of the BFME 1 "release the pointer I own, then forget it" bodies:
//
//     mov esi,ecx / mov eax,[esi+OFF] / test eax,eax / je ...
//     push eax / call <free> / add esp,4 / mov dword ptr [esi+OFF],0 / ret
//
// `mov esi,ecx` is __thiscall -- a member, not a pointer parameter of a free
// __cdecl function, which would arrive as `mov esi,[esp+8]`.
//
// WHERE THE NULL STORE SITS IS NOT COSMETIC. The forward branch either lands on
// the store or past it, and that distinguishes
//     if (p) { free(p); p = 0; }
// from
//     if (p) free(p); p = 0;
// as source, and gives different displacements. Here the store sits INSIDE the
// guard: 0x0023C631 `je` lands at 0x0023C63F, past the store.
//
// CALLEE IDENTITY. The indirect `call dword ptr [0x00BBA5DC]` goes through a
// function-pointer variable at a fixed address. That is a DIR32 site, so
// build.py copies the four bytes from retail and they are NOT evidence: the
// slot is never named here, and this file makes no claim about what it holds.
// The only thing the call site itself proves is a __cdecl function taking one
// pointer.
//
// IDENTITY IS NOT RECOVERED. The class is the RVA of the body, the owned field
// is named for its offset, and the leading filler is not a claim that anything
// else lives there.

// ?release@Rva00382AA0@@QAEXXZ
// retail 0x0023C629, 24 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/R3GuardedReleaseAndClear.cpp
// (reference/open-bfme-1 @ 6d943426). Byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other five release bodies are omitted.

// Gen00BBA5DC is the import slot __imp__fclose (data ledger); call the
// import directly so nothing dangles.
extern "C" __declspec(dllimport) int __cdecl fclose(void *fp);

class Rva00382AA0
{
public:
	void release();
	char m_lead[0x18];
	void *m_18;
};
void Rva00382AA0::release()
{
	if ( m_18 )
	{
		fclose( m_18 );
		m_18 = 0;
	}
}