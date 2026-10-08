// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// makeStateMachine overrides (vtable slot 150) of three AIUpdate subclasses,
// each Zero Hour's newInstance(AIStateMachine)(getObject(), name) with BFME
// 2's name key in place of the name, as the rowed base
// AIUpdateInterface::makeStateMachine 0x00262513 does with 0x4A9A0E38:
//  - SupplyTruckAIUpdate, retail 0x004A6E33 (vtable 0x00852FB0), key 0x539D6184
//  - TransportAIUpdate, retail 0x004A90EC (vtable 0x00853AA8), key 0x2FD27857
//  - WanderAIUpdate, retail 0x004A93C9 (vtable 0x00853D30), key 0x11224BB7
// Each vtable's slot 150 holds the address; the class names are the data
// ledger's for those vtables.
typedef unsigned int UnsignedInt;
class Object;
class AIStateMachine
{
public:
	AIStateMachine(Object *owner, UnsignedInt nameKey);	// rowed 0x00351C48
private:
	unsigned char m_pad[0x68];	// operator new size 0x68
};
class AIUpdateModuleView
{
public:
	Object *getObject() const { return m_object; }
protected:
	virtual void v000();
	unsigned char m_pad04[0x04];
	Object *m_object; // +0x08
};
class SupplyTruckAIUpdate : public AIUpdateModuleView
{
protected:
	virtual AIStateMachine *makeStateMachine();
};
class TransportAIUpdate : public AIUpdateModuleView
{
protected:
	virtual AIStateMachine *makeStateMachine();
};
class WanderAIUpdate : public AIUpdateModuleView
{
protected:
	virtual AIStateMachine *makeStateMachine();
};

AIStateMachine *SupplyTruckAIUpdate::makeStateMachine()
{
	return new AIStateMachine(getObject(), 0x539D6184);
}

AIStateMachine *TransportAIUpdate::makeStateMachine()
{
	return new AIStateMachine(getObject(), 0x2FD27857);
}

AIStateMachine *WanderAIUpdate::makeStateMachine()
{
	return new AIStateMachine(getObject(), 0x11224BB7);
}

// Two machine factories reached only through vtables, both newInstance'ing a
// sub-machine for the machine's owner (StateMachine +0x14) with a name key:
//  - AIStateMachine vtable 0x00814CD0 slot 10, retail 0x0034145C: the rowed
//    AIGuardMachine (0x00543163) with key 0x0F9E47F7;
//  - giant-bird machine vtable 0x00817600 slot 9 (also at 0x0081778C), retail
//    0x00367F9E: the rowed sub-machine 0x003676A2 with key 0x615E895F.
// Slot names are unknown; the methods keep their addresses.
class AIGuardMachine
{
public:
	AIGuardMachine(Object *owner, UnsignedInt nameKey);	// rowed 0x00543163
private:
	unsigned char m_pad[0x74];	// operator new size 0x74
};
class Rva003676A2
{
public:
	Rva003676A2(Object *owner, UnsignedInt nameKey);	// rowed 0x003676A2
private:
	unsigned char m_pad[0x3C];	// operator new size 0x3C
};
class StateMachineOwnerView
{
public:
	Object *getOwner() const { return m_owner; }
protected:
	virtual void v000();
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};
class AIStateMachineSlot10 : public StateMachineOwnerView
{
public:
	virtual AIGuardMachine *rva0034145C();
};
class Rva0036792FSlot9 : public StateMachineOwnerView
{
public:
	virtual Rva003676A2 *rva00367F9E();
};

AIGuardMachine *AIStateMachineSlot10::rva0034145C()
{
	return new AIGuardMachine(getOwner(), 0x0F9E47F7);
}

Rva003676A2 *Rva0036792FSlot9::rva00367F9E()
{
	return new Rva003676A2(getOwner(), 0x615E895F);
}
