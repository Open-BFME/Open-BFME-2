// cl: /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?rva0005C892@Rva0005C892@@QAEXXZ @0x0005C892 41B.
// Zero the float at +0x90, default-construct the 8-byte Rva00052B3D helper
// (rowed ctor ??0Rva00052B3D@@QAE@XZ) in an 8-byte frame slot, then call the
// rowed MilesAudioManager::processPlayingList at 0x0005C23C with its address.
// Target facts: xorps-zero movss store precedes the ctor call; the helper
// call takes the single local-pointer argument; /Oy- frame with leave.
class Rva00052B3D
{
public:
	Rva00052B3D();
private:
	int m_a;
	int m_b;
};

class Rva0005C892
{
public:
	void rva0005C892();
private:
	char m_pad00[0x90];
	float m_vol90;
};

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

void Rva0005C892::rva0005C892()
{
	m_vol90 = 0.0f;
	Rva00052B3D tmp;
	reinterpret_cast<MilesAudioManager *>(this)->processPlayingList(&tmp);
}
