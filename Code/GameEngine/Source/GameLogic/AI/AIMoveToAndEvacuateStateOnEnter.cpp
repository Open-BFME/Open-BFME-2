// cl: /DNDEBUG /MD
// AIMoveToAndEvacuateState::onEnter, retail 0x003500E6 (103 bytes): slot 4
// of vtable 0x00C12D50; subtracts owner position from the stored goal, calls
// Rva0033FA64Do(owner), then runs AIMoveToState::onEnter when length exceeds INV.
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Coord3D
{
public:
	Coord3D() {}
	Coord3D(float ax, float ay, float az) { x = ax; y = ay; z = az; }
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
	Coord3D &operator-=(const Coord3D &that) { x -= that.x; y -= that.y; z -= that.z; return *this; }
	float length() const;
	float x, y, z;
};

inline Coord3D operator-(const Coord3D &a, const Coord3D &b)
{
	Coord3D result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;
};

class Object0033FA64;
void Rva0033FA64Do(const Object0033FA64 *obj);

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner;
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition;
};

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

class AIMoveToAndEvacuateState : public AIMoveToState
{
public:
	virtual StateReturnType onEnter();
};

extern "C" float INV;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

StateReturnType AIMoveToAndEvacuateState::onEnter()
{
	Object *owner = getMachineOwner();
	const Coord3D *pos = owner->getPosition();
	float goalX = m_goalPosition.x;
	float goalY = m_goalPosition.y;
	float goalZ = m_goalPosition.z;
	// Retail loads all three goal components before subtracting owner position.
	_ReadWriteBarrier();
	float dx = goalX - pos->x;
	float dy = goalY - pos->y;
	float dz = goalZ - pos->z;
	// Keep the three arithmetic results live until the target's grouped stores.
	_ReadWriteBarrier();
	Coord3D delta;
	delta.x = dx;
	delta.y = dy;
	delta.z = dz;
	Rva0033FA64Do((const Object0033FA64 *)owner);
	if (delta.length() > INV)
		return AIMoveToState::onEnter();
	return STATE_CONTINUE;
}
