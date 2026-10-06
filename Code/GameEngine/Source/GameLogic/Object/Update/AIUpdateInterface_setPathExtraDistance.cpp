// cl: /arch:SSE /MD /DNDEBUG
//
// ?setPathExtraDistance@AIUpdateInterface@@QAEXM@Z, retail 0x002633F3, 17 bytes.
// Dedicated TU (formerly the Rva002633F3FloatField row of
// Common/Disp32FloatFieldSetters.cpp, same flags).
// Identity: WorldBuilder's AIUpdate.cpp:9291 defines
// AIUpdateInterface::setPathExtraDistance storing its argument at +0x168, and
// its retail callers (AIFollowPathState::onEnter 0x0034DFF1 / 0x0034E05A)
// pass the owner AI as ECX, as Zero Hour's setPathExtraDistance callers do.
// Member name from WorldBuilder's accessor (reverse/wb_members.csv).

typedef float Real;

class AIUpdateInterface
{
public:
	void setPathExtraDistance(Real dist);

private:
	char m_pad[0x168];
	Real m_pathExtraDistance;
};

void AIUpdateInterface::setPathExtraDistance(Real dist)
{
	m_pathExtraDistance = dist;
}
