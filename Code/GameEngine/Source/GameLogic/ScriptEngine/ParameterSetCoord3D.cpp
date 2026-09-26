// cl: /O1 /DNDEBUG /MD
//
// ?setCoord3D@Parameter@@IAEXPBUCoord3D@@@Z, retail 0x003B27E2 (22 bytes).
// Parameter::setCoord3D protected setter: if m_paramType==COORD3D (0x10),
// copies 12 bytes from *pLoc to m_coord at +0x14 (3x movsd string moves).
// Donor ZH Scripts.cpp Parameter::setCoord3D with DEBUG_ASSERTCRASH compiled
// out (/DNDEBUG). Caller at 0x003B5D0F.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter
{
protected:
	void setCoord3D(const Coord3D *pLoc);

private:
	int m_paramType; // +0x00, COORD3D is 0x10
	char m_pad[0x10]; // +0x04
	Coord3D m_coord; // +0x14
};

void Parameter::setCoord3D(const Coord3D *pLoc)
{
	if (m_paramType == 0x10) {
		m_coord = *pLoc;
	}
}
