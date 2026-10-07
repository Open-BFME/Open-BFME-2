// cl: /DNDEBUG /MD /EHsc
//
// ?getSideInfo@SidesList@@QAEPAVSidesInfo@@H@Z
// retail 0x002035BA, 25 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptList_updateDefaults_Thunk.cpp,
// SidesList::getSideInfo mirror of the Zero Hour layout): bounds-checked index
// into the side array, NULL when out of range. The retail side array sits at
// +0x40 with a 0x60 stride and the count at +0x3C; the script list lives at
// SidesInfo+0x08 (as in the reference header).

class SidesInfo
{
public:
	unsigned char m_data[0x60];
};

class SidesList
{
public:
	SidesInfo *getSideInfo(int i);

private:
	unsigned char m_pad[0x3C];
	int m_numSides; // +0x3C
	SidesInfo m_sides[1]; // +0x40, 0x60 stride
};

// ?getSideInfo@SidesList@@QAEPAVSidesInfo@@H@Z
SidesInfo *SidesList::getSideInfo(int i)
{
	return (i >= 0 && i < m_numSides) ? &m_sides[i] : 0;
}
