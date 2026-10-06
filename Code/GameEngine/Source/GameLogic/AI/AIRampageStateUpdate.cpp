// cl: /O1 /DNDEBUG /MD
// ?update@AIRampageState@@UAE?AW4StateReturnType@@XZ @0x0034FE10 94B
// Slot 6 (update) of vtable 0x00811A08 (ctor Rva0033F80E 0x0033F80E stores it).
// Sibling onEnter 0x0034BD1B and onExit 0x0034BDF8 prove the class is
// AIRampageState with Bool +0x20 and frame ints +0x24/+0x28; helper
// rva0034BE57's own comment names this update as its caller.
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

class Slot62Iface : public VSlots<62>
{
public:
	virtual void slot62() = 0;
};

class Object
{
public:
	unsigned char m_pad00[0x250];
	Slot62Iface *m_250; // +0x250
};

class BfmeSubBGB
{
public:
	bool rva00298893();
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_frame40; // +0x40
};
extern GameLogic *TheGameLogic;

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(int status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

class AIRampageState : public State
{
public:
	virtual StateReturnType update();
	void rva0034BE57(Object *obj);
private:
	bool m_20; // +0x20
	unsigned char m_pad21[0x24 - 0x21];
	unsigned int m_24; // +0x24
	unsigned int m_28; // +0x28
};

StateReturnType AIRampageState::update()
{
	Object *owner = m_machine->getOwner();
	if (!owner)
		return STATE_FAILURE;
	rva0034BE57(owner);
	if (m_28 <= TheGameLogic->m_frame40)
	{
		Slot62Iface *iface = owner->m_250;
		if (iface)
			iface->slot62();
		m_28 = (unsigned int)-1;
	}
	if (m_24 <= TheGameLogic->m_frame40)
	{
		((BfmeSubBGB *)owner)->rva00298893();
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
