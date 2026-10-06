// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// ?test@Rva004104F0@@QAE_NI@Z, retail 0x000788C0 (19B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/Rva004104F0Test.cpp
// (BFME1 0x004104F0). The donor bytes are the only free placement: the other
// candidate sits inside the matched ?Inverse_Rotate_Vector@Matrix3D (181B at
// 0x0013F160), so elimination leaves this address. The neg/sbb/neg tail is
// the bool normalization of (m_114 & mask) != 0.

class Rva004104F0
{
	char m_pad[0x114];
	unsigned m_114;

public:
	bool test(unsigned mask);
};

bool Rva004104F0::test(unsigned mask)
{
	return (m_114 & mask) != 0;
}
