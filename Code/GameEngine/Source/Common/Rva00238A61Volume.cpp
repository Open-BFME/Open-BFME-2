// cl: /MD /EHsc
// stlport
// ?rva00238A61@Rva00238A61@@QAEXXZ @0x00238A61 85B
// Evidence: rowed OptionPreferences ctor 0x002E434E and getVolume 0x002E4B2D
// plus rowed OptionPreferences dtor 0x002E4272; global
// float 0.01 at 0x00BCF628 via 0.01f; caller 0x0004171A; precedent
// Code/GameEngine/Source/Common/Rva0051847BAudio.cpp for the
// OptionPreferences local shape and 5-volume loop.
#include "../../Include/Common/OptionPreferences.h"
class Rva00238A61
{
public:
	void rva00238A61();
private:
	char m_pad[0x30];
	float m_volumes[5];
};
void Rva00238A61::rva00238A61()
{
	OptionPreferences prefs;
	for (int i = 0; i < 5; ++i)
		m_volumes[i] = prefs.getVolume(i) * 0.01f;
}
