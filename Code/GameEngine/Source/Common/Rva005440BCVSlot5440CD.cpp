// cl: /MD
// ?rva005440CD@Rva005440BC@@UAEXXZ, retail 0x005440CD, 41 bytes.
// Virtual slot 15 (offset 0x3C) of vtable 0x008699A0 (VA 0x00C699A0), class of
// ??1Rva005440BC@@UAE@XZ in Rva004D759CDerived.cpp (base StateMachine). Gets TurretStateMachine
// goal object, finds the DockUpdateInterface via Object::getDockUpdateInterface, notifies slot 0x34 with
// this+0x14, then tail-jumps to StateMachine::halt. Callees getGoalObject
// 0x004D7726 getDockUpdateInterface 0x0028BCB4 halt 0x004D73A4 already rowed.

class Object;
class DockUpdateInterface;

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class Object
{
public:
	DockUpdateInterface *getDockUpdateInterface();
};

class DockUpdateInterface
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void onSlot34( int v );
};

class StateMachine
{
public:
	virtual ~StateMachine();
	void halt();

private:
	char m_pad04[ 8 ];
};

class Rva005440BC : public StateMachine
{
public:
	virtual void rva005440CD();

private:
	char m_pad0C[ 8 ];
	int m_14;
};

void Rva005440BC::rva005440CD()
{
	TurretStateMachine *turret = (TurretStateMachine *)this;
	Object *goal = turret->getGoalObject();
	if( goal == 0 )
		goto halt;

	DockUpdateInterface *bec = goal->getDockUpdateInterface();
	if( bec == 0 )
		goto halt;

	bec->onSlot34( m_14 );

halt:
	halt();
}
