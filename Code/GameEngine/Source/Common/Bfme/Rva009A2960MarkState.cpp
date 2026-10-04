// cl: /DNDEBUG /MD /EHsc

class Rva009A2960
{
public:
	void markState();
    void markState3();

private:
	unsigned char m_unmodelled_000[0xC068];
	unsigned m_state;
	unsigned char m_flag;
};

void Rva009A2960::markState()
{
	if (m_state != 2)
	{
		m_state = 2;
		m_flag = 1;
	}
}

// Target758920 is a complete29B state update between padding runs.
// Its direct native entry is the owner-pointer tail call758223. It uses the
// same stateC068 and dirty byteC06C as the existing state2 sibling758900;
// original receiver identity, state enum and flag meaning remain unproven.
// Whole clean BF1 donor: game/GameEngine/Source/Common/Bfme/
// Rva009A2960MarkState.cpp at6583b3c1ff21db4a561285717028fdafc780b7db.
// Discovery final/O2; existing home compiler flags retained and both bodies verified.
void Rva009A2960::markState3() {
    if (m_state != 3) {
        m_state = 3;
        m_flag = 1;
    }
}
