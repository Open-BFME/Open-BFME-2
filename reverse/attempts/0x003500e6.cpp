// ?onEnter@AIMoveToAndEvacuateState@@UAE?AW4StateReturnType@@XZ
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?onEnter@AIMoveToAndEvacuateState@@UAE?AW4StateReturnType@@XZ @0x003500E6 103B finish from stash 0.96 plus INV.
// Slot 4 of 0x00C12D50: goal +0x20 minus owner +0x38 then Rva0033FA64Do then base onEnter when length exceeds INV else CONTINUE. Evidence: callees rowed INV in use pin onEnter; prev 0x0034FCAC next 0x0035014D.
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

StateReturnType AIMoveToAndEvacuateState::onEnter()
{
	Object *owner = getMachineOwner();
	const Coord3D *pos = owner->getPosition();
	Coord3D delta = m_goalPosition - *pos;
	Rva0033FA64Do((const Object0033FA64 *)owner);
	if (delta.length() > INV)
		return AIMoveToState::onEnter();
	return STATE_CONTINUE;
}
