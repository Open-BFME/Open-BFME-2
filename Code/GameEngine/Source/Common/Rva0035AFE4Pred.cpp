// cl: /DNDEBUG /MD
// ?rva0035AFE4@Rva0035AFE4@@QAE_NH@Z retail 0x0035AFE4 44B
// Predicate testing the relationship mask at +0x1c: arg 0 tests bit 0,
// arg 1 tests bit 1, arg 2 tests bit 2, any other arg tests nothing.
// Evidence: unlock lane, callers at 0x0035B031 (passes Player
// getRelationship result) and 0x0035B05C, ecx-first thiscall with ret 4,
// sibling CommandButton::isContextCommand (0x0035B140, bit 9 of m_1c).

class Rva0035AFE4
{
public:
	bool rva0035AFE4(int which);

private:
	char m_pad[0x1c];
	unsigned int m_1c;
};

bool Rva0035AFE4::rva0035AFE4(int which)
{
	int bit = 0;
	if (which == 0) {
		bit = 1;
	} else if (which == 2) {
		bit = 4;
	} else if (which == 1) {
		bit = 2;
	}
	return (m_1c & bit) != 0;
}
