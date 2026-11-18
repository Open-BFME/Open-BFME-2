// Command constructor caller 0x0058DE5B names this as the player-index setter;
// the rowed Matrix3D::Set_Y_Translation at 0x00318B09 has the same 10-byte
// dword store at +0x1C. NetCommandMsg's field sequence in
// NetPacket_isRoomForFrameMessage.cpp places this member at +0x1C (object size
// 0x20), so the two independently identified setters are an ICF pair.
#include "../../Include/Common/ScalarTypes.h"

class Rva004D57AE
{
public:
	void setPlayerIndex(UnsignedInt value);

private:
	char m_pad00[0x1C];
	UnsignedInt m_playerIndex;
};

void Rva004D57AE::setPlayerIndex(UnsignedInt value)
{
	m_playerIndex = value;
}
