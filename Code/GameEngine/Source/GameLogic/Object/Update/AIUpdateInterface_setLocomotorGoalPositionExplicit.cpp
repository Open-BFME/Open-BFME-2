// cl: /DNDEBUG /MD
//
// ?setLocomotorGoalPositionOnPath@AIUpdateInterface@@UAEXXZ, retail 0x00262C13, 34 bytes.
// ?setLocomotorGoalPositionExplicit@AIUpdateInterface@@UAEXABUCoord3D@@@Z, retail 0x00262C35, 30 bytes.
// ?setLocomotorGoalOrientation@AIUpdateInterface@@UAEXM@Z, retail 0x00262C9B, 27 bytes.
// ZH donor AIUpdate.cpp verbatim locomotor goal setters for m_locomotorGoalType at +0x1FC
// and m_locomotorGoalData at +0x200.

struct Coord3D
{
	float x;
	float y;
	float z;
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

class AIUpdateInterface
{
	char m_pad04[0x1F8];
	int m_locomotorGoalType;
	Coord3D m_locomotorGoalData;
public:
	virtual void setLocomotorGoalPositionOnPath();
	virtual void setLocomotorGoalPositionExplicit(const Coord3D &newPos);
	virtual void setLocomotorGoalOrientation(float angle);
};

void AIUpdateInterface::setLocomotorGoalPositionOnPath()
{
	m_locomotorGoalType = 1;
	m_locomotorGoalData.zero();
}

void AIUpdateInterface::setLocomotorGoalPositionExplicit(const Coord3D &newPos)
{
	m_locomotorGoalType = 2;
	m_locomotorGoalData = newPos;
}

void AIUpdateInterface::setLocomotorGoalOrientation(float angle)
{
	m_locomotorGoalType = 3;
	m_locomotorGoalData.x = angle;
}

