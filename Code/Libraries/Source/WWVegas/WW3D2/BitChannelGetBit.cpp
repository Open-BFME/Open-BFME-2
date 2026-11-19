// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD
// ?Get_Bit@BitChannelClass@@QAEHH@Z, retail 0x00160110 (59 bytes, RET 4), between the raw
// animation channel readers: Zero Hour hrawanim BitChannelClass::Get_Bit -- the default
// value outside [FirstFrame, LastFrame], else the frame's bit of the packed Bits array (the
// mask is formed as a byte).
typedef unsigned int uint32;
#include "../../../../GameEngine/Include/Common/ScalarTypes/Source/uint8.h"

class BitChannelClass
{
public:
	int Get_Bit(int frame);

private:
	uint32 PivotIdx;
	uint32 Type;
	int DefaultVal;
	int FirstFrame;
	int LastFrame;
	uint8 *Bits;
};

int BitChannelClass::Get_Bit(int frame)
{
	if (frame < FirstFrame || frame > LastFrame)
		return DefaultVal;
	int bit = frame - FirstFrame;
	return (Bits[bit >> 3] & (uint8)(1 << (bit & 7))) != 0;
}
