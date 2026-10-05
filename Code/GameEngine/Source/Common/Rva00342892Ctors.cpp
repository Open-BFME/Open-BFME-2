// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva00342892@@QAE@PAVStateMachine@@@Z @0x00342892 29B
// ??0Rva003428AF@@QAE@PAVStateMachine@@@Z @0x003428AF 29B
// AIInternalMoveToState-derived ctors, hashes 0xD5F5D4FA / 0xE3F474A1,
// vtables 0x00812538 / 0x00812580, no extra members. Same base + vtable
// shape as landed siblings Rva00342826Ctor.cpp (29B) and
// Rva00342843Ctor.cpp (37B, with members). Evidence: intermediate base
// pin 0x0034286E Rva0034286E ctor (over AIInternalMoveToState 0x0033F279);
// each body abuts the next.
class StateMachine;
struct Coord3D
{
	float x, y, z;
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition;
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination;
};
class Rva0034286E : public AIInternalMoveToState
{
public:
	Rva0034286E(StateMachine *machine, unsigned int hash);
};
class Rva00342892 : public Rva0034286E
{
public:
	Rva00342892(StateMachine *machine);
};
Rva00342892::Rva00342892(StateMachine *machine)
	: Rva0034286E(machine, 0xD5F5D4FAu)
{
}
class Rva003428AF : public Rva0034286E
{
public:
	Rva003428AF(StateMachine *machine);
};
Rva003428AF::Rva003428AF(StateMachine *machine)
	: Rva0034286E(machine, 0xE3F474A1u)
{
}
