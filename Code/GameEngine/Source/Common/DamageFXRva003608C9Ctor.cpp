// cl: /DNDEBUG /MD
// ??0Rva003608C9@@QAE@XZ, retail 0x003608C9, 22 bytes.
// Array ctor of 0x78 DFX via vector iterator.
// Evidence: unlock lane; callees DFX ctor ??_H; caller 0x00360ABA; HEAD START fc600b627.
#include "../../Include/Common/DamageFXClass.h"
class Rva003608C9
{
public:
	Rva003608C9();
private:
	DamageFX::DFX m_arr[0x78];
};
Rva003608C9::Rva003608C9()
{
}
