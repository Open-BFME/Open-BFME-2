// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva00171780@MeshModelClass@@QAEXXZ 0x00171780 11B chain calls 0x0015B8C0 loads [ecx+0x94] then jmp
#include "MeshMatDescClass.h"

class MeshModelClass
{
public:
	void rva00171780();
	char m_pad[0x94];
	MeshMatDescClass *m_desc;
};

void MeshModelClass::rva00171780()
{
	m_desc->rva0015B8C0();
}
