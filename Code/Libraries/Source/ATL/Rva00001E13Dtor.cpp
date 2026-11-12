// cl: /EHsc
// ??1Rva00001E13@@QAE@XZ 0x00001E13 8B
// Evidence: leaf 8B add ecx,4 + jmp rowed ??1W3DRadarResetSurface@@QAE@XZ; wrapper with member at +4.

#include "../../../GameEngine/Include/Common/W3DRadarResetSurface.h"

class Rva00001E13
{
public:
	~Rva00001E13();
private:
	int m_00;
	W3DRadarResetSurface m_04;
};

Rva00001E13::~Rva00001E13()
{
}
