// cl: /DNDEBUG /MD
//
// ?rva00202739@Rva00202739@@QAE_NH@Z @0x00202739 51B. Static-LOD level setter:
// rejects -1, treats level 5 as always-apply, otherwise applies only on change,
// then stores the level at +0x1768 AFTER the apply helper.
// Evidence: independent objdump decoding of [0x00602739..0x0060276C) --
// push esi / mov esi,[esp+8] / cmp esi,-1 / push edi / mov edi,ecx / je false /
// cmp esi,5 / je apply / cmp [edi+0x1768],esi / je false / push esi /
// mov ecx,edi / call 0x002022E9 / mov [edi+0x1768],esi / mov al,1 /
// xor al,al / pop edi / pop esi / ret 4 (ret4 at 0x00602769).
// Adjacent exact body ?rva0020276C@Rva0020276C@@QAE_NH@Z (36B, this same
// directory) is the dynamic-level counterpart and shares the -1 / change-detect
// structure, but the order here is call-then-store, not store-then-call.
// Semantic reference reviewed: BFME1 GameLODManagerApplyStaticLODLevel.cpp
// at donor revision 6583b3c1ff21db4a561285717028fdafc780b7db. Boundary,
// field offset, call target and call-before-store order come from BFME2.
// Level names are donor semantics only: no native GameLODManager spelling is
// asserted for this receiver.
class Rva00202739
{
public:
	bool rva00202739(int level);
	// Native apply body 0x002022E9 (Ghidra extent 707B) takes ECX as receiver and
	// one stack int. Declared only: with the definition visible in this unit
	// keep the call opaque, consistent with retail saving esi/edi.
	void rva002022E9(int level);
	char m_pad[0x1768];
	int m_1768;
};

bool Rva00202739::rva00202739(int level)
{
	if (level != -1) {
		if (level == 5 || m_1768 != level) {
			this->rva002022E9(level);
			m_1768 = level;
			return true;
		}
	}
	return false;
}