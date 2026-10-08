// cl: /O1 /DNDEBUG /MD
// ?setLocomotorGoalPositionExplicitSmart@AIUpdateInterface@@UAEXABUCoord3D@@@Z @0x00262C53 72B. Slot 133 of 8
// AIUpdate vtables: if (m_1FC != 4) delete Path at +0x140 via rowed
// ??1Path@@QAE@XZ plus rowed ??3@YAXPAX@Z and null it; set m_1FC=4; copy 12B
// Coord3D arg to +0x200 via 3x movsd. Prev setLocomotorGoalPositionExplicit.
// Identity: WorldBuilder's AIUpdate.cpp:4256-4258 defines
// AIUpdateInterface::setLocomotorGoalPositionExplicitSmart with exactly this
// body (m_locomotorGoalType +0x1FC != 4 -> delete the +0x140 Path; type 4;
// copy the position to +0x200).
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Path {
public:
	~Path();
};
class AIUpdateInterface {
public:
	virtual void setLocomotorGoalPositionExplicitSmart(const Coord3D &newPos);
private:
	char m_pad00[316];
	Path *m_140;
	char m_pad144[184];
	int m_1FC;
	Coord3D m_200;
};
void AIUpdateInterface::setLocomotorGoalPositionExplicitSmart(const Coord3D &newPos)
{
	if (m_1FC != 4) {
		delete m_140;
		m_140 = 0;
	}
	m_1FC = 4;
	m_200 = newPos;
}
