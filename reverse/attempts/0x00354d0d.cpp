// ?onEnter@Rva003428CC@@UAE?AW4StateReturnType@@XZ
// partial score=0.91 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?onEnter@Rva003428CC@@UAE?AW4StateReturnType@@XZ, retail 0x00354D0D, 419B: slot 4 of vtable 0x008125C8.
// Evidence: vslot slot 4 (onEnter); ctor TU AIStateMoveTightenCtors Rva003428CC; TurretStateMachine goal via rowed getGoalObject 0x004D7726; CritterDesync 13 log.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x, y, z;
	void normalize();
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual ~GeometryInfo();
	float getMaxHeightAbovePosition() const;
private:
	unsigned char m_pad04[0x5C - 0x04];
};

class Object
{
public:
	void rva0028AE6D();
	void rva0028AD32();
private:
	unsigned char m_pad00[0x38];
public:
	Coord3D m_pos; // +0x38
private:
	unsigned char m_pad44[0x114 - 0x44];
public:
	unsigned int m_flags114; // +0x114
private:
	unsigned char m_pad118[0x258 - 0x118];
public:
	class AIUpdateInterface *m_ai; // +0x258
};

template <int N> class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <> class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<142>
{
public:
	virtual void slot142(int val);
	void requestPath(Coord3D *pos, bool flag);
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
public:
	Object *m_owner; // +0x14
};

class TurretStateMachine : public StateMachine
{
public:
	Object *getGoalObject();
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit();
	virtual StateReturnType update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination; // +0x48
};

class Rva00342843 : public AIInternalMoveToState
{
protected:
	int m_4C; // +0x4C
	bool m_50; // +0x50
};

class Rva003428CC : public Rva00342843
{
public:
	virtual StateReturnType onEnter();
private:
	bool m_54; // +0x54
	char m_pad55[3];
	int m_58; // +0x58
};

struct FprintfTarget
{
	char m_pad[4];
};
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern const float g_bfmeClearA;

StateReturnType Rva003428CC::onEnter()
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 13");
	}
	m_adjustsDestination = false;
	Object *owner = m_machine->getOwner();
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	AIUpdateInterface *ai = m_machine->getOwner()->m_ai;
	if (goal == 0 || ai == 0 || owner == 0)
		return STATE_FAILURE;
	GeometryInfo tmp(*(GeometryInfo *)((char *)goal + 0xA8));
	float dz = goal->m_pos.z - owner->m_pos.z;
	if (dz > tmp.getMaxHeightAbovePosition())
		return STATE_FAILURE;
	ai->slot142(4);
	if ((owner->m_flags114 & 1) == 0)
	{
		owner->m_flags114 |= 1;
		owner->rva0028AE6D();
	}
	m_4C = 1;
	m_50 = true;
	m_54 = false;
	owner->rva0028AD32();
	Coord3D dest;
	dest.x = owner->m_pos.x;
	dest.y = owner->m_pos.y;
	dest.z = owner->m_pos.z;
	Coord3D dir;
	dir.x = dest.x - goal->m_pos.x;
	dir.y = dest.y - goal->m_pos.y;
	dir.z = dest.z - goal->m_pos.z;
	dir.normalize();
	dest.x += dir.x * g_bfmeClearA;
	dest.y += dir.y * g_bfmeClearA;
	dest.z += dir.z * g_bfmeClearA;
	ai->requestPath(&dest, true);
	return AIInternalMoveToState::onEnter();
}
