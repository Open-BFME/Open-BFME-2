// A constant-field constructor from the R3 scalar-field family.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/R3ScalarFieldConstructors2.cpp); trimmed to
// the T1 body the sweep places. Its sibling 0x000F0F98 is the
// Geometry constructor, now in W3DVolumetricShadowAllocateShadowVolume.cpp.

class Rva006853A0
{
public:
	Rva006853A0();
	int m_00, m_04, m_08, m_0C, m_10, m_14;
	short m_18;
};
Rva006853A0::Rva006853A0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}
