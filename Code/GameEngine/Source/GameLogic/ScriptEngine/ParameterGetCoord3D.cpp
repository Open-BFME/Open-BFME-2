// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?getCoord3D@Parameter@@QBEXPAUCoord3D@@@Z, retail 0x003B27BB (39 bytes).
// Parameter::getCoord3D const getter: zeroes *pLoc via xmm0/movss, then if
// m_paramType==COORD3D (0x10) copies m_coord at +0x14 (3x movsd string moves).
// Donor ZH Scripts.cpp Parameter::getCoord3D with DEBUG_ASSERTCRASH compiled
// out (/DNDEBUG). /arch:SSE for xorps/movss zeroing.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter
{
public:
	void getCoord3D(Coord3D *pLoc) const;

private:
	int m_paramType; // +0x00, COORD3D is 0x10
	char m_pad[0x10]; // +0x04
	Coord3D m_coord; // +0x14
};

void Parameter::getCoord3D(Coord3D *pLoc) const
{
	pLoc->x = pLoc->y = pLoc->z = 0;
	if (m_paramType == 0x10) {
		*pLoc = m_coord;
	}
}
