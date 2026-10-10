// cl: /MD
// ??1GiantBirdGuardMachine@@UAE@XZ @0x00367F8D 11B
// Empty virtual dtor storing vtable 0x00817768 then tail-jmp to rowed base
// ??1AIGuardMachine@@UAE@XZ @0x00542C19 (itself child of StateMachine).
// Evidence: retail mov [ecx],0x00817768 plus jmp to 0x542C19; deleting dtor
// 0x00368B35 (vtable slot 0) calls here then conditional delete (28B ??_G
// shape). Owner (target facts): the rowed GiantBirdGuardMachine ctor
// 0x00368A13 installs the same vtable, whose slot 2 0x00367F98 returns
// "GiantBirdGuardMachine" and slot 3 is the rowed GiantBirdGuardMachine::xfer;
// the base's vtable 0x00869680 slot 2 returns "AIGuardMachine". Both classes
// declare only their destructors, like GiantBirdGuardMachine.cpp's views, so
// the vtable and deleting destructor copies agree.
class AIGuardMachine
{
public:
	virtual ~AIGuardMachine();
};
class GiantBirdGuardMachine : public AIGuardMachine
{
public:
	virtual ~GiantBirdGuardMachine();
};
GiantBirdGuardMachine::~GiantBirdGuardMachine()
{
}
