// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z
// partial score=0.960515703287303 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z
// partial score=0.97 date=2026-09-27
// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z
// partial score=0.97 date=2026-09-27
// cl: /O1 /DNDEBUG /MD /arch:SSE
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object;
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};
class Object
{
public:
	unsigned char m_pad0[0x38];
	Coord3D m_position;
};
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039E5B9(Coord3D *out);
};
// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z present-unmatched
void Team::rva0039E5B9(Coord3D *out)
{
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	int count = 0;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		pos.x += cur->m_position.x;
		pos.y += cur->m_position.y;
		pos.z += cur->m_position.z;
		++count;
	}
	float recip = 1.0f / (float)count;
 _ReadWriteBarrier();
	pos.x *= recip;
	pos.y *= recip;
	pos.z *= recip;
	*out = pos;
}