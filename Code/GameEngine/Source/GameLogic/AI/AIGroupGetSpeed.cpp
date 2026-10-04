// cl: /O1 /DNDEBUG /MD
//
// ?getSpeed@AIGroup@@QAEMXZ @0x0036E333 (19B), Zero Hour AIGroup.cpp shape:
// recompute when dirty, then return the cached group speed. Target evidence:
// the dirty byte at +0x0C, the x87 load of +0x08, and the call to 0x0036D2C5,
// which is AIGroup::recompute (getCenter, then the +0x08 speed stores and the
// +0x0C clear at its end). Caller AIFollowWaypointPathExactState::onEnter
// 0x0034F090. View of the BFME 2 prefix only.

typedef float Real;
typedef bool Bool;

class AIGroup
{
public:
	Real getSpeed(void);

private:
	void recompute(void);

	unsigned char m_pad00[8];
	Real m_speed;   // +0x08
	Bool m_dirty;   // +0x0C
};

Real AIGroup::getSpeed(void)
{
	if (m_dirty)
		recompute();

	return m_speed;
}
