// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z
// partial score=0.995 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z @0x0039E5B9 (165B).
// Team center into a Coord3D: average the member Objects' +0x38 positions
// through the rowed DLINK iterator (iterate_TeamMemberList 0x00263864,
// advance 0x00263526), scaled by 1.0/count. Callers: ReturnTheRing
// 0x005AB5B7 (REL32 at 0x005AB5EC) plus ScriptActions nearest-kindof,
// Rva00368004Getter, AIGuardMachineGuardPosition and BfmeApplierBH.
// Views: DLINK_ITERATOR and Team head from TeamIterateTeamMemberList.cpp,
// Object +0x38 position from TeamUpdateState.cpp.
// Prior bank (score 0.9) notes: no empty-team guard - retail divides by
// zero (1.0f/0.0f) when the team has no members; kept here for the record.

struct Coord3D
{
	float x, y, z;
};

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

// Introduces the vbptr at its own +0; lands at +0x68 inside Object.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad04[0x38 - 0x04];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad44[0x68 - 0x44];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039E5B9(Coord3D *pos);
};

void Team::rva0039E5B9(Coord3D *pos)
{
	Coord3D sum;
	sum.x = 0.0f;
	sum.y = 0.0f;
	sum.z = 0.0f;
	int count = 0;
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	Object *member;
	while ((member = iter.cur()) != 0)
	{
		sum.x += member->m_pos.x;
		sum.y += member->m_pos.y;
		sum.z += member->m_pos.z;
		++count;
		iter.advance();
	}
	float scale = 1.0f / count;
	sum.x *= scale;
	sum.y *= scale;
	sum.z *= scale;
	*pos = sum;
}
