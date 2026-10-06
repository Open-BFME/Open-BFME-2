// cl: /DNDEBUG /MD
//
// ?getCurrentStateID@AIUpdateInterface@@QBEHXZ, retail 0x00262FC3, 40 bytes.
// AIUpdateInterface::getCurrentStateID inlined from AIStateMachine: machine at
// +0x30; primary State* at machine+0x50 else INVALID 999999 (0xF423F); if that
// id is INVALID fall back to State* at machine+0x04 else INVALID. State ID at
// +0x04. Donor BFME1 AIUpdateInterface_joinTeam.cpp getCurrentStateID plus
// WaypointGoalPathSize.cpp primary/fallback shape (BFME2 shifts +0x58/+0x1C to
// +0x50/+0x04); callers compare to AI_FOLLOW_PATH 6 and 0x43 then size a
// 12-byte vector. No direct callees.

struct AIState
{
	char m_pad00[4];
	int m_id;
};

struct AIStateMachine
{
	char m_pad00[4];
	AIState *m_state04;
	char m_pad08[0x50 - 8];
	AIState *m_state50;
};

class AIUpdateInterface
{
	char m_pad00[0x30];
	AIStateMachine *m_machine;
public:
	int getCurrentStateID() const;
};

int AIUpdateInterface::getCurrentStateID() const
{
	AIStateMachine *m = m_machine;
	int id = m->m_state50 ? m->m_state50->m_id : 0xF423F;
	if (id != 0xF423F)
		return id;
	return m->m_state04 ? m->m_state04->m_id : 0xF423F;
}
