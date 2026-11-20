// ?bfmeGo1036E@BfmeE1036@@QAEXXZ, retail 0x00664FC0 (37B). Ported from
// Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1036.cpp (BFME1 0x007F7B00).
// Trimmed to the placed E-release body; the A-body (dllimport Wait) is
// declared-only here. Callee repair: the donor names the release helper
// bfmeRelease1036, but both BFME1 (0x00804330) and BFME2 (0x00670370) carry
// that body under the rowed extern-C helper ProtoMangleDestroy, so the call
// spells the rowed name. Zero new pins.

// Rowed in Code/Libraries/Source/DirtySock/Y2ProtoMangleHelpers.cpp.
extern "C" void ProtoMangleDestroy(void *ref);

class BfmeE1036
{
public:
	void bfmeGo1036E(void);

	char m_bfmePad[8];
	void *m_bfmeP;
	char m_bfmePad2[0xc];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

// ?bfmeGo1036E@BfmeE1036@@QAEXXZ
void BfmeE1036::bfmeGo1036E(void)
{
	int empty = 0;

	if (m_bfmeP != 0) {
		ProtoMangleDestroy(m_bfmeP);
		m_bfmeP = (void *)empty;
	}

	m_bfmeA = empty;
	m_bfmeB = empty;
	m_bfmeC = empty;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
