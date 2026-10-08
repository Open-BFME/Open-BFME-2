// cl: /DNDEBUG /MD
//
// ?rva0023C6A4@Rva0023C6A4@@QAE_NXZ @0x0023C6A4, 33B.
// Mode-plus-singleton predicate: true when m_unk114==3, the 0xDFEF10
// singleton is present, and its byte at +0xB4 is non-zero.
// Retail: cmp [ecx+0x114],3 jne false; mov eax,[0xDFEF10]; test; je false;
// cmp [eax+0xB4],0 je false; mov al,1 ret; false xor al,al ret.
// Evidence: six callers pass the same this (e.g. 0x002034E9 re-checks
// [ecx+0x114]==3 before calling); +0x114==3 matches GameLogic m_unk114
// (GameLogicModeGateChecks.cpp) but owner unproven so Rva class; global
// proven by Rva002BA8F1Logic find callers using 0xDFEF10. &&-chain shares
// the single false block (separate early returns give setne shape).
//
// ?rva00200084@Rva0023C6A4@@QAE_NXZ @0x00200084, 32B.
// OR of global-mode check 0x0023D607 and this predicate 0x0023C6A4.
// Evidence: chain lane (0x0023D607 just landed); same this passed to
// 0x0023C6A4; 12 callers; retail push-esi test-je test-je xor/inc shape.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
typedef bool Bool;

unsigned char Rva0023D607Get();

class Rva0023C6A4
{
public:
	Bool rva0023C6A4();
	Bool rva00200084();

private:
	char m_pad[0x114];
	int m_unk114; // +0x114
};

Bool Rva0023C6A4::rva0023C6A4()
{
	if (m_unk114 == 3 && (*(void **)&TheLivingWorldLogic) != 0 && *(unsigned char *)((char *)(*(void **)&TheLivingWorldLogic) + 0xB4) != 0)
		return true;
	return false;
}

Bool Rva0023C6A4::rva00200084()
{
	return Rva0023D607Get() || rva0023C6A4();
}
